#pragma once

#include <iostream>
#include <vector>
#include <thread>

#include <SDL2/SDL.h>

#include "Noise.h"
#include "HeightMap.h"
#include "MapChunk.h"
#include "../Vector2D.h"
#include "../Texture.h"

class Island {
    private:
        int width = 0;
        int height = 0;

        Vector2D* position;
        Vector2D* coord;

        vector<MapChunk*> chunks;
        vector<MapChunk*> chunksVisible;

        int chunksToLoad = 0;

        Noise* noise;

    public:
        Island(SDL_Rect rect, Noise* n, int chunksPerLine);
        Island(SDL_Rect rect, Noise* n, vector<MapChunk*> chunks);
        ~Island();

        // void Render(SDL_Renderer* ren);
        void Update(SDL_Rect* area);
        void Render(SDL_Renderer* ren, SDL_Rect* area);

        void LoadChunk(MapChunk* chunk);

        MapChunk* GetChunkAtPoint(SDL_Point mousePos);
        vector<MapChunk*> GetChunksInRect(SDL_Rect* area);

        int getWidth();
        int getHeight();

        SDL_Rect getWorldRect();
};