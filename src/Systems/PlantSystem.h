#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <random>

#include "basesystem.h"
#include "TerrainSystem.h"
#include "InputSystem.h"

class TerrainSystem;
class InputSystem;

#include "../Entities/Plant.h"

class PlantSystem : public BaseSystem
{
public:
    PlantSystem();//, const char* background_file);
    ~PlantSystem();

    void update();
    void init(Engine*);

    shared_ptr<TerrainSystem> terrain;

    vector<shared_ptr<Plant>> GetPlantsInRect(SDL_Rect* rect);
    void KillPlant(shared_ptr<Plant> plant);
    //void CreatePlantTemplate(SDL_Renderer* ren, int width, int height);

    shared_ptr<Plant> GetPlantFromPoint(float x, float y);

    bool hasTemplate = false;

private:
    vector<shared_ptr<Plant>> plants;
    vector<shared_ptr<Plant>> plantsToRemove;

    const int plantWidth = 512;
    const int plantHeight = 512;

    SDL_Texture* plantTemplate = nullptr;


};

