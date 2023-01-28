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
    SDL_Window* window;
    SDL_Renderer* renderer;
};