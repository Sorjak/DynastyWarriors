#pragma once
#include "basesystem.h"

#include "../Engine.h"
#include "CameraSystem.h"

class InputSystem :
	public BaseSystem {
        

    public:
    	InputSystem();
    	~InputSystem();

    	void update();

    	SDL_Event mEvent;
    	vector<BaseSystem*> inputList;

        SDL_Point mousePosition;
        bool mouseLeft = true;

        bool mouseIsDown = false;
};

