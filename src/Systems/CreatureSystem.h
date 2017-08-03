#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <random>

#include "basesystem.h"
#include "TerrainSystem.h"
#include "InputSystem.h"

class TerrainSystem;
class InputSystem;

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

    vector<shared_ptr<Creature>> GetCreaturesInRect(SDL_Rect* rect);

private:
    vector<shared_ptr<Creature>> creatures;

    const int creatureWidth = 512;
    const int creatureHeight = 512;

};

