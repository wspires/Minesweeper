#pragma once

#include "Cell.hpp"
#include "Coord.hpp"
#include "Settings.hpp"

#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <vector>

namespace wade {

class Board
{
public:
    // Ctors.
    Board(std::size_t a_rows, std::size_t a_cols);
    Board(Settings const &);

    // Get numbers of rows and columns.
    std::size_t rows() const;
    std::size_t cols() const;

    // Determine if row and column is a valid board position.
    bool is_valid(std::size_t row, std::size_t col) const;
    bool is_valid(Coord const &) const;

    // Access cell on the board.
    Cell & at(std::size_t row, std::size_t col)             { assert(is_valid(row, col)); return m_board[row][col]; }
    Cell const & at(std::size_t row, std::size_t col) const { assert(is_valid(row, col)); return m_board[row][col]; }
    Cell & at(Coord const & a_coord)             { assert(is_valid(a_coord)); return m_board[a_coord.row][a_coord.col]; }
    Cell const & at(Coord const & a_coord) const { assert(is_valid(a_coord)); return m_board[a_coord.row][a_coord.col]; }

    // Determine if board has a mine at the given position.
    bool is_mine(std::size_t row, std::size_t col) const { return at(row, col) == Cell::Mine; }
    bool is_mine(Coord const & a_coord) const { return at(a_coord) == Cell::Mine; }

    void hide();

    std::ostream & write(std::ostream &) const;

private:

    using Row = std::vector<Cell>;
    using Grid = std::vector<Row>;

    Grid m_board = {};
};

inline
std::size_t
Board::
rows() const
{
    return m_board.size();
}

inline
std::size_t
Board::
cols() const
{
    assert(rows() != 0);
    return m_board[0].size();
}

std::ostream & operator<<(std::ostream &, Board const &);

}

