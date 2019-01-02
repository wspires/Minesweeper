#include "Game.hpp"

#include <cassert>
#include <istream>
#include <iterator>
#include <ostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace wade {

Game::
Game(Settings const & a_settings)
    : m_real_board{a_settings}
    , m_play_board{a_settings}
{
    make_mines(a_settings.mines);
    m_play_board.hide();
}

void
Game::
make_mines(std::size_t a_mines)
{
    // Limit the number of mines: must have at least 1 empty space.
    a_mines = std::min(a_mines, (m_real_board.rows() * m_real_board.cols()) - 1);

    m_mine_coords.clear();

    std::random_device rd{}; // Will be used to obtain a seed for the random number engine.
    std::mt19937 gen{rd()}; // Standard mersenne_twister_engine seeded with rd().

    // Distributions for rows and columns.
    std::uniform_int_distribution<> row_dist{0, static_cast<int>(m_real_board.rows() - 1)};
    std::uniform_int_distribution<> col_dist{0, static_cast<int>(m_real_board.cols() - 1)};

    // Generate random mine locations.
    for (std::size_t i = 0; i != a_mines; ++i)
    {
        // Keep trying to generate a coordinate until we get a unique one.
        Coord coord{};
        while (1)
        {
            auto row = row_dist(gen);
            auto col = col_dist(gen);
            coord = Coord{row, col};
            if (m_mine_coords.find(coord) == std::cend(m_mine_coords))
            {
                break;
            }
        }

        m_mine_coords.insert(coord);
        m_real_board.at(coord) = Cell::Mine;
    }

    count_adjacent_mines();
}


void
Game::
count_adjacent_mines()
{
    // Increment count for each cell adjacent to a mine.
    for (auto && coord : m_mine_coords)
    {
        for (auto && offset : offsets())
        {
            auto adj_coord = coord + offset;
            if (not m_real_board.is_valid(adj_coord)
                or m_real_board.is_mine(adj_coord))
            {
                continue;
            }

            // Relying on Cell enum Zero, One, etc. values to correspond directly to values.
            static_assert(static_cast<int>(Cell::Zero) == 0, "Cell enum values must correspond to int values");
            static_assert(static_cast<int>(Cell::Eight) == 8, "Cell enum values must correspond to int values");
            Cell cell = m_real_board.at(adj_coord);
            int cell_value = static_cast<int>(cell);
            ++cell_value;
            m_real_board.at(adj_coord) = static_cast<Cell>(cell_value);
        }
    }
}

Game::Coords
Game::
offsets()
{
    // Offsets for all around a coord, including diagonals.
    static std::vector<Coord> coord_offsets = {
          {-1, -1}
        , {-1,  0}
        , {-1, +1}
        , { 0, -1}
        , { 0, +1}
        , {+1, -1}
        , {+1,  0}
        , {+1, +1}
        };
    return coord_offsets;
}

Game::Result
Game::
play(std::istream & a_is, std::ostream & a_os)
{
    m_result = Result::None;

    static std::string const prompt = "> ";

    // Show user the board and available commands to begin.
    a_os << m_play_board;
    handle_help_cmd(a_os);
    a_os << prompt;

    // Read each line.
    std::string line{};
    while (std::getline(a_is, line))
    {
        a_os << line << '\n';

        // Split line into words (space-delimited).
        std::vector<std::string> words{};
        std::stringstream ss{line};
        std::string word{};
        while (std::getline(ss, word, ' '))
        {
            words.push_back(word);
        }

        bool const keep_playing = handle_cmd(words, a_os);
        if (not keep_playing)
        {
            break;
        }

        a_os << prompt;
    }

    a_os << m_real_board;
    if (m_result != Result::Quit)
    {
        if (m_result == Result::Won)
        {
            a_os << "You won!" << std::endl;
        }
        else if (m_result == Result::Lost)
        {
            a_os << "Sorry, you lost..." << std::endl;
        }
    }

    return m_result;
}

bool
Game::
handle_cmd(std::vector<std::string> const & a_words, std::ostream & a_os)
{
    if (a_words.empty())
    {
        return true;
    }

    // Handle commands.
    auto && cmd = a_words.front();
    if (cmd == "quit" or cmd == "q")
    {
        m_result = Result::Quit;
        return false;
    }
    else if (cmd == "help" or cmd == "h" or cmd == "?")
    {
        handle_help_cmd(a_os);
    }
    else if (cmd == "select" or cmd == "s")
    {
        handle_select_cmd(a_words, a_os);
    }
    else if (cmd == "flag" or cmd == "f")
    {
        handle_flag_cmd(a_words, a_os);
    }
    else if (cmd == "board" or cmd == "b")
    {
        a_os << m_play_board;
    }
    else
    {
        a_os << "Invalid command: '" << cmd << "'" << std::endl;
    }

    // Keep playing until have a result.
    bool const keep_playing = (m_result == Result::None);
    return keep_playing;
}

void
Game::
handle_help_cmd(std::ostream & a_os)
{
    a_os << "=== Help ===\n"
        << "quit: Quit game\n"
        << "help: Show this help message\n"
        << "select: Select square: " << select_cmd_usage() << '\n'
        << "flag: Flag square as suspected mine: " << flag_cmd_usage() << '\n'
        << "board: Show the board\n"
        ;
}

void
Game::
handle_select_cmd(std::vector<std::string> const & a_words, std::ostream & a_os)
{
    auto write_usage = [&a_os]()
        {
            a_os << "usage: " << select_cmd_usage() << '\n';
        };
    if (a_words.size() != 3)
    {
        write_usage();
        return;
    }

    try
    {
        auto row = std::stoi(a_words[1]);
        auto col = std::stoi(a_words[2]);
        auto coord = Coord{row, col};

        if (not m_real_board.is_valid(coord))
        {
            auto max_row = static_cast<decltype(row)>(m_real_board.rows() - 1);
            auto max_col = static_cast<decltype(col)>(m_real_board.cols() - 1);
            a_os << "Coordinate " << coord << " is invalid"
                << ": Select a coordinate from " << Coord{0, 0} << " to " << Coord{max_row, max_col}
                << std::endl;
            return;
        }

        // Selected a mine, so lost.
        if (m_mine_coords.find(coord) != std::cend(m_mine_coords))
        {
            m_result = Result::Lost;
            return;
        }

        show_more_board(coord);
        check_for_win();
        a_os << m_play_board;
    }
    catch (...)
    {
        write_usage();
    }
}

void
Game::
show_more_board(Coord const & selected_coord)
{
    // Use breadth-first search to show more area of the board.
    CoordSet visited{};
    std::queue<Coord> q{};
    q.push(selected_coord);

    while (not q.empty())
    {
        auto && coord = q.front();
        q.pop();

        // Visit coordinate by showing more of the real board.
        m_play_board.at(coord) = m_real_board.at(coord);
        visited.insert(coord);

        // We can see cells that border a mine, but it acts as a wall and we cannot queue this adjacent cell,
        // so only queue empty (0) cells.
        auto cell = m_real_board.at(coord);
        int cell_value = static_cast<int>(cell);
        if (cell_value != 0)
        {
            continue;
        }

        for (auto && offset : offsets())
        {
            auto adj_coord = coord + offset;
            if (not m_real_board.is_valid(adj_coord)
                or visited.find(adj_coord) != std::cend(visited)
                )
            {
                // Skip invalid coordinates and already-visited cells.
                continue;
            }

            // Queue adjacent coordinate to be visited.
            q.push(adj_coord);
        }
    }
}

void
Game::
check_for_win()
{
    // We won if the only hidden cells left are mines.
    std::size_t hidden_count = 0;
    for (std::size_t i = 0; i != m_play_board.rows(); ++i)
    {
        for (std::size_t j = 0; j != m_play_board.rows(); ++j)
        {
            if (m_play_board.at(i, j) == Cell::Hidden
                or m_play_board.at(i, j) == Cell::Flagged
                )
            {
                ++hidden_count;
            }
        }
    }
    if (hidden_count == m_mine_coords.size())
    {
        m_result = Result::Won;
    }
}

void
Game::
handle_flag_cmd(std::vector<std::string> const & a_words, std::ostream & a_os)
{
    auto write_usage = [&a_os]()
        {
            a_os << "usage: " << flag_cmd_usage() << '\n';
        };
    if (a_words.size() != 3)
    {
        write_usage();
        return;
    }

    try
    {
        auto row = std::stoi(a_words[1]);
        auto col = std::stoi(a_words[2]);
        auto coord = Coord{row, col};

        if (m_play_board.at(coord) == Cell::Hidden)
        {
            m_play_board.at(coord) = Cell::Flagged;
            // TODO: Save flagged coords and add command to list them.
        }
        else if (m_play_board.at(coord) == Cell::Flagged)
        {
            m_play_board.at(coord) = Cell::Hidden;
        }
        a_os << m_play_board;
    }
    catch (...)
    {
        write_usage();
    }
}

std::string
Game::
select_cmd_usage()
{
    return "select <row> <col>";
}

std::string
Game::
flag_cmd_usage()
{
    return "flag <row> <col>";
}

std::ostream &
Game::
write(std::ostream & a_os) const
{
    a_os << m_real_board;

    a_os << "=== Mines ===" << std::endl;
    for (auto && mine : m_mine_coords)
    {
        a_os << mine << std::endl;
    }

    return a_os;
}

std::ostream &
operator<<(std::ostream & a_os, Game const & a_game)
{
    a_game.write(a_os);
    return a_os;
}

}

