#include "PlayerInputSystem.h"

PlayerInputSystem::PlayerInputSystem(){

	// Initialize the joystick soundsystem if it hasn't been already
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joystick = SDL_JoystickOpen(i);


			if (joystick && SDL_JoystickGetAttached(joystick))
			{
				mJoysticks.push_back(joystick);
			}
			else
			{
				printf("Joystick error: %s\n", SDL_GetError());
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		printf("Joysticks initalized. Number of joysticks: %d\n", mJoysticks.size());
	}
	else
	{
		printf("No joysticks found\n");
	}
}
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


		int joystickDeadZone = 5000;
		//
		// JOYSTICK AXIS MOTION
		//
		if (e.type == SDL_JOYBUTTONDOWN)
		{
			printf("Button was pressed: %d\n", e.jbutton.button);
			if (e.jbutton.button == 10) {
				jump(vel, motion);
			}

		}
		SDL_PumpEvents();
		int joystickValue = SDL_JoystickGetAxis(mJoysticks[0], 0);
		if (joystickValue > joystickDeadZone) {
			vel->mFacing = 1;
			move(vel, abs(joystickValue / 162));
		}
		else if (joystickValue < -joystickDeadZone) {
			vel->mFacing = -1;
			move(vel, abs(joystickValue / 162));
		}
		else {}

	}
}

void PlayerInputSystem::move(VelocityComponent *vel, float amount) {
	Vector2D* velocity = vel->getVelocity();
	int facing = vel->mFacing;

	velocity->x() += amount * facing;
}


void PlayerInputSystem::jump(VelocityComponent *vel, PlayerMotionComponent* motion) {
	Vector2D* velocity = vel->getVelocity();
	if (motion->jumpsLeft > 0) {
		velocity->y() = -motion->xVelocity; 
		motion->isOnGround = false; 
		motion->jumpsLeft--;
	}
}

