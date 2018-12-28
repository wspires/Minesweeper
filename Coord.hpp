#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <iosfwd>

namespace wade {

// Row and column coordinate.
struct Coord
{
    std::int64_t row = 0;
    std::int64_t col = 0;

    // Equality operators.
    bool operator==(Coord const & a_rhs) const noexcept
    {
        return (row == a_rhs.row) and (col == a_rhs.col);
    }
    bool operator!=(Coord const & a_rhs) const noexcept
    {
        return not (*this == a_rhs);
    }

    // Comparison operators.
    bool operator<(Coord const & a_rhs) const noexcept
    {
        if (row == a_rhs.row)
        {
            return col < a_rhs.col;
        }
        return row < a_rhs.row;
    }
    bool operator<=(Coord const & a_rhs) const noexcept
    {
        return (*this < a_rhs) or (*this == a_rhs);
    }
    bool operator>(Coord const & a_rhs) const noexcept
    {
        return not (*this <= a_rhs);
    }
    bool operator>=(Coord const & a_rhs) const noexcept
    {
        return (*this > a_rhs) or (*this == a_rhs);
    }

    // Arithmetic operators.
    Coord & operator+=(Coord const & a_rhs)
    {
        row += a_rhs.row;
        col += a_rhs.col;
        return *this;
    }
    Coord & operator+(Coord const & a_rhs) const
    {
        return Coord{*this} += a_rhs;
    }
    Coord & operator-=(Coord const & a_rhs)
    {
        row -= a_rhs.row;
        col -= a_rhs.col;
        return *this;
    }
    Coord & operator-(Coord const & a_rhs) const
    {
        return Coord{*this} -= a_rhs;
    }
};

std::ostream & operator<<(std::ostream &, Coord const &);

}

// Custom specialization of std::hash injected in namespace std.
namespace std
{
    template<>
    struct hash<wade::Coord>
    {
        std::size_t operator()(wade::Coord const & a_coord) const noexcept
        {
            // Combine individual row and column hashes.
            auto const h1 = std::hash<decltype(a_coord.row)>{}(a_coord.row);
            auto const h2 = std::hash<decltype(a_coord.col)>{}(a_coord.col);
            return h1 ^ (h2 << 1); // Or use boost::hash_combine.
        }
    };
}

