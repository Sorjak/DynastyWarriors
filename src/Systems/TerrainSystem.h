#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <random>

#include "basesystem.h"
#include "CameraSystem.h"
#include "InputSystem.h"

class CameraSystem;
class InputSystem;

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
    void init(Engine*);

    vector<shared_ptr<Island>> getIslandsInRect(SDL_Rect* view_rect);
    shared_ptr<Island> getIslandFromCoord(int x, int y);
    shared_ptr<Island> getIslandFromPoint(int x, int y);

    float GetElevationAtPoint(int x, int y);

    map<pair<int, int>, shared_ptr<Island>> islands;
    shared_ptr<CameraSystem> cam;
    shared_ptr<InputSystem> input;

    vector<shared_ptr<Island>> islandsInView;

private:
    void MakeIsland(int x, int y);
    void MorphLand(shared_ptr<MapChunk> chunk, SDL_Point point, bool raise);

    const int chunksPerIsland = 50 * 50;
    const float islandSizeMod = 2;
    const float morphPowerMod = .005;

    int islandWidth;
    int islandHeight;

    SDL_Rect landMorphBox;
};

