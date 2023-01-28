#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <tgmath.h>
#include <vector>

struct Piece
{
    Piece();
    std::vector<SDL_Point> getPossibleMoves();
};