#pragma once
#include "basecomponent.h"

#include "../Vector2D.h"

class DimensionComponent :
	public BaseComponent
{
public:
	DimensionComponent(int x, int y, int w, int h, int facing);
	~DimensionComponent();

	Vector2D* getPosition();
	SDL_Rect* getRect();
	SDL_Rect* getLastRect();
	int getFacing();
	void setFacing(int facing);
	void setLastRect(SDL_Rect*);

	Vector2D* mPosition;
	SDL_Rect* mRect;
	SDL_Rect* mLastRect;
	int mFacing;
};

