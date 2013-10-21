#include "InputSystem.h"

InputSystem::InputSystem() {}

InputSystem::~InputSystem() {}

void InputSystem::update() {
	SDL_Event e;
	vector<const char*> input;
	//Event polling
    while (SDL_PollEvent(&e)){
        //If user closes he window
        if (e.type == SDL_QUIT)
			mEngine->setRunning(false);
        //If user presses any key
        if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_q) {
				mEngine->setRunning(false);
			}
			if (e.key.keysym.sym == SDLK_w) {
				input.push_back("w");
			}
			if (e.key.keysym.sym == SDLK_s) {
				input.push_back("s");
			}
			if (e.key.keysym.sym == SDLK_a) {
				input.push_back("a");
			}
			if (e.key.keysym.sym == SDLK_d) {
				input.push_back("d");
			}
			if (e.key.keysym.sym == SDLK_SPACE) {
				input.push_back("space");
			}
		}
        //If user clicks the mouse
		if (e.type == SDL_MOUSEBUTTONDOWN) {}
    }

	for (size_t i = 0; i < input.size(); i++) {
		const char* command = input[i];
		for (size_t j = 0; j < entityList.size(); j++) {
			InputComponent *in = (InputComponent*) entityList[j]->componentMap["input"];
			in->setInput(command, entityList[j]);
		}
	}
}
