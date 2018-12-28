#include "GameSession.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char * argv[])
{
    std::ios::sync_with_stdio(false);
    wade::GameSession game_session{};
    game_session.play(std::cin, std::cout);
    return EXIT_SUCCESS;
}

