#pragma once

#include <iostream>

class HeightMap {
    private:
        int width = 0;
        int height = 0;

        int maxValue = 0;
        int minValue = 0;

        float* values;

    public:
        HeightMap(int width, int height);
        HeightMap(int width, int height, float* heights);
        ~HeightMap();

        float* getValues();
        float getAverageValue();
        void setHeightAt(int x, int y, float value);
        float getHeightAt(int x, int y);

        int getMapWidth();
        int getMapHeight();
};