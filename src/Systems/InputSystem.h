#pragma once
#include <set>

#include "basesystem.h"
#include "../Engine.h"

class InputSystem :
	public BaseSystem {
        

    public:
    	InputSystem();
    	~InputSystem();
    	void update();
        void init(Engine*);

        // shared_ptr<CameraSystem> cam;

    	SDL_Event mEvent;
        set<SDL_Keycode> keysDown;
    	vector<BaseSystem*> inputList;

        SDL_Point mousePosition;
        bool mouseLeft = true;

        bool mouseIsDown = false;

        Uint32 lastPressedTime = 0;

        bool isClicked(const char* key);
        bool isDown(const char* key);
};

