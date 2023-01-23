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
    bool whiteTurn;
    bool cl;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture[12];
    SDL_Rect square;
    SDL_Rect dst;
    SDL_Point mouse;
    SDL_Point wasClicked{2,0};
    SDL_Point isClicked{2,0};
    std::vector<SDL_Point> pm;
    std::vector<SDL_Point> gp;
    std::vector<SDL_Point> rp;
    Piece piece[2][16];
    frameColour colour[8][8];
};