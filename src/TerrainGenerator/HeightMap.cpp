#include "HeightMap.h"

HeightMap::HeightMap(int width, int height) {
    this->width = width;
    this->height = height;

    this->values = new float[width * height];
}

HeightMap::HeightMap(int width, int height, float* heights) {
    this->width = width;
    this->height = height;
    this->values = heights;

}

HeightMap::~HeightMap() {
    delete[] this->values;

}


float* HeightMap::getValues() {
    return this->values;
}

float HeightMap::getAverageValue() {
    float total = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float value = getHeightAt(x, y);
            total += value;
        }
    }

    return total / (width * height);
}


void HeightMap::setHeightAt(int x, int y, float value) {
    this->values[x + this->width * y] = value;

    // std::cout << "Setting [" << x << ", " <<  y << "] to : " << value << std::endl;
}

float HeightMap::getHeightAt(int x, int y) {
    return this->values[x + this->width * y];
}

int HeightMap::getMapWidth() {
    return this->width;
}

int HeightMap::getMapHeight() {
    return this->height;
}

