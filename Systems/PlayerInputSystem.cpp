#include "PlayerInputSystem.h"

PlayerInputSystem::PlayerInputSystem(){}

PlayerInputSystem::~PlayerInputSystem(){}

void PlayerInputSystem::update() {
	if (entityList.size() == 1) {
		ShipEntity* ship = (ShipEntity*) entityList[0];
		VelocityComponent *vel = (VelocityComponent*) ship->componentMap["velocity"];
		DimensionComponent *dim = (DimensionComponent*) ship->componentMap["dimension"];
		SDL_Event e;
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
					vel->mVelocity->y()--;
				}
				if (e.key.keysym.sym == SDLK_s) {
					vel->mVelocity->y()++;
				}
				if (e.key.keysym.sym == SDLK_a) {
					vel->mVelocity->x()--;
				}
				if (e.key.keysym.sym == SDLK_d) {
					vel->mVelocity->x()++;
				}
				if (e.key.keysym.sym == SDLK_SPACE) {
					int x = dim->getRect()->x + dim->getRect()->w;
					int y = dim->getRect()->y;
					mEngine->addEntity(new LaserEntity(mEngine->getNextId(), x, y));
				}
			}
			//If user clicks the mouse
			if (e.type == SDL_MOUSEBUTTONDOWN) {}
		}
	}
}
