#pragma once
#include "basecomponent.h"

#include "LaserEntity.h"

class ShootLaserComponent :
	public BaseComponent
{
public:
	ShootLaserComponent();
	~ShootLaserComponent();

	void shoot();
};

