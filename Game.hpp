#pragma once

#include "Board.hpp"
#include "Cell.hpp"
#include "Coord.hpp"
#include "Settings.hpp"

#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>
#include <unordered_set>

namespace wade {

// Play a single game.
class Game
{
public:

    // End game result.
    enum class Result
    {
        None,
        Won,
        Lost,
        Quit,
    };

    Game(Settings const &);

    Result play(std::istream &, std::ostream &);
    Result result() const { return m_result; }

    std::ostream & write(std::ostream &) const;

protected:

    void make_mines(std::size_t a_mines);
    void count_adjacent_mines();

    void handle_help_cmd(std::ostream &);
    void handle_select_cmd(std::vector<std::string> const &, std::ostream &);
    bool handle_cmd(std::vector<std::string> const &, std::ostream &);
    void show_more_board(Coord const &);
    void check_for_win();

    static std::string select_cmd_usage();

    using Coords = std::vector<Coord>;
    static Coords offsets();

private:

    Board m_real_board; // Real board with mines shown.
    Board m_play_board; // Play board that player sees.
    Result m_result = Result::None;

    using CoordSet = std::unordered_set<Coord>;
    CoordSet m_mine_coords = {};
};

std::ostream & operator<<(std::ostream &, Game const &);

}

