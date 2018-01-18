#pragma once

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

    Plant(SDL_Texture* tex, float x, float y);
    ~Plant();

    void Render(SDL_Renderer* ren, SDL_Rect* drawRect, int scale);
    void Update();

    float GetEaten(float amount);


    float GetAge() { return ageValue; }
    bool isDead() { return ageValue <= 0; }

};