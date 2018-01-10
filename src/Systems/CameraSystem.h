#pragma once
#include <cmath>

#include "basesystem.h"
#include "InputSystem.h"
class InputSystem;

class CameraSystem : public BaseSystem
{

private:
    const int moveAmount = 10;
    shared_ptr<InputSystem> input;

public:
    CameraSystem(int, int);
    ~CameraSystem();

    void update();
    void init(Engine* e);

    void moveView(SDL_Point delta);

	SDL_Rect view;
    int scale;
};