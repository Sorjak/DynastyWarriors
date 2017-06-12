#pragma once

#include <iostream>

class HeightMap {
    private:
        int width = 0;
        int height = 0;

        double* values;

    public:
        HeightMap(int width, int height);
        HeightMap(int width, int height, double* heights);
        ~HeightMap();

        double* getValues();
        void setHeightAt(int x, int y, double value);
        double getHeightAt(int x, int y);

        int getMapWidth();
        int getMapHeight();
};