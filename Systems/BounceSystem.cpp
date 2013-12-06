#include "BounceSystem.h"


BounceSystem::BounceSystem(int width, int height) {
	mWidth = width;
	mHeight = height;
}


BounceSystem::~BounceSystem(){}


void BounceSystem::update() {

	for (size_t i = 0; i < entityList.size(); i++) {
		DimensionComponent *dim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
		VelocityComponent *vel = (VelocityComponent*) entityList[i]->componentMap["velocity"];
		SDL_Rect *rect = dim->getRect();
		Vector2D *velocity = vel->getVelocity();
		Vector2D *position = new Vector2D((float)rect->x, (float)rect->y);

		if (position->x() + rect->w > mWidth) {
			velocity->x() = (velocity->x() * -1) * 1.f;
			position->x() = (mWidth - rect->w - 1) * 1.f;
		}
		if (position->x() < 0) {
			velocity->x() = (velocity->x() * -1) * 1.f;
			position->x() = 1.f;
		}

		if (position->y() + rect->h > mHeight) {
			velocity->y() = (velocity->y() * -1) * 1.f;
			position->y() = (mHeight - rect->h - 1) * 1.f;
		}

		if (position->y() < 0) {
			velocity->y() = (velocity->y() * -1) * 1.f;
			position->y() = 1.f;
		}
	}
}