#include <piece.h>

Piece::Piece():exists(true){}

std::vector<SDL_Point> Piece::getPossibleMoves()
{
    std::vector<SDL_Point> ret;
    int n;
    switch(this->type)
    {
        case pieceType::pawn:
            ret.push_back({this->x,this->isWhite?y-1:y+1});
            if((this->isWhite&&this->y==6)||(!this->isWhite&&this->y==1)) ret.push_back({this->x,this->isWhite?y-2:y+2});
            return ret;
        break;
        case pieceType::rook:
            for(int i = this->y-1; i>=0; i--) ret.push_back({this->x,i}); //UP
            for(int i = this->y+1; i<=7; i++) ret.push_back({this->x,i}); //DOWN
            for(int i = this->x-1; i>=0; i--) ret.push_back({i,this->y}); //LEFT
            for(int i = this->x+1; i<=7; i++) ret.push_back({i,this->y}); //RIGHT
            return ret;
        break;
        case pieceType::knight:
            if(x-1>=0&&y-2>=0) ret.push_back({x-1,y-2});
            if(x-2>=0&&y-1>=0) ret.push_back({x-2,y-1});
            if(x-1>=0&&y+2<=7) ret.push_back({x-1,y+2});
            if(x-2>=0&&y+1<=7) ret.push_back({x-2,y+1});
            if(x+1<=7&&y-2>=0) ret.push_back({x+1,y-2});
            if(x+2<=7&&y-1>=0) ret.push_back({x+2,y-1});
            if(x+1<=7&&y+2<=7) ret.push_back({x+1,y+2});
            if(x+2<=7&&y+1<=7) ret.push_back({x+2,y+1});
        break;
        case pieceType::bishop:
            n = 1; while(x-n>=0&&y-n>=0) {ret.push_back({x-n,y-n}); n++;}
            n = 1; while(x-n>=0&&y+n<=7) {ret.push_back({x-n,y+n}); n++;}
            n = 1; while(x+n<=7&&y-n>=0) {ret.push_back({x+n,y-n}); n++;}
            n = 1; while(x+n<=7&&y+n<=7) {ret.push_back({x+n,y+n}); n++;}
        break;
        case pieceType::queen:
            for(int i = this->y-1; i>=0; i--) ret.push_back({this->x,i}); //UP
            for(int i = this->y+1; i<=7; i++) ret.push_back({this->x,i}); //DOWN
            for(int i = this->x-1; i>=0; i--) ret.push_back({i,this->y}); //LEFT
            for(int i = this->x+1; i<=7; i++) ret.push_back({i,this->y}); //RIGHT
            n = 1; while(x-n>=0&&y-n>=0) {ret.push_back({x-n,y-n}); n++;}
            n = 1; while(x-n>=0&&y+n<=7) {ret.push_back({x-n,y+n}); n++;}
            n = 1; while(x+n<=7&&y-n>=0) {ret.push_back({x+n,y-n}); n++;}
            n = 1; while(x+n<=7&&y+n<=7) {ret.push_back({x+n,y+n}); n++;}
        break;
        case pieceType::king:
            if(x-1>=0) 
            {
                ret.push_back({x-1,y});
                if(y-1>=0) ret.push_back({x-1,y-1});
                if(y+1<=7) ret.push_back({x-1,y+1});
            }
            if(x+1<=7)
            {
                ret.push_back({x+1,y});
                if(y-1>=0) ret.push_back({x+1,y-1});
                if(y+1<=7) ret.push_back({x+1,y+1});
            }
            if(y-1>=0) ret.push_back({x,y-1});
            if(y+1<=7) ret.push_back({x,y+1});
        break;
    }
}