#include "Noise.h"

Noise::Noise(){
    // double value = perlin.GetValue (1.25, 0.75, 0.5);

}

Noise::~Noise() {}


HeightMap* Noise::generateHeightMap(
    int width, int height, int seed, double scale, int octaves, double persistance, double lacunarity, Vector2D* offset) {

    HeightMap* heightMap = new HeightMap(width, height);

    Vector2D* octaveOffsets[octaves];
    for (int i = 0; i < octaves; i++ ) {
        // float offsetX = rand() % 100001 - 100000 + offset->x();
        // float offsetY = rand() % 100001 - 100000 + offset->y();

        float offsetX = offset->x();
        float offsetY = offset->y();

        Vector2D* temp = new Vector2D(offsetX, offsetY);

        octaveOffsets[i] = temp;
    }

    if (scale <= 0) {
        scale = .001;
    }

    double minNoiseHeight = 100.0; //std::numeric_limits<double>::max();
    double maxNoiseHeight = -100.0; //std::numeric_limits<double>::min();

    
    // cout << "Scale: " << to_string(scale) << endl;
    // cout << "Octaves: " << to_string(octaves) << endl;
    // cout << "Persistance: " << to_string(persistance) << endl;
    // cout << "Lacunarity: " << to_string(lacunarity) << endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            double amplitude = 1.0;
            double frequency = 1.0;

            double currentHeight = 0.0;

            for (int i = 0; i < octaves; i++) {
                double sampleX = x / scale * frequency + octaveOffsets[i]->x();
                double sampleY = y / scale * frequency + octaveOffsets[i]->y();

                double noiseVal = noiseModule.GetValue(sampleX, sampleY, 1.0);
                currentHeight += noiseVal * amplitude;

                amplitude *= persistance;
                frequency *= lacunarity;
            }

            if (currentHeight > maxNoiseHeight) { maxNoiseHeight = currentHeight; }
            else if (currentHeight < minNoiseHeight) { minNoiseHeight = currentHeight; }

            heightMap->setHeightAt(x, y, currentHeight);
        }
    }

    // cout << "Max Height: " << maxNoiseHeight << ", Min Height: " << minNoiseHeight << endl << endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double height = heightMap->getHeightAt(x, y);
            double newHeight = (height + abs(minNoiseHeight))  / (maxNoiseHeight - minNoiseHeight);

            heightMap->setHeightAt(x, y, newHeight);

        }
    }
    

    return heightMap;
}



