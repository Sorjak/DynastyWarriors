#include "DimensionComponent.h"


DimensionComponent::DimensionComponent(int x, int y, int w, int h) {
	mPosition = new Vector2D(x, y);

	mRect = new SDL_Rect();
	mRect->x = x;
	mRect->y = y;
	mRect->w = w;
	mRect->h = h;

	mLastRect = new SDL_Rect();

	mFacing = 1;
}


DimensionComponent::~DimensionComponent() {
	delete mRect;
	delete mLastRect;
}

Vector2D* DimensionComponent::getPosition() {
	return mPosition;
}

SDL_Rect* DimensionComponent::getRect() {
	mRect->x = mPosition->x();
	mRect->y = mPosition->y();
	return mRect;
}

SDL_Rect* DimensionComponent::getLastRect() {
	return mLastRect;
}

void DimensionComponent::setLastRect(SDL_Rect* rect) {
	mLastRect->x = rect->x;
	mLastRect->y = rect->y;
	mLastRect->w = rect->w;
	mLastRect->h = rect->h;
}
