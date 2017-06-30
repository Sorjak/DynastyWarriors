#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "Noise.h"
#include "HeightMap.h"
#include "../Vector2D.h"
#include "../Texture.h"

class MapChunk {
    private:
        int width = 0;
        int height = 0;

        Vector2D* localPosition;
        Vector2D* worldPosition;
        Vector2D* coord;
        Texture* chunkTex = NULL;
        HeightMap* heightMap;

        bool selected = false;

    public:
        bool loadingHeightMap = false;
        bool hasHeightMap = false;
        bool hasTexture = false;


        MapChunk(SDL_Rect rect, SDL_Rect islandBounds);
        // MapChunk(SDL_Rect rect, Noise* n,  SDL_Rect islandBounds);
        MapChunk(int width, int height, HeightMap* hm);
        ~MapChunk();

        void Load(Noise* n, SDL_Rect islandBounds);

        void Render(SDL_Renderer*);
        void Render(SDL_Renderer*, int offsetX, int offsetY);

        void Select(bool val);

        string getName();

        int getWidth();
        int getHeight();
        SDL_Rect getLocalRect();
        SDL_Rect getWorldRect();
};