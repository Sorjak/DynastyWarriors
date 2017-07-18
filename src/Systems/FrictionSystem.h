#pragma once
#include "basesystem.h"

#include "../Components/FrictionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/DimensionComponent.h"
#include "../Components/StateComponent.h"

class FrictionSystem :
	public BaseSystem
{
public:
	FrictionSystem();
	~FrictionSystem();

	void update();
};

