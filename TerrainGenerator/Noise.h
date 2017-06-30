#pragma once

#include <iostream>
#include <string>
#include <cmath>
// #include <vector>
#include <random>

#include <SDL2/SDL.h>
#include <noise/noise.h>

#include "../Vector2D.h"
#include "HeightMap.h"

using namespace std;

static std::mt19937 Generator;

class Noise
{
    public:
        Noise(int minSeed, int maxSeed);
        Noise(int seed);
        ~Noise();
        float getRandom(float min, float max);
        int getRandom(int min, int max);
        HeightMap* generateHeightMap(int width, int height, Vector2D* offset, SDL_Rect* islandBounds);
        HeightMap* generateSubMap(HeightMap* original, SDL_Rect* region);
        bool updateSubMap(HeightMap* original, HeightMap* submap, SDL_Rect* region);

        float scale = 100.0;
        int octaves = 5;
        float persistance = .5;
        float lacunarity = 2.0;

        bool falloff = true;
        int seed;

    private:
        noise::module::Perlin noiseModule;
        // noise::module::Voronoi noiseModule;

        float clamp(float x, float upper, float lower);
};