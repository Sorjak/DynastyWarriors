#pragma once

#include <iostream>
#include <memory>
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

        SDL_Point localPosition;
        SDL_Point worldPosition;
        SDL_Point coord;
        Texture* chunkTex = NULL;
        shared_ptr<HeightMap> heightMap;

        bool selected = false;

        bool ocean = false;



    public:
        // bool loadingHeightMap = false;
        bool hasHeightMap = false;
        bool hasTexture = false;
        bool updateHeightMap = false;

        bool dirty = false;

        MapChunk(SDL_Rect rect, SDL_Rect islandBounds);
        ~MapChunk();

        void Load(shared_ptr<HeightMap> heightMap);

        void Render(SDL_Renderer*, int offsetX, int offsetY);

        void Select(bool val);

        std::string getName();

        shared_ptr<HeightMap> getHeightMap();

		float getHeightAt(int x, int y);

        int getWidth();
        int getHeight();
        SDL_Point getLocalPosition();
        SDL_Point getWorldPosition();

        SDL_Rect getLocalRect();
        SDL_Rect getWorldRect();
};