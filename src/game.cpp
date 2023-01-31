#include <game.h>
#define REFRESH 30

Game::Game()
{
    window = SDL_CreateWindow("sdl2-chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    squareShape.w = squareShape.h = 100;
    dst.w = dst.h = 80;
    texture[0] = IMG_LoadTexture(renderer, "res/black_pawn.png");
    texture[1] = IMG_LoadTexture(renderer, "res/black_rook.png");
    texture[2] = IMG_LoadTexture(renderer, "res/black_knight.png");
    texture[3] = IMG_LoadTexture(renderer, "res/black_bishop.png");
    texture[4] = IMG_LoadTexture(renderer, "res/black_queen.png");
    texture[5] = IMG_LoadTexture(renderer, "res/black_king.png");
    texture[6] = IMG_LoadTexture(renderer, "res/white_pawn.png");
    texture[7] = IMG_LoadTexture(renderer, "res/white_rook.png");
    texture[8] = IMG_LoadTexture(renderer, "res/white_knight.png");
    texture[9] = IMG_LoadTexture(renderer, "res/white_bishop.png");
    texture[10] = IMG_LoadTexture(renderer, "res/white_queen.png");
    texture[11] = IMG_LoadTexture(renderer, "res/white_king.png");
    for(int i=0;i<32;i++)
    {
        int ity = floor(i/8)==1||floor(i/8)==2?0:(i%8<5?i%8+1:8-(i%8));
        pieceType ty;
        switch(ity)
        {
            case 0: ty = pieceType::pawn; break;
            case 1: ty = pieceType::rook; break;
            case 2: ty = pieceType::knight; break;
            case 3: ty = pieceType::bishop; break;
            case 4: ty = pieceType::queen; break;
            case 5: ty = pieceType::king; break;
        }
        SDL_Point dp = {i%8, (int)(floor(i/8)>1?floor(i/8)+4:floor(i/8))};
        pieces.push_back(Piece(ty, i<16?false:true, dp));
    }
}

void Game::run()
{
    isRunning = true;
    unsigned int timeValue = 0;
    unsigned int deltaTime = 0;
    clickLimiter = true;
    whiteTurn = true;
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) frames[i][j] = frameColour::none;
    render();
    while(isRunning)
    {
        timeValue = SDL_GetTicks();
        if(input()) {update(); render();}
        deltaTime = SDL_GetTicks() - timeValue;
        if(deltaTime<1000/REFRESH) SDL_Delay(1000/REFRESH-deltaTime);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    getch();
}

bool Game::input()
{
    SDL_Event e; SDL_PollEvent(&e); if(e.type==SDL_QUIT) isRunning = false;
    if(SDL_GetMouseState(&mouse.x, &mouse.y)&SDL_BUTTON(SDL_BUTTON_LEFT))
    {   
        if(clickLimiter)
        {
            clickedP = clicked;
            clicked.x = floor(mouse.x/100); clicked.y = floor(mouse.y/100);
            clickLimiter = false;
            return true;
        }
    }
    else
    {
        clickLimiter = true;
        return false;
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 41, 41, 24, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 227, 227, 154, 255);
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) if(i%2==j%2)
    {
        squareShape.x = i*100; squareShape.y = j*100;
        SDL_RenderFillRect(renderer, &squareShape);
    }

    for(Piece piece : pieces)
    {
        dst.x = piece.getPos().x*100+10;
        dst.y = piece.getPos().y*100+10;
        SDL_RenderCopy(renderer, texture[piece.getTxt()], NULL, &dst);
    }

    for(int i=0;i<8;i++) for(int j=0;j<8;j++)
    {
        switch(frames[i][j])
        {
            case none: break;
            break;
            case red:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            squareShape.x = i*100; squareShape.y = j*100;
            SDL_RenderDrawRect(renderer, &squareShape);
            break;
            case green:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            squareShape.x = i*100; squareShape.y = j*100;
            SDL_RenderDrawRect(renderer, &squareShape);
            break;
            case blue:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            squareShape.x = i*100; squareShape.y = j*100;
            SDL_RenderDrawRect(renderer, &squareShape);
            break;
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::update()
{
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) square[i][j] = -1;
    int k = 0;
    for(Piece piece : pieces)
    {
        square[piece.getPos().x][piece.getPos().y] = k;
        k++;
    }
    k = 0;

    if(frames[clicked.x][clicked.y]==frameColour::green)
    {
        pieces[square[clickedP.x][clickedP.y]].setPos(clicked);
        if(square[clicked.x][clicked.y]!=-1)
        {
            if(pieces[square[clicked.x][clicked.y]].getType()==pieceType::king) lose(pieces[square[clicked.x][clicked.y]].isColourWhite());
            pieces.erase(pieces.begin()+square[clicked.x][clicked.y]);
        }
        whiteTurn = !whiteTurn;
        k = 1;
    }

    for(int i=0;i<8;i++) for(int j=0;j<8;j++) frames[i][j] = frameColour::none;
    frames[clicked.x][clicked.y] = frameColour::blue;
    pm.clear();
    gs.clear();
    rs.clear();

    if(square[clicked.x][clicked.y]!=-1&&pieces[square[clicked.x][clicked.y]].isColourWhite()==whiteTurn&&k==0)
    {
        int m[8][8];
        for(int i=0;i<8;i++) for(int j=0;j<8;j++)
            m[i][j]=
            square[i][j]==-1?0:(pieces[square[i][j]].isColourWhite()==pieces[square[clicked.x][clicked.y]].isColourWhite()?1:2);
        pm = pieces[square[clicked.x][clicked.y]].getPossibleMoves(m);
    }
    
    for(SDL_Point move : pm)
    {
        if(pieces[square[move.x][move.y]].isColourWhite()==pieces[square[clicked.x][clicked.y]].isColourWhite()&&
        square[move.x][move.y]!=-1)
        {
            rs.push_back(move);
        }
        else gs.push_back(move);
    }

    for(SDL_Point grSq : gs)
    {
        frames[grSq.x][grSq.y] = frameColour::green;
    }

    for(SDL_Point reSq : rs)
    {
        frames[reSq.x][reSq.y] = frameColour::red;
    }
}

void Game::lose(bool iw)
{
    std::cout << (iw?"Black Wins":"White Wins") << "\n";
    isRunning = false;
}