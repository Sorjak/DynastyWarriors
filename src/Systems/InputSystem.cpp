#include "InputSystem.h"

InputSystem::InputSystem() {}

InputSystem::~InputSystem() {}

void InputSystem::init(Engine* e) {
    mEngine = e;
}

void InputSystem::update() {
    mouseScroll = false;
    // mousePosition = {0, 0};
	//Event polling
	while (SDL_PollEvent(&mEvent)){

		//If user closes he window
		if (mEvent.type == SDL_QUIT) {
			mEngine->setRunning(false);
		}

		//If user presses any key
		if (mEvent.type == SDL_KEYDOWN) {
            keysDown.insert(mEvent.key.keysym.sym);
            lastPressedTime = SDL_GetTicks();
            // cout << "Inserting: " << SDL_GetKeyName(mEvent.key.keysym.sym) << endl;
        }

        if (mEvent.type == SDL_KEYUP) {
            keysDown.erase(mEvent.key.keysym.sym);
            // cout << "Removing: " << SDL_GetKeyName(mEvent.key.keysym.sym) << endl;
        }

        //If user clicks the mouse
        if (mEvent.type == SDL_MOUSEBUTTONDOWN) {
            mousePosition.x = mEvent.button.x;
            mousePosition.y = mEvent.button.y;
            mouseIsDown = true;

            mouseLeft = mEvent.button.button == SDL_BUTTON_LEFT;
        }

        if (mEvent.type == SDL_MOUSEBUTTONUP) {
            mouseIsDown = false;
        }

        if (mEvent.type == SDL_MOUSEMOTION && mouseIsDown) {
            mousePosition.x = mEvent.motion.x;
            mousePosition.y = mEvent.motion.y;
        }

        if (mEvent.type == SDL_MOUSEWHEEL) {
            mouseScroll = mEvent.wheel.y;
        }
		
	}
}

bool InputSystem::isClicked(const char* key) {
    return isDown(key) && !SDL_TICKS_PASSED(SDL_GetTicks(), lastPressedTime + 20);
}

bool InputSystem::isDown(const char* key) {
    SDL_Keycode kc = SDL_GetKeyFromName(key);

    return keysDown.count(kc) > 0;
}

bool InputSystem::isScrolling() {
    return mouseScroll != 0;
}
