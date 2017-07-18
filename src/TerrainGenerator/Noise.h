#pragma once

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <memory>

#include <SDL2/SDL.h>
#include <noise/noise.h>

#include "../Vector2D.h"
#include "HeightMap.h"

using namespace std;

static std::mt19937 Generator;

class Noise
{
    public:
        Noise(int seed, float persistance, float lacunarity, float scale);
        ~Noise();
        float getRandom(float min, float max);
        int getRandom(int min, int max);

        shared_ptr<HeightMap> generateHeightMap(int width, int height, SDL_Point offset, SDL_Rect* islandBounds);
        
        shared_ptr<HeightMap> generateSubMap(shared_ptr<HeightMap> original, SDL_Rect* region);
        bool updateSubMap(shared_ptr<HeightMap> original, shared_ptr<HeightMap> submap, SDL_Rect* region);

        int seed;
        float scale;
        float persistance;
        float lacunarity;

        bool falloff = true;
        
    private:
        noise::module::Perlin noiseModule;
        // noise::module::Voronoi noiseModule;

        float clamp(float x, float upper, float lower);
};