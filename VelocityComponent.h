#pragma once
#include "basecomponent.h"

#include "Vector2D.h"

class VelocityComponent :
	public BaseComponent
{
public:
	VelocityComponent(float, float);
	~VelocityComponent();

	Vector2D* mVelocity;

	Vector2D* getVelocity();
};

