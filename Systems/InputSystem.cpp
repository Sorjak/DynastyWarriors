#include "InputSystem.h"

InputSystem::InputSystem() {}

InputSystem::~InputSystem() {}

void InputSystem::update() {
	//Event polling
	while (SDL_PollEvent(&mEvent)){
		//If user closes he window
		if (mEvent.type == SDL_QUIT) {
			mEngine->setRunning(false);
		}

		//If user presses any key
		if (mEvent.type == SDL_KEYDOWN) {
			CameraSystem* cam = (CameraSystem*) mEngine->getSystem("camera");
			SDL_Point delta = {0, 0};

            if (mEvent.key.keysym.sym == SDLK_q) {
                mEngine->setRunning(false);
            }

            if (mEvent.key.keysym.sym == SDLK_a) {
                delta.x -= 10;
            }

            if (mEvent.key.keysym.sym == SDLK_d) {
                delta.x += 10;
            }

            if (mEvent.key.keysym.sym == SDLK_w) {
                delta.y -= 10;
            }

            if (mEvent.key.keysym.sym == SDLK_s) {
                delta.y += 10;
            }

            cam->moveView(delta);
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

		for (size_t i = 0; i < inputList.size(); i++) {
			PlayerInputSystem* pi = (PlayerInputSystem*)inputList[i];
			pi->process(mEvent);
		}
		
	}


}
