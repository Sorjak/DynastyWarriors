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
			if (mEvent.key.keysym.sym == SDLK_q) {
				mEngine->setRunning(false);
			}
		}
		//If user clicks the mouse
		if (mEvent.type == SDL_MOUSEBUTTONDOWN) {}


		
	}

	for (size_t i = 0; i < inputList.size(); i++) {
		PlayerInputSystem* pi = (PlayerInputSystem*)inputList[i];
		pi->process(mEvent);
	}
}
