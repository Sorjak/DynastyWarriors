#pragma once

#include <iostream>
#include <vector>
#include <map>
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

        SDL_Point position;
        SDL_Point coord;

        map<pair<int, int>, shared_ptr<MapChunk>> chunks;
        vector<shared_ptr<MapChunk>> chunksVisible;

        int chunksPerLine = 0;

        int chunksToLoad = 0;

        shared_ptr<Noise> noise;

		SDL_Texture* islandTex;

        SDL_Color black;
		SDL_Color deep_water;
		SDL_Color water;
		SDL_Color sand;
		SDL_Color grass;
		SDL_Color mountain;
		SDL_Color snow;

    public:
        Island(SDL_Rect rect, shared_ptr<Noise> n, int totalChunks);
        ~Island();

		bool hasTexture = false;

        // void Render(SDL_Renderer* ren);
        void Update(SDL_Rect* area, int scale);
        void Render(SDL_Renderer* ren, SDL_Rect* area, int scale);

        void LoadChunk(shared_ptr<MapChunk> chunk);

        shared_ptr<MapChunk> FindChunk(float low, float high);
        shared_ptr<MapChunk> GetChunkAtPoint(SDL_Point point);
        vector<shared_ptr<MapChunk>> GetChunksInRect(SDL_Rect* area, int scale);

        int getWidth();
        int getHeight();

        void AddChunk(SDL_Rect chunkRect);
        shared_ptr<MapChunk> GetChunkFromCoord(int x, int y);
        shared_ptr<MapChunk> GetChunkFromPosition(int x, int y);

		void UpdateTexture(shared_ptr<MapChunk> chunk);

        SDL_Rect getLocalRect();
        SDL_Rect getWorldRect();
        SDL_Rect getScaledWorldRect(int scale);
};