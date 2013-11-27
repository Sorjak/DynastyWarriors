#pragma once
#include "BaseSystem.h"

#include "../Components/DimensionComponent.h"
#include "../Components/VelocityComponent.h"

class CollisionSystem :
	public BaseSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void update();
	bool isColliding(SDL_Rect*, SDL_Rect*);
	int collidedFrom(SDL_Rect*, SDL_Rect*);
	string getPrettyDirection(int);

	enum DIRECTIONS { LEFT = 1, TOP = 2, RIGHT = 4, BOTTOM = 8 };

};

