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
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: velocity->y() -= y_velocity; motion->isOnGround = false; break;
			case SDLK_s: break;
			case SDLK_a: velocity->x() -= x_velocity; break;
			case SDLK_d: velocity->x() += x_velocity; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: break;
			case SDLK_s: break;
			case SDLK_a: velocity->x() += x_velocity; break;
			case SDLK_d: velocity->x() -= x_velocity; break;
			}
		}

		const Uint8 *kbstate = SDL_GetKeyboardState(NULL);

		if (kbstate[SDL_SCANCODE_D]) {
			velocity->x() += x_velocity;
		}

		if (kbstate[SDL_SCANCODE_A]){
			velocity->x() -= x_velocity;
		}
		
		if (!kbstate[SDL_SCANCODE_D] && !kbstate[SDL_SCANCODE_A]) {
			if (velocity->x() > 0)
				velocity->x() -= x_velocity;
			if (velocity->x() < 0)
				velocity->x() += x_velocity;
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

