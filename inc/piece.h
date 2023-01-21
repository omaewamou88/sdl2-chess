#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <tgmath.h>
#include <vector>

enum pieceType{pawn = 0, rook = 1, knight = 2, bishop = 3, queen = 4, king = 5};

struct Piece
{
    Piece();
    bool exists;
    bool isWhite;
    pieceType type;
    int x;
    int y;
};