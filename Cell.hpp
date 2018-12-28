#pragma once

#include <iosfwd>

namespace wade {

// Possible states for cell on the board.
enum class Cell : int
{
    Mine  =  -1, // Cell is a mine.
    Zero  =   0, // Adjacent to 0 mines.
    One   =   1, // Adjacent to 1 mine.
    Two   =   2, // Adjacent to 2 mines.
    Three =   3, // Adjacent to 3 mines.
    Four  =   4, // Adjacent to 4 mines.
    Five  =   5, // Adjacent to 5 mines.
    Six   =   6, // Adjacent to 6 mines.
    Seven =   7, // Adjacent to 7 mines.
    Eight =   8, // Adjacent to 8 mines.
    Flagged = 9, // Player has flagged cell as a mine.
    Hidden = 10, // Cell is hidden from the player.
};

std::ostream & operator<<(std::ostream &, Cell);

}

