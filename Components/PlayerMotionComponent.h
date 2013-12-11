#pragma once
#include <string>

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

	string fighterState;
	string fighterAttackState;
};

