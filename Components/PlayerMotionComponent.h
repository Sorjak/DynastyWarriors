#pragma once
#include "BaseComponent.h"

class PlayerMotionComponent :
	public BaseComponent
{
public:
	PlayerMotionComponent(int, int, int);
	~PlayerMotionComponent();

	bool isOnGround;
	int jumpsLeft;
	int maxJumps;
	int xVelocity;
	int yVelocity;
};

