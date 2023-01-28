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

std::vector<SDL_Point> Piece::getPossibleMoves(bool is1, bool is2, bool is3, bool is4)
{
    std::vector<SDL_Point> v;
    switch(type)
    {
        case pawn:
        if(position.y==(isWhite?6:1)&&!is4) v.push_back({position.x, position.y+(isWhite?-2:2)});
        if(!is2&&(isWhite?position.y>0:position.y<7)) v.push_back({position.x, position.y+(isWhite?-1:1)});
        if(is1&&(isWhite?position.y>0:position.y<7)&&(position.x>0)) v.push_back({position.x-1, position.y+(isWhite?-1:1)});
        if(is3&&(isWhite?position.y>0:position.y<7)&&(position.x<7)) v.push_back({position.x+1, position.y+(isWhite?-1:1)});
        break;
        case rook:
            for(int i=position.x-1; i>=0; i--) v.push_back({i,position.y}); //UP
            for(int i=position.x+1; i<=7; i++) v.push_back({i,position.y}); //DOWN
            for(int i=position.y-1; i>=0; i--) v.push_back({position.x,i}); //LEFT
            for(int i=position.y+1; i<=7; i++) v.push_back({position.x,i}); //RIGHT
        break;
        case knight:
            if(position.x-2>=0&&position.y+1<=7) v.push_back({position.x-2,position.y+1});
            if(position.x-1>=0&&position.y+2<=7) v.push_back({position.x-1,position.y+2});
            if(position.x+2<=7&&position.y+1<=7) v.push_back({position.x+2,position.y+1});
            if(position.x+1<=7&&position.y+2<=7) v.push_back({position.x+1,position.y+2});
            if(position.x+2<=7&&position.y-1>=0) v.push_back({position.x+2,position.y-1});
            if(position.x+1<=7&&position.y-2>=0) v.push_back({position.x+1,position.y-2});
            if(position.x-2>=0&&position.y-1>=0) v.push_back({position.x-2,position.y-1});
            if(position.x-1>=0&&position.y-2>=0) v.push_back({position.x-1,position.y-2});
        break;
        case bishop:
            for(int i=1;;i++) if(position.x-i>=0&&position.y-i>=0) v.push_back({position.x-i,position.y-i}); else break;
            for(int i=1;;i++) if(position.x+i<=7&&position.y-i>=0) v.push_back({position.x+i,position.y-i}); else break;
            for(int i=1;;i++) if(position.x+i<=7&&position.y+i<=7) v.push_back({position.x+i,position.y+i}); else break;
            for(int i=1;;i++) if(position.x-i>=0&&position.y+i<=7) v.push_back({position.x-i,position.y+i}); else break;
        break;
        case queen:
            for(int i=position.x-1; i>=0; i--) v.push_back({i,position.y}); //UP
            for(int i=position.x+1; i<=7; i++) v.push_back({i,position.y}); //DOWN
            for(int i=position.y-1; i>=0; i--) v.push_back({position.x,i}); //LEFT
            for(int i=position.y+1; i<=7; i++) v.push_back({position.x,i}); //RIGHT
            for(int i=1;;i++) if(position.x-i>=0&&position.y-i>=0) v.push_back({position.x-i,position.y-i}); else break;
            for(int i=1;;i++) if(position.x+i<=7&&position.y-i>=0) v.push_back({position.x+i,position.y-i}); else break;
            for(int i=1;;i++) if(position.x+i<=7&&position.y+i<=7) v.push_back({position.x+i,position.y+i}); else break;
            for(int i=1;;i++) if(position.x-i>=0&&position.y+i<=7) v.push_back({position.x-i,position.y+i}); else break;
        break;
        case king:
            if(position.x-1>=0)
            {
                v.push_back({position.x-1,position.y});
                if(position.y-1>=0) v.push_back({position.x-1,position.y-1});
                if(position.y+1<=7) v.push_back({position.x-1,position.y+1});
            }
            if(position.x+1<=7)
            {
                v.push_back({position.x+1,position.y});
                if(position.y-1>=0) v.push_back({position.x+1,position.y-1});
                if(position.y+1<=7) v.push_back({position.x+1,position.y+1});
            }
            if(position.y-1>=0) v.push_back({position.x,position.y-1});
            if(position.y+1<=7) v.push_back({position.x,position.y+1});
        break;
    }
    return v;
}

int Piece::getTxt()
{
    return txtIndex;    
}

SDL_Point Piece::getPos()
{
    return position;
}

void Piece::setPos(SDL_Point pos)
{
    position = pos;
}

bool Piece::isColourWhite()
{
    return isWhite;
}