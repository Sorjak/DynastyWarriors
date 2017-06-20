#pragma once

#include <iostream>

class HeightMap {
    private:
        int width = 0;
        int height = 0;

        float* values;

    public:
        HeightMap(int width, int height);
        HeightMap(int width, int height, float* heights);
        ~HeightMap();

        float* getValues();
        void setHeightAt(int x, int y, float value);
        float getHeightAt(int x, int y);

        int getMapWidth();
        int getMapHeight();
};