#include "PlayerInputSystem.h"

PlayerInputSystem::PlayerInputSystem(){}
PlayerInputSystem::~PlayerInputSystem(){}

void PlayerInputSystem::update() {}

void PlayerInputSystem::process(SDL_Event e) {
	if (entityList.size() == 1) {
		FighterEntity* fighter = (FighterEntity*)entityList[0];
		VelocityComponent *vel = (VelocityComponent*)fighter->componentMap["velocity"];
		DimensionComponent *dim = (DimensionComponent*)fighter->componentMap["dimension"];
		PlayerMotionComponent *motion = (PlayerMotionComponent*)fighter->componentMap["player_motion"];

		int x_velocity = motion->xVelocity;
		int y_velocity = motion->yVelocity;
		Vector2D* velocity = vel->getVelocity();

		//If a key was pressed
		if (e.type == SDL_KEYDOWN)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
				case SDLK_w: 
					jump(velocity, motion); 
					break;
				case SDLK_d:
					velocity->x() = motion->xVelocity;
					break;
				case SDLK_a:
					velocity->x() = -motion->xVelocity;
					break;
			}
		}
		SDL_PumpEvents();
		const Uint8 *kbstate = SDL_GetKeyboardState(NULL);

		if (kbstate[SDL_SCANCODE_D]) {
			velocity->x() = x_velocity;
		}

		if (kbstate[SDL_SCANCODE_A]){
			velocity->x() = -x_velocity;
		}
		
		//If user presses any key
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_SPACE) {
				int x = dim->getRect()->x + dim->getRect()->w;
				int y = dim->getRect()->y;
				mEngine->addEntity(new LaserEntity(mEngine->getNextId(), x, y));
			}
		}
	}
}

void PlayerInputSystem::jump(Vector2D* velocity, PlayerMotionComponent* motion) {
	if (motion->jumpsLeft > 0) {
		velocity->y() -= motion->yVelocity; 
		motion->isOnGround = false; 
		motion->jumpsLeft--;
	}
}

