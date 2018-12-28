#include "Stats.hpp"

#include <ostream>

namespace wade {

double
Stats::
percentage() const
{
    auto total = wins + losses;
    if (total == 0)
    {
        return 0;
    }
    return 100. * (wins / total);
}

std::ostream &
operator<<(std::ostream & a_os, Stats const & a_stats)
{
    a_os << "wins = " << a_stats.wins
        << ", losses = " << a_stats.losses
        << ", win_percentage = " << a_stats.percentage()
        ;
    return a_os;
}

}

