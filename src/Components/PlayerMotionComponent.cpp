#include "PlayerMotionComponent.h"


PlayerMotionComponent::PlayerMotionComponent(int xvel, int yvel, int totaljumps) {
	jumpsLeft = totaljumps;
	maxJumps = totaljumps;
	xVelocity = xvel;
	yVelocity = yvel;
}


PlayerMotionComponent::~PlayerMotionComponent(){}
