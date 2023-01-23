#include <game.h>
#define REFRESH 30

Game::Game()
{
    window = SDL_CreateWindow("sdl2-chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    square.w = square.h = 100;
    dst.w = dst.h = 80;
    dst.x = dst.y = 10;
    texture[0] = IMG_LoadTexture(renderer, "res/white_pawn.png");
    texture[1] = IMG_LoadTexture(renderer, "res/white_rook.png");
    texture[2] = IMG_LoadTexture(renderer, "res/white_knight.png");
    texture[3] = IMG_LoadTexture(renderer, "res/white_bishop.png");
    texture[4] = IMG_LoadTexture(renderer, "res/white_queen.png");
    texture[5] = IMG_LoadTexture(renderer, "res/white_king.png");
    texture[6] = IMG_LoadTexture(renderer, "res/black_pawn.png");
    texture[7] = IMG_LoadTexture(renderer, "res/black_rook.png");
    texture[8] = IMG_LoadTexture(renderer, "res/black_knight.png");
    texture[9] = IMG_LoadTexture(renderer, "res/black_bishop.png");
    texture[10] = IMG_LoadTexture(renderer, "res/black_queen.png");
    texture[11] = IMG_LoadTexture(renderer, "res/black_king.png");
    for(int i = 0; i<2; i++)
    {
        for(int j = 0; j<16; j++)
        {
            piece[i][j].type = j<8?pieceType::pawn:(j==8||j==15?pieceType::rook:(j==9||j==14?pieceType::knight
                                :(j==10||j==13?pieceType::bishop:(j==11?pieceType::queen:pieceType::king))));
            piece[i][j].isWhite = i==0?true:false;
            piece[i][j].x = j%8;
            switch((int)floor((j+(i*16))/8))
            {
                case 0: piece[i][j].y = 6; break;
                case 1: piece[i][j].y = 7; break;
                case 2: piece[i][j].y = 1; break;
                case 3: piece[i][j].y = 0; break;
            }
        }
    }
    for(int i = 0; i<8; i++) {for(int j = 0; j<8; j++) colour[i][j] = frameColour::none;}
    cl = false;
}

void Game::run()
{
    isRunning = true;
    whiteTurn = true;
    int timeValue = 0;
    int deltaTime = 0;
    render();
    while(isRunning)
    {
        timeValue = SDL_GetTicks();
        if(input()) {update(); render();}
        deltaTime = SDL_GetTicks() - timeValue;
        if(deltaTime<1000/REFRESH) SDL_Delay(1000/REFRESH-deltaTime);
    }
    /*SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();*/
    //for some reasons these three lines doesn't work
}

bool Game::input()
{
    SDL_Event event; SDL_PollEvent(&event); if(event.type==SDL_QUIT) isRunning = false;
    if(SDL_GetMouseState(&mouse.x, &mouse.y)&SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        if(!cl)
        {
        std::cout<<"clicked\n";
        wasClicked = isClicked;
        isClicked.x = floor(mouse.x/100); isClicked.y = floor(mouse.y/100);
        cl = true;
        return true;
        }
    }
    else
    {
        cl = false;
        return false;
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 227, 227, 154, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 41, 41, 24, 255);
    for(int i = 0; i<8; i++)
    {
        for(int j = 0; j<8; j++)
        {
            square.x = j*100; square.y = i*100;
            if(i%2==j%2) SDL_RenderFillRect(renderer, &square);
        }
    }

    for(int i = 0; i<2; i++)
    {
        for(int j = 0; j<16; j++)
        {
            if(piece[i][j].exists)
            {
            dst.x = (piece[i][j].x*100)+10; dst.y = (piece[i][j].y*100)+10;
            SDL_RenderCopy(renderer, texture[piece[i][j].type+(piece[i][j].isWhite?0:6)], NULL, &dst);
            }
        }
    }

    for(int i = 0; i<8; i++) for(int j = 0; j<8; j++)
    {
        switch(colour[i][j])
        {
            case none: break;
            case blue: 
                square.x = i*100; square.y = j*100;
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); SDL_RenderDrawRect(renderer, &square); 
            break;
            case green:
                square.x = i*100; square.y = j*100;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); SDL_RenderDrawRect(renderer, &square);
            break;
            case red:
                square.x = i*100; square.y = j*100;
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); SDL_RenderDrawRect(renderer, &square);
            break;
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::update()
{
    if(colour[isClicked.x][isClicked.y]==frameColour::green)
    {
        for(int i = 0; i<16; i++) if(piece[whiteTurn?0:1][i].x==wasClicked.x&&piece[whiteTurn?0:1][i].y==wasClicked.y)
        {
            piece[whiteTurn?0:1][i].x=isClicked.x;
            piece[whiteTurn?0:1][i].y=isClicked.y;
            for(int j = 0; j<16; j++) if(piece[whiteTurn?1:0][j].x==isClicked.x&&piece[whiteTurn?1:0][j].y==isClicked.y)
                piece[whiteTurn?1:0][j].exists = false;
            whiteTurn = !whiteTurn;
        }
    }

    rp.clear(); gp.clear(); pm.clear();
    for(int i = 0; i<8; i++) for(int j = 0; j<8; j++) colour[i][j] = frameColour::none;

    for(int i = 0; i<16; i++) if(piece[whiteTurn?0:1][i].x==isClicked.x&&piece[whiteTurn?0:1][i].y==isClicked.y)
        pm = piece[whiteTurn?0:1][i].getPossibleMoves();

    for(int i = 0; i<pm.size(); i++) for(int j = 0; j<16; j++) 
        if(piece[whiteTurn?0:1][j].x==pm[i].x&&piece[whiteTurn?0:1][j].y==pm[i].y) rp.push_back({pm[i].x,pm[i].y});
        else gp.push_back({pm[i].x,pm[i].y});
    for(int i = 0; i<gp.size(); i++) colour[gp[i].x][gp[i].y] = frameColour::green;
    for(int i = 0; i<rp.size(); i++) colour[rp[i].x][rp[i].y] = frameColour::red;

    colour[isClicked.x][isClicked.y] = frameColour::blue;
}