#include "PlayerInputSystem.h"

PlayerInputSystem::PlayerInputSystem(){

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
	if (initEntity()) {

		int x_velocity = mPlayerMotion->xVelocity;
		int y_velocity = mPlayerMotion->yVelocity;
		Vector2D* velocity = mPlayerVelocity->getVelocity();

		int joystickDeadZone = 8000;
		int maxJoystickValue = 32768;
		int scaleFactor = 200;
		bool moving = false;

		if (mJoysticks.size() > 0) {
			int joystickValue = SDL_JoystickGetAxis(mJoysticks[0], 0);
			if (abs(joystickValue) > joystickDeadZone && mPlayerState->getVerticalState() != "GROUND") {
				joystickValue = maxJoystickValue * (joystickValue / abs(joystickValue));
			}
			int amountToMove = abs(joystickValue / scaleFactor);

			if (joystickValue > joystickDeadZone) {	
				mPlayerDimension->mFacing = 1;
				velocity->x() = amountToMove * mPlayerDimension->mFacing;
				moving = true;
			}
			else if (joystickValue < -joystickDeadZone) {
				mPlayerDimension->mFacing = -1;
				velocity->x() = amountToMove * mPlayerDimension->mFacing;
				moving = true;
			}
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_D]) {
			mPlayerDimension->mFacing = 1;
			velocity->x() += x_velocity * mPlayerDimension->mFacing;
			moving = true;
		}
		else if (state[SDL_SCANCODE_A]) {
			mPlayerDimension->mFacing = -1;
			velocity->x() += x_velocity * mPlayerDimension->mFacing;
			moving = true;
		}

		if (mPlayerState->getVerticalState() == "GROUND") { 
			if (moving) {
				mPlayerState->setHorizontalState("RUNNING");
			}
			else {
				if (abs(velocity->x()) > 0) {
					mPlayerState->setHorizontalState("SLOWING");
				}
			}
		} else {
			if (mPlayerState->getVerticalState() != "JUMPING") {
				mPlayerState->setVerticalState("FALLING");
			}
		}
	}
}

void PlayerInputSystem::process(SDL_Event e) {
	if (initEntity()) {

		int x_velocity = mPlayerMotion->xVelocity;
		int y_velocity = mPlayerMotion->yVelocity;
		Vector2D* velocity = mPlayerVelocity->getVelocity();

		//If user presses any key
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_j) {
				if (mPlayerState->getVerticalState() == "GROUND")
					mPlayerState->setAttackState("PUNCHING");
			}
			if (e.key.keysym.sym == SDLK_i) {
				if (mPlayerState->getVerticalState() == "GROUND")
					mPlayerState->setAttackState("KICKING");
			}
			if (e.key.keysym.sym == SDLK_w) {
				jump();
			}
		}
		if (e.type == SDL_JOYBUTTONDOWN) {
			if (e.jbutton.button == 10) {
				jump();
			}
			if (e.jbutton.button == 12) {
				if (mPlayerState->getVerticalState() == "GROUND" && mPlayerState->getHorizonalState() != "RUNNING")
					mPlayerState->setAttackState("PUNCHING");
			}
			if (e.jbutton.button == 11) {
				if (mPlayerState->getVerticalState() == "GROUND" && mPlayerState->getHorizonalState() != "RUNNING")
					mPlayerState->setAttackState("KICKING");
			}
		}
	}
}

bool PlayerInputSystem::initEntity() {
	if (entityList.size() >= 1) {
		FighterEntity* fighter = (FighterEntity*)entityList[0];
		mPlayerVelocity = (VelocityComponent*)fighter->getComponent("velocity");
		mPlayerDimension = (DimensionComponent*)fighter->getComponent("dimension");
		mPlayerMotion = (PlayerMotionComponent*)fighter->getComponent("player_motion");
		mPlayerState = (StateComponent*)fighter->getComponent("state");
		return true;
	}

	return false;
}

void PlayerInputSystem::jump() {
	Vector2D* velocity = mPlayerVelocity->getVelocity();
	if (mPlayerMotion->jumpsLeft > 0) {
		velocity->y() -= mPlayerMotion->yVelocity;
		mPlayerMotion->jumpsLeft--;
		mPlayerState->setVerticalState("JUMPING");
	}
}

