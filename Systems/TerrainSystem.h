#pragma once
#include <SDL2/SDL.h>
#include <string>

#include "basesystem.h"
#include "CameraSystem.h"

#include "../TerrainGenerator/Noise.h"
#include "../TerrainGenerator/HeightMap.h"
#include "../TerrainGenerator/MapChunk.h"
#include "../TerrainGenerator/Island.h"
#include "../Texture.h"

class TerrainSystem : public BaseSystem
{
public:
    TerrainSystem(int, int);//, const char* background_file);
    ~TerrainSystem();

    void update();

    map<pair<int, int>, shared_ptr<Island>> islands;
    

private:
    void MakeIsland(int x, int y);
    void MorphLand(shared_ptr<MapChunk> chunk, SDL_Point point, bool raise);

    const int chunksPerIsland = 50 * 50;
    const float morphPowerMod = .005;

    int islandWidth;
    int islandHeight;

    SDL_Rect landMorphBox = {0, 0, 150, 150};
};

