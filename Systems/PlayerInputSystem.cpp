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
					jump(vel, motion); 
					break;
				case SDLK_d:
					vel->mFacing = 1;
					move(vel, motion);
					break;
				case SDLK_a:
					vel->mFacing = -1;
					move(vel, motion);
					break;
			}
		}
		//SDL_PumpEvents();
		const Uint8 *kbstate = SDL_GetKeyboardState(NULL);

		if (kbstate[SDL_SCANCODE_D]) {
			vel->mFacing = 1;
			move(vel, motion);
		}

		if (kbstate[SDL_SCANCODE_A]){
			vel->mFacing = -1;
			move(vel, motion);
		}
		
		//If user presses any key
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_SPACE) {
				int x = 0;
				if (vel->mFacing == 1) {
					x = dim->getRect()->x + dim->getRect()->w;
				} else if (vel->mFacing == -1) {
					x = dim->getRect()->x - 64;
				}
				int y = dim->getRect()->y;
				mEngine->addEntity(new LaserEntity(mEngine->getNextId(), x, y, vel->mFacing));
			}
		}
	}
}

void PlayerInputSystem::move(VelocityComponent *vel, PlayerMotionComponent* motion) {
	Vector2D* velocity = vel->getVelocity();
	int facing = vel->mFacing;

	velocity->x() += motion->xVelocity * facing;
}


void PlayerInputSystem::jump(VelocityComponent *vel, PlayerMotionComponent* motion) {
	Vector2D* velocity = vel->getVelocity();
	if (motion->jumpsLeft > 0) {
		velocity->y() -= motion->yVelocity; 
		motion->isOnGround = false; 
		motion->jumpsLeft--;
	}
}

