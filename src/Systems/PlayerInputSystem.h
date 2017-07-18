#pragma once
#include "BaseSystem.h"

#include "../Engine.h"
#include "../Vector2D.h"
#include "../Entities/FighterEntity.h"

#include "../Components/PlayerMotionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/StateComponent.h"
#include "../Components/DimensionComponent.h"

#define INPUT_ANALOG_UP -1
#define INPUT_ANALOG_DOWN 1
#define INPUT_ANALOG_LEFT -1
#define INPUT_ANALOG_RIGHT 1
#define INPUT_ANALOG_DEAD 0

class PlayerInputSystem :
	public BaseSystem
{
public:
	PlayerInputSystem();
	~PlayerInputSystem();

	void update();

	void process(SDL_Event e);

	bool initEntity();
	void jump();

	vector<SDL_Joystick*> mJoysticks;

	PlayerMotionComponent* mPlayerMotion;
	VelocityComponent* mPlayerVelocity;
	DimensionComponent* mPlayerDimension;
	StateComponent* mPlayerState;

};

