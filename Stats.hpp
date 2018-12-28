#pragma once

#include <cstddef>
#include <iosfwd>

namespace wade {

struct Stats
{
    std::size_t wins = 0;
    std::size_t losses = 0;

    // Calculate win percentage.
    double percentage() const;
};

std::ostream & operator<<(std::ostream &, Stats const &);

}

