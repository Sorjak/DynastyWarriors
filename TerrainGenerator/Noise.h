#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include <noise/noise.h>

#include "../Vector2D.h"
#include "HeightMap.h"

using namespace std;

class Noise
{
    public:
        Noise();
        ~Noise();

        HeightMap* generateHeightMap(int, int, int seed, double, int, double, double, Vector2D*);

    private:
        noise::module::Perlin noiseModule;
        // module::Voronoi noiseModule;
        int seed;
};