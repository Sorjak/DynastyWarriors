#include "DimensionComponent.h"


DimensionComponent::DimensionComponent(int x, int y, int w, int h) {
	mRect = new SDL_Rect();
	mRect->x = x;
	mRect->y = y;
	mRect->w = w;
	mRect->h = h;
}


DimensionComponent::~DimensionComponent() {
	delete mRect;
}

SDL_Rect* DimensionComponent::getRect() {
	return mRect;
}
