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

    const int chunksPerIsland = 100 * 100;
    const float islandSizeMod = 5;
    const float morphPowerMod = .005;
    const int maxThreads = 3;

    vector<shared_ptr<Island>> getIslandsInRect(SDL_Rect* view_rect, int scale);
    shared_ptr<Island> getIslandFromCoord(int x, int y);
    shared_ptr<Island> getIslandFromPoint(int x, int y);
    shared_ptr<MapChunk> getChunkFromPoint(int x, int y);

    float GetElevationAtPoint(int x, int y);
    shared_ptr<MapChunk> getCurrentChunk();
    string getCurrentChunkInfo();

    map<pair<int, int>, shared_ptr<Island>> islands;
    vector<shared_ptr<Island>> islandsInView;

    shared_ptr<CameraSystem> cam;
    shared_ptr<InputSystem> input;

private:
    int islandWidth;
    int islandHeight;
    int currentThreads;

    queue<pair<int, int>> islandsToGenerate;
    set<pair<int, int>> islandsGenerating;

    SDL_Rect landMorphBox;
    shared_ptr<MapChunk> currentChunk;

    void GenerateIsland(int x, int y);
    void MakeIsland(pair<int, int> coord, SDL_Rect islandBounds);
    void MorphLand(shared_ptr<MapChunk> chunk, SDL_Point point, bool raise);


};

