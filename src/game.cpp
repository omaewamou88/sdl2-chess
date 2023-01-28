#include <game.h>

Game::Game()
{
    window = SDL_CreateWindow("sdl2-chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::run()
{
    
}

bool Game::input()
{
    
}

void Game::render()
{
    
}

void Game::update()
{
    
}