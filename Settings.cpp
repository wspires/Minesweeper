#include "Settings.hpp"

#include <ostream>

namespace wade {

std::ostream &
operator<<(std::ostream & a_os, Settings const & a_settings)
{
    a_os << "Settings{"
        << "rows=" << a_settings.rows
        << ", cols=" << a_settings.cols
        << ", mines=" << a_settings.mines
        << "}"
        ;
    return a_os;
}

}

