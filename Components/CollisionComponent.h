#pragma once
#include <vector>

#include "basecomponent.h"
#include "../Entities/BaseEntity.h"


class CollisionComponent :
	public BaseComponent
{
public:
	CollisionComponent();
	~CollisionComponent();

	bool isColliding();
	void clearCollisions();

	// left = 1
	// top = 2
	// right = 4
	// bottom = 8
	// topleft = left + top = 3, and so on
	vector<pair<BaseEntity*, int>> *mCollidingWith;
};