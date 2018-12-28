#pragma once

#include "Settings.hpp"
#include "Stats.hpp"

#include <cassert>
#include <cstddef>
#include <iosfwd>

namespace wade {

// Play a series of games.
class GameSession
{
public:
    GameSession() = default;

    void play(std::istream &, std::ostream &);

    std::ostream & write(std::ostream &) const;

private:

    Settings m_settings = Settings{9, 9, 10}; // Default to 9x9 board with 10 mines.
    Stats m_stats = {};
};

std::ostream & operator<<(std::ostream &, GameSession const &);

}

