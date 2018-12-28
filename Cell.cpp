#include "Cell.hpp"

#include <ostream>

namespace wade {

std::ostream &
operator<<(std::ostream & a_os, Cell a_cell)
{
    switch (a_cell)
    {
        case Cell::Mine:
            a_os << 'X';
            break;

        case Cell::Zero:
            a_os << ' ';
            break;

        case Cell::One:
            a_os << '1';
            break;

        case Cell::Two:
            a_os << '2';
            break;

        case Cell::Three:
            a_os << '3';
            break;

        case Cell::Four:
            a_os << '4';
            break;

        case Cell::Five:
            a_os << '5';
            break;

        case Cell::Six:
            a_os << '6';
            break;

        case Cell::Seven:
            a_os << '7';
            break;

        case Cell::Eight:
            a_os << '8';
            break;

        case Cell::Flagged:
            a_os << 'F';
            break;

        case Cell::Hidden:
            a_os << '#';
            break;
    }
    return a_os;
}

}

