#pragma once
#include "basecomponent.h"

#include "../Vector2D.h"

class DimensionComponent :
	public BaseComponent
{
public:
	DimensionComponent(int x, int y, int w, int h);
	~DimensionComponent();

	Vector2D* getPosition();
	SDL_Rect* getRect();
	SDL_Rect* getLastRect();
	void setLastRect(SDL_Rect*);

	Vector2D* mPosition;
	SDL_Rect* mRect;
	SDL_Rect* mLastRect;
};

