#include "PlayerMotionComponent.h"


PlayerMotionComponent::PlayerMotionComponent(int xvel, int yvel, int totaljumps) {
	isOnGround = false;
	jumpsLeft = totaljumps;
	maxJumps = totaljumps;
	xVelocity = xvel;
	yVelocity = yvel;
}


PlayerMotionComponent::~PlayerMotionComponent(){}
