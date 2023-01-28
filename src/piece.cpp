#include <piece.h>

Piece::Piece(pieceType ty, bool iw, SDL_Point dp):type(ty),isWhite(iw),position(dp)
{
    txtIndex = 0;
    txtIndex = txtIndex + isWhite?6:0;
    switch(type)
    {
        case pawn: break;
        case rook: txtIndex+=1; break;
        case knight: txtIndex+=2; break;
        case bishop: txtIndex+=3; break;
        case queen: txtIndex+=4; break;
        case king: txtIndex+=5; break;
    }
}

int Piece::getTxt()
{
    return txtIndex;    
}

SDL_Point Piece::getPos()
{
    return position;
}