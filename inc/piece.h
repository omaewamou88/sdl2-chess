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
    void setPos(SDL_Point pos);
    bool isColourWhite();
    std::vector<SDL_Point> getPossibleMoves(int m[8][8]);
    private:
    pieceType type;
    bool isWhite;
    int txtIndex;
    SDL_Point position;
};