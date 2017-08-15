#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

#include <SDL2/SDL.h>

#include "../Utils.h"


class Plant {

private:
    bool hasTexture = false;

    float ageValue = 1;


public:
    int plantWidth;
    int plantHeight;

    Vector2 position;

    SDL_Texture* texture = nullptr;

    Plant(SDL_Texture* tex, int x, int y);
    ~Plant();

    void Render(SDL_Renderer* ren, SDL_Rect* drawRect);
    void Update();

    float GetEaten(float amount);


    bool isDead() { return ageValue <= 0; }
};