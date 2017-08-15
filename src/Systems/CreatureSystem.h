#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <random>

#include "basesystem.h"
#include "TerrainSystem.h"
#include "InputSystem.h"
#include "PlantSystem.h"

class TerrainSystem;
class InputSystem;
class PlantSystem;


#include "../Entities/Creature.h"

class CreatureSystem : public BaseSystem
{
public:
    CreatureSystem();//, const char* background_file);
    ~CreatureSystem();

    void update();
    void init(Engine*);

    shared_ptr<TerrainSystem> terrain;
    shared_ptr<InputSystem> input;
    shared_ptr<PlantSystem> plant;

    vector<shared_ptr<Creature>> GetCreaturesInRect(SDL_Rect* rect);
    void KillCreature(shared_ptr<Creature> creature);
    void CreateCreatureTemplate(SDL_Renderer* ren, int width, int height);

    bool hasTemplate = false;

private:
    vector<shared_ptr<Creature>> creatures;
    vector<shared_ptr<Creature>> creaturesToRemove;

    const int creatureWidth = 512;
    const int creatureHeight = 512;

    SDL_Texture* creatureTemplate = nullptr;


};

