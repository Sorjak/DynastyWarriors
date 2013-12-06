#include "VelocityComponent.h"


VelocityComponent::VelocityComponent(float x, float y) {
	mVelocity = new Vector2D(x, y);
	mFacing = 1;
}


VelocityComponent::~VelocityComponent(void) {
	delete mVelocity;
}

Vector2D* VelocityComponent::getVelocity() {
	return mVelocity;
}
