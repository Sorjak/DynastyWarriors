#include "BounceSystem.h"


BounceSystem::BounceSystem(int width, int height) {
	mWidth = width;
	mHeight = height;
}


BounceSystem::~BounceSystem(){}


void BounceSystem::update() {

	for (size_t i = 0; i < entityList.size(); i++) {
		BaseEntity* current = entityList[i];
		DimensionComponent *dim = (DimensionComponent*) current->getComponent("dimension");
		VelocityComponent *vel = (VelocityComponent*)current->getComponent("velocity");
		SDL_Rect *rect = dim->getRect();
		Vector2D *velocity = vel->getVelocity();
		Vector2D *position = dim->getPosition();

		if (position->x() >= mWidth) {
			position->x() = 1.f;
		}
		if (position->x() + rect->w < 0) {
			position->x() = mWidth - rect->w - 1;
		}

		if (position->y()  >= mHeight) {
			position->y() = 1.f;
		}

		if (position->y() + rect->h < 0) {
			position->y() = mHeight - 1.f;
		}
	}
}