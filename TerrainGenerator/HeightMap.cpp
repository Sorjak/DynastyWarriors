#include "HeightMap.h"

HeightMap::HeightMap(int width, int height) {
    this->width = width;
    this->height = height;

    this->values = new double[width * height];
}

HeightMap::HeightMap(int width, int height, double* heights) {
    this->width = width;
    this->height = height;
    this->values = heights;

}

HeightMap::~HeightMap() {}


double* HeightMap::getValues() {
    return this->values;
}


void HeightMap::setHeightAt(int x, int y, double value) {
    this->values[x + this->width * y] = value;

    // std::cout << "Setting [" << x << ", " <<  y << "] to : " << value << std::endl;
}

double HeightMap::getHeightAt(int x, int y) {
    return this->values[x + this->width * y];
}

int HeightMap::getMapWidth() {
    return this->width;
}

int HeightMap::getMapHeight() {
    return this->height;
}

