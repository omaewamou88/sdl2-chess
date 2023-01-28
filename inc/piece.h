#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <tgmath.h>
#include <iostream>

enum pieceType{pawn=0,rook=1,knight=2,bishop=3,queen=4,king=5};

class Piece
{
    public:
    Piece(pieceType ty, bool iw, SDL_Point dp);
    int getTxt();
    SDL_Point getPos();
    bool isColourWhite();
    std::vector<SDL_Point> getPossibleMoves(bool is1, bool is2, bool is3, bool is4);
    private:
    pieceType type;
    bool isWhite;
    int txtIndex;
    SDL_Point position;
};