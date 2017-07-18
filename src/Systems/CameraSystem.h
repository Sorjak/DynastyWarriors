#pragma once

#include "basesystem.h"

#include "../Engine.h"

class CameraSystem : public BaseSystem
{

private:
    int moveAmount = 10;

public:
    CameraSystem(int, int);
    ~CameraSystem();

    void update();

    void moveView(SDL_Point delta);

	SDL_Rect view;
};