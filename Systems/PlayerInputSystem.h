#pragma once
#include "BaseSystem.h"

#include "../Engine.h"
#include "../Vector2D.h"
#include "../Components/PlayerMotionComponent.h"
#include "../Components/VelocityComponent.h"

class PlayerInputSystem :
	public BaseSystem
{
public:
	PlayerInputSystem();
	~PlayerInputSystem();

	void update();

	void process(SDL_Event e);

	void move(VelocityComponent*, PlayerMotionComponent*);
	void jump(VelocityComponent*, PlayerMotionComponent*);

};

