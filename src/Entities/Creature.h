#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

#include <SDL2/SDL.h>
// #include <noise/noise.h>

#include "../Utils.h"
// #include "../Vector2D.h"

void GenerateBody(int width, int height, bool* bodyPoints, SDL_Rect* bounds);
SDL_Texture* MakeSprite(SDL_Renderer* ren, int fullWidth, bool* bodyPoints, SDL_Rect* bounds);

class Creature {

private:
    bool hasTexture = false;
    float hungerValue = 0;
    float matingValue = 0;
    float ageValue = 0;

    float speed = 1.0;

    Vector2 target;


public:
    int creatureWidth;
    int creatureHeight;

    // SDL_Point position;
    Vector2 position;

    SDL_Rect bodyBounds;
    SDL_Texture* texture = nullptr;

    Creature(SDL_Texture* tex, int x, int y);
    ~Creature();

    void Render(SDL_Renderer* ren, SDL_Rect* drawRect);
    void Update();

    void MoveTo(int x, int y);
};