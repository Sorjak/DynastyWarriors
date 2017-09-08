#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

#include <SDL2/SDL.h>
// #include <noise/noise.h>
#include <tinyfsm.hpp>

// #include "CreatureState.h"
#include "Plant.h"
#include "../Utils.h"
// #include "../Vector2D.h"

void GenerateBody(int width, int height, bool* bodyPoints, SDL_Rect* bounds);
SDL_Texture* MakeSprite(SDL_Renderer* ren, int fullWidth, bool* bodyPoints, SDL_Rect* bounds);

/* EVENTS */

struct CreatureEvent : tinyfsm::Event {
    string name;
};

struct GotHungry    : CreatureEvent { };
struct DoneEating   : CreatureEvent { };
struct BeginEating  : CreatureEvent { };


class Creature : public tinyfsm::Fsm<Creature>{

private:
    bool hasTexture = false;
    float hungerValue = 0;
    float matingValue = 0;
    float ageValue = 0;

    float speed = 1.0;

    Vector2 target;
    // shared_ptr<Plant> nearestPlant = nullptr;
    // CreatureState state;


public:
    int creatureWidth;
    int creatureHeight;

    string name = "";

    // SDL_Point position;
    Vector2 position;

    SDL_Rect bodyBounds;
    SDL_Texture* texture = nullptr;

    Creature() {};

    Creature(SDL_Texture* tex, int x, int y);
    ~Creature();

    void react(tinyfsm::Event const &) { };

    virtual void react(GotHungry    const &);
    virtual void react(DoneEating   const &);
    virtual void react(BeginEating  const &);

    virtual void entry(void) { };  /* entry actions in some states */
    void         exit(void)  { };  /* no exit actions at all */

    void Render(SDL_Renderer* ren, SDL_Rect* drawRect);
    void Update();

    void MoveTo(int x, int y);
    void Eat(float amount);
    // void Wander();

    float GetHunger() { return hungerValue; }
    // bool isHungry() { return hungerValue > 50; };
    // bool isOld() { return ageValue >= 100; };
    // bool isEating() { return position.distance(target) < 2; }

};




