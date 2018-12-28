#include "Coord.hpp"

#include <ostream>

namespace wade {

std::ostream &
operator<<(std::ostream & a_os, Coord const & a_coord)
{
    a_os << "("
        << a_coord.row
        << ", " << a_coord.col
        << ")"
        ;
    return a_os;
}

}

