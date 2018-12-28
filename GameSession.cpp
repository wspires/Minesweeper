#include "GameSession.hpp"

#include "Game.hpp"

#include <cassert>
#include <ostream>
#include <iostream>

namespace wade {

void
GameSession::
play(std::istream & a_is, std::ostream & a_os)
{
    Game game{m_settings};
    auto const result = game.play(a_is, a_os);
    if (result == Game::Result::Won)
    {
        ++m_stats.wins;
    }
    else if (result == Game::Result::Won)
    {
        ++m_stats.losses;
    }
    // TODO: Ask to play again
}

std::ostream &
GameSession::
write(std::ostream & a_os) const
{
    a_os << "settings=" << m_settings
        << ", stats=" << m_stats
        ;
    return a_os;
}

std::ostream &
operator<<(std::ostream & a_os, GameSession const & a_game_session)
{
    a_game_session.write(a_os);
    return a_os;
}

}

