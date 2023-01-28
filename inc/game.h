#include <piece.h>

enum frameColour{none, blue, green, red};

class Game
{
    public:
    Game();
    void run();
    private:
    void update();
    void render();
    bool input();
    bool isRunning;
    bool clickLimiter;
    bool whiteTurn;
    int square[8][8];
    frameColour frames[8][8];
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture[12];
    std::vector<Piece> pieces;
    std::vector<SDL_Point> pm;
    std::vector<SDL_Point> gs;
    std::vector<SDL_Point> rs;
    SDL_Rect squareShape;
    SDL_Rect dst;
    SDL_Point mouse;
    SDL_Point clicked;
    SDL_Point clickedP;
};