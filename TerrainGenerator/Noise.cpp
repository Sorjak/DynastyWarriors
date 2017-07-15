#include "Noise.h"

Noise::Noise(int minSeed, int maxSeed) {
    this->seed = getRandom(minSeed, maxSeed);
}

Noise::Noise(int seed) {
    this->seed = seed;
}

Noise::~Noise() {}


float Noise::getRandom(float min, float max) {
    static std::uniform_int_distribution<int> uid(min, max);
    return uid(Generator);
}

int Noise::getRandom(int min, int max) {
    static std::uniform_int_distribution<int> uid(min, max);
    return uid(Generator);
}

float Noise::clamp(float x, float lower, float upper) {
    return min(upper, max(x, lower));
}

HeightMap* Noise::generateHeightMap
    (int width, int height, SDL_Point offset, SDL_Rect* islandBounds) {

    // cout << "Generating height map" << endl;
    // cout << "Seed: " << to_string(seed) << endl;
    // cout << "Scale: " << to_string(scale) << endl;
    // cout << "Octaves: " << to_string(octaves) << endl;
    // cout << "Persistance: " << to_string(persistance) << endl;
    // cout << "Lacunarity: " << to_string(lacunarity) << endl;
    // cout << "Offset: x: " << offset->x() << ", y: " <<  offset->y() << endl;

    Generator.seed(seed);
    HeightMap* heightMap = new HeightMap(width, height);

    float maxPossibleHeight = 0;
    float amplitude = 1.0;
    float frequency = 1.0;

    float a = 3;
    float b = 2.0f;

    float minNoiseHeight = 100.0;
    float maxNoiseHeight = -100.0; 

	const int octaves = 5;

    SDL_Point octaveOffsets[octaves];
    for (int i = 0; i < octaves; i++ ) {
        float offsetX = getRandom(-10001, 10000) + offset.x;
        float offsetY = getRandom(-10001, 10000) + offset.y;

        octaveOffsets[i] = {(int) offsetX, (int) offsetY};

        maxPossibleHeight += amplitude;
        amplitude *= persistance;
    }

    float halfWidth = width / 2.0;
    float halfHeight = height / 2.0;

    for (int y = 0; y < height; y++) {    
        for (int x = 0; x < width; x++) {

            amplitude = 1;
            frequency = 1;

            float currentHeight = 0.0;

            for (int i = 0; i < octaves; i++) {
                float sampleX = (x - halfWidth + octaveOffsets[i].x) / (scale * frequency);
                float sampleY = (y - halfHeight + octaveOffsets[i].y) / (scale * frequency);

                float noiseVal = noiseModule.GetValue(sampleX, sampleY, 1.0);
                currentHeight += noiseVal * amplitude;

                amplitude *= persistance;
                frequency *= lacunarity;
            }

            if (currentHeight > maxNoiseHeight) { maxNoiseHeight = currentHeight; }
            else if (currentHeight < minNoiseHeight) { minNoiseHeight = currentHeight; }

            // Normalize and clamp resulting height
			float normalizedHeight = (currentHeight + 1) / (maxPossibleHeight);
            float clampedHeight = clamp(normalizedHeight, 0.0f, 100.0f);

            // Subtract falloff height from our current height
            if (falloff) {
                // Get x an y values between -1 and 1
                float i = ((offset.x + x) / (float) islandBounds->w) * 2 - 1;
                float j = ((offset.y + y) / (float) islandBounds->h) * 2 - 1;

                // cout << i << ", " << j << endl;
                // Which one is closer to the edge?
                float val = max(abs(i), abs(j));

                // Gradual increase curve from 0 to 1
                float falloffHeight = pow(val, a) / (pow(val, a) + pow(b - b * val, a));

				clampedHeight -= falloffHeight;
            }

            heightMap->setHeightAt(x, y, clampedHeight);
        }
    }

    // cout << "Max Possible Height: " << maxPossibleHeight << endl;
    // cout << "Max Height: " << maxNoiseHeight << ", Min Height: " << minNoiseHeight << endl << endl;

    return heightMap;
}

HeightMap* Noise::generateSubMap(HeightMap* original, SDL_Rect* region) {
    int mapWidth = region->w;
    int mapHeight = region->h;

    HeightMap* submap = new HeightMap(mapWidth, mapHeight);

    updateSubMap(original, submap, region);
    return submap;
}

bool Noise::updateSubMap(HeightMap* original, HeightMap* submap, SDL_Rect* region) {

    for (int y = 0; y < region->h; y++) {
        for (int x = 0; x < region->w; x++) {

            // Wrap region offset around original dimensions so we don't segfault
            int offsetX = (region->x + x) % original->getMapWidth();
            int offsetY = (region->y + y) % original->getMapHeight();

            float origHeight = original->getHeightAt(offsetX, offsetY);
            // float newHeight = noiseModule.GetValue(x, y, 1.0); //submap->getHeightAt(x, y);
            // float clampedHeight = clamp(origHeight + (newHeight / 1.0f), 0.0f, 100.0f);

            submap->setHeightAt(x, y, origHeight);
        }
    }

    return true;
}