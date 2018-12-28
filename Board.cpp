#include "Board.hpp"

#include <cassert>
#include <ostream>

namespace wade {

Board::
Board(std::size_t a_rows, std::size_t a_cols)
    : m_board(a_rows, Row(a_cols, Cell::Zero))
{
    assert(a_rows > 0);
    assert(a_cols > 0);
}

Board::
Board(Settings const & a_settings)
    : Board{a_settings.rows, a_settings.cols}
{
}

bool
Board::
is_valid(std::size_t row, std::size_t col) const
{
    if (row >= rows())
    {
        return false;
    }
    else if (col >= cols())
    {
        return false;
    }
    return true;
}

bool
Board::
is_valid(Coord const & a_coord) const
{
    return is_valid(a_coord.row, a_coord.col);
}

void
Board::
hide()
{
    for (auto && row : m_board)
    {
        for (auto && cell : row)
        {
            cell = Cell::Hidden;
        }
    }
}

std::ostream &
Board::
write(std::ostream & a_os) const
{
    // Functions to write border along top and bottom.
    auto write_digit_border =
        [this, &a_os]()
        {
            // Write digits to make it easier to select a cell coordinate.
            a_os << "  ";
            for (std::size_t i = 0; i != cols(); ++i)
            {
                a_os << (i % 10) << ' ';
            }
            a_os << std::endl;
        };
    auto write_border =
        [this, &a_os]()
        {
            a_os << " |-";
            for (std::size_t i = 1; i != cols(); ++i)
            {
                a_os << '-' << '-';
            }
            a_os << '|' << std::endl;
        };

    // Write top border.
    write_digit_border();
    write_border();

    int i = 0;
    for (auto && row : m_board)
    {
        // Write |cell|
        a_os << (i % 10) << '|';
        for (auto && cell : row)
        {
            a_os << cell << '|';
        }
        a_os << (i % 10) << std::endl;
        ++i;
    }

    // Write bottom border.
    write_border();
    write_digit_border();

    return a_os;
}

std::ostream &
operator<<(std::ostream & a_os, Board const & a_board)
{
    a_board.write(a_os);
    return a_os;
}

}

