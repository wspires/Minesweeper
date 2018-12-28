#pragma once

#include <cstdint>
#include <iosfwd>

namespace wade {

struct Settings
{
    size_t rows = 1;
    size_t cols = 1;
    size_t mines = 1;
};

std::ostream & operator<<(std::ostream &, Settings const &);

}

