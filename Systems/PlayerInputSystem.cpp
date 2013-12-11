#include "PlayerInputSystem.h"

PlayerInputSystem::PlayerInputSystem(){

	mJumped = 0;

	// Initialize the joystick subsystem if it hasn't been already
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0){
		for (int i = 0; i < SDL_NumJoysticks(); i++){
			SDL_Joystick* joystick = SDL_JoystickOpen(i);

			if (joystick && SDL_JoystickGetAttached(joystick)){
				mJoysticks.push_back(joystick);
			}
			else {
				printf("Joystick error: %s\n", SDL_GetError());
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		printf("Joysticks initalized. Number of joysticks: %d\n", mJoysticks.size());
	}
	else {
		printf("No joysticks found\n");
	}
}
PlayerInputSystem::~PlayerInputSystem(){}

void PlayerInputSystem::update() {
	if (entityList.size() >= 1) {
		FighterEntity* fighter = (FighterEntity*)entityList[0];
		VelocityComponent *vel = (VelocityComponent*)fighter->getComponent("velocity");
		DimensionComponent *dim = (DimensionComponent*)fighter->getComponent("dimension");
		PlayerMotionComponent *motion = (PlayerMotionComponent*)fighter->getComponent("player_motion");

		int x_velocity = motion->xVelocity;
		int y_velocity = motion->yVelocity;
		Vector2D* velocity = vel->getVelocity();

		int joystickDeadZone = 8000;
		int maxJoystickValue = 32768;
		int scaleFactor = 200;
		bool moving = false;

		if (mJoysticks.size() > 0) {
			int joystickValue = SDL_JoystickGetAxis(mJoysticks[0], 0);
			if (joystickValue > joystickDeadZone) {
				int amountToMove = abs(joystickValue / scaleFactor);
				dim->mFacing = 1;
				velocity->x() = amountToMove * dim->mFacing;
				moving = true;
			}
			else if (joystickValue < -joystickDeadZone) {
				int amountToMove = abs(joystickValue / scaleFactor);
				dim->mFacing = -1;
				velocity->x() = amountToMove * dim->mFacing;
				moving = true;
			}
			else {}
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		if (state[SDL_SCANCODE_D]) {
			dim->mFacing = 1;
			velocity->x() += x_velocity * dim->mFacing;
			moving = true;
		} else if (state[SDL_SCANCODE_A]) {
			dim->mFacing = -1;
			velocity->x() += x_velocity * dim->mFacing;
			moving = true;
		}

		if (motion->isOnGround) {
			if (moving) {
				motion->fighterState = "RUNNING";
			} else {
				if (abs(velocity->x()) > 0) {
					motion->fighterState = "SLOWING";
				}
			}
		} else {
			if (motion->fighterState != "JUMPING") {
				motion->fighterState = "FALLING";
			}
		}
		

		//printf("Fighter state: %s\n", motion->fighterState.c_str());
	}
}

void PlayerInputSystem::process(SDL_Event e) {
	if (entityList.size() >= 1) {
		FighterEntity* fighter = (FighterEntity*)entityList[0];
		VelocityComponent *vel = (VelocityComponent*)fighter->getComponent("velocity");
		DimensionComponent *dim = (DimensionComponent*)fighter->getComponent("dimension");
		PlayerMotionComponent *motion = (PlayerMotionComponent*)fighter->getComponent("player_motion");

		int x_velocity = motion->xVelocity;
		int y_velocity = motion->yVelocity;
		Vector2D* velocity = vel->getVelocity();

		//If user presses any key
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_SPACE) {
				int x = 0;
				if (dim->mFacing == 1) {
					x = dim->getRect()->x + dim->getRect()->w;
				} else if (dim->mFacing == -1) {
					x = dim->getRect()->x - 64;
				}
				int y = dim->getRect()->y;
				mEngine->addEntity(new LaserEntity(mEngine->getNextId(), x, y, dim->mFacing));
			}
			if (e.key.keysym.sym == SDLK_w) {
				jump(vel, motion);
			}
		}
		if (e.type == SDL_JOYBUTTONDOWN) {
			if (e.jbutton.button == 10) {
				jump(vel, motion);
			}
		}
	}
}

void PlayerInputSystem::jump(VelocityComponent *vel, PlayerMotionComponent* motion) {
	Vector2D* velocity = vel->getVelocity();
	if (motion->jumpsLeft > 0) {
		velocity->y() -= motion->yVelocity; 
		motion->isOnGround = false; 
		motion->jumpsLeft--;
		motion->fighterState = "JUMPING";
	}
}

