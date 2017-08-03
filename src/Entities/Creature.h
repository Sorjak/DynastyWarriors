#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

#include <SDL2/SDL.h>
#include <noise/noise.h>

#include "../Utils.h"

class Creature {

public:
    int creatureWidth;
    int creatureHeight;

    SDL_Point position;

    SDL_Rect bodyBounds;
    SDL_Texture* texture = nullptr;

    noise::module::Perlin noiseModule;

    Creature(int w, int h);
    Creature(SDL_Texture* tex);
    Creature(SDL_Texture* tex, int w, int h);
    ~Creature();

    void Render(SDL_Renderer* ren, SDL_Rect* drawRect);
    void MoveTo(int x, int y);

    void GenerateBody();
    void MakeSprite(SDL_Renderer* ren);
};