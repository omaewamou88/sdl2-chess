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
    int square[8][8];
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture[12];
    std::vector<Piece> pieces;
    SDL_Rect squareShape;
    SDL_Rect dst;
};