#pragma once
#include "basecomponent.h"
class DimensionComponent :
	public BaseComponent
{
public:
	DimensionComponent(int x, int y, int w, int h);
	~DimensionComponent();

	SDL_Rect* getRect();
	SDL_Rect* getLastRect();
	void setLastRect(SDL_Rect*);

	SDL_Rect* mRect;
	SDL_Rect* mLastRect;
};

