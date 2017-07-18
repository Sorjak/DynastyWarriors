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
		SDL_Rect *rect = dim->getRect();
		Vector2D *position = dim->getPosition();

		int centerx = position->x() + (rect->w / 2);
		int centery = position->y() + (rect->h / 2);

		if (centerx >= mWidth) {
			position->x() = 1.f;
		}
		if (centerx < 0) {
			position->x() = mWidth - rect->w - 1;
		}

		if (centery >= mHeight) {
			position->y() = 1.f;
		}

		if (centery < 0) {
			position->y() = mHeight - 1.f;
		}
	}
}