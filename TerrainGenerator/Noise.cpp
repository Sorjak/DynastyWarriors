#include "Noise.h"

Noise::Noise(int seed) {
    this->seed = seed;

}
Noise::~Noise() {}

float Noise::getRandom(float min, float max) {
    static std::uniform_int_distribution<int> uid(min, max);
    return uid(Generator);
}

float Noise::clamp(float x, float lower, float upper) {
    return min(upper, max(x, lower));
}


HeightMap* Noise::generateHeightMap(
    int width, int height, Vector2D* offset) {

    cout << "Generating height map" << endl;
    cout << "Seed: " << to_string(seed) << endl;
    cout << "Scale: " << to_string(scale) << endl;
    cout << "Octaves: " << to_string(octaves) << endl;
    cout << "Persistance: " << to_string(persistance) << endl;
    cout << "Lacunarity: " << to_string(lacunarity) << endl;

    Generator.seed(seed);
    HeightMap* heightMap = new HeightMap(width, height);
    HeightMap* falloffMap = new HeightMap(width, height);

    float maxPossibleHeight = 0;
    float amplitude = 1.0;
    float frequency = 1.0;


    Vector2D* octaveOffsets[octaves];
    for (int i = 0; i < octaves; i++ ) {
        float offsetX = getRandom(-10001, 10000) + offset->x();
        float offsetY = getRandom(-10001, 10000) + offset->y();

        Vector2D* temp = new Vector2D(offsetX, offsetY);

        octaveOffsets[i] = temp;

        maxPossibleHeight += amplitude;
        amplitude *= persistance;
    }


    if (falloff) {
        float a = 3;
        float b = 2.2f;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {

                float i = x / width * 2 - 1;
                float j = y / height * 2 - 1;

                float val = max(abs(i), abs(j));

                float falloffHeight = pow(val, a) / (pow(val, a) + pow(b - b * val, a));

                falloffMap->setHeightAt(x, y, falloffHeight);

            }
        }
    }

    if (scale <= 0) {
        scale = .001;
    }

    float minNoiseHeight = 100.0; //std::numeric_limits<float>::max();
    float maxNoiseHeight = -100.0; //std::numeric_limits<float>::min();

    string progress = "";

    for (int y = 0; y < height; y++) {
        // cout << to_string(y) + " " << endl;
        
        for (int x = 0; x < width; x++) {

            amplitude = 1;
            frequency = 1;

            float currentHeight = 0.0;

            for (int i = 0; i < octaves; i++) {
                float sampleX = (x + octaveOffsets[i]->x()) / (scale * frequency);
                float sampleY = (y + octaveOffsets[i]->y()) / (scale * frequency);

                float noiseVal = noiseModule.GetValue(sampleX, sampleY, 1.0);
                currentHeight += noiseVal * amplitude;

                amplitude *= persistance;
                frequency *= lacunarity;
            }

            if (currentHeight > maxNoiseHeight) { maxNoiseHeight = currentHeight; }
            else if (currentHeight < minNoiseHeight) { minNoiseHeight = currentHeight; }

            // heightMap->setHeightAt(x, y, currentHeight);
            if (falloff) 
                currentHeight = currentHeight - falloffMap->getHeightAt(x, y);


            float normalizedHeight = (currentHeight + 1) / (maxPossibleHeight / 0.9f);
            float clampedHeight = clamp(normalizedHeight, 0.0f, 100.0f);

            heightMap->setHeightAt(x, y, clampedHeight);
        }
    }

    cout << "done" << endl;

    // cout << "Max Height: " << maxNoiseHeight << ", Min Height: " << minNoiseHeight << endl << endl;



    

    return heightMap;
}

HeightMap* Noise::generateSubMap(HeightMap* original, SDL_Rect* region) {
    int mapWidth = region->w; //original->getMapWidth();
    int mapHeight = region->h; //original->getMapHeight();

    // HeightMap* submap = generateHeightMap(mapWidth, mapHeight, new Vector2D(region->x, region->y));

    HeightMap* submap = new HeightMap(mapWidth, mapHeight);

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {

            int offsetX = region->x + x;// + (int)(x % region->w);
            int offsetY = region->y + y;// + (int)(y % region->h);

            float origHeight = original->getHeightAt(offsetX, offsetY);
            // float newHeight = noiseModule.GetValue(x, y, 1.0); //submap->getHeightAt(x, y);
            // float clampedHeight = clamp(origHeight + (newHeight / 1.0f), 0.0f, 100.0f);


            submap->setHeightAt(x, y, origHeight);
        }
    }

    return submap;


}

bool Noise::updateSubMap(HeightMap* original, HeightMap* submap, SDL_Rect* region) {
    int mapWidth = region->w; //original->getMapWidth();
    int mapHeight = region->h; //original->getMapHeight();

    // HeightMap* submap = generateHeightMap(mapWidth, mapHeight, new Vector2D(region->x, region->y));

    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {

            int offsetX = region->x + x;// + (int)(x % region->w);
            int offsetY = region->y + y;// + (int)(y % region->h);

            float origHeight = original->getHeightAt(offsetX, offsetY);
            // float newHeight = noiseModule.GetValue(x, y, 1.0); //submap->getHeightAt(x, y);
            // float clampedHeight = clamp(origHeight + (newHeight / 1.0f), 0.0f, 100.0f);


            submap->setHeightAt(x, y, origHeight);
        }
    }

    return true;

}



