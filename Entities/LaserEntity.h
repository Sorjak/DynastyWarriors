#pragma once
#include "baseentity.h"

#include "../Components/TextureComponent.h"
#include "../Components/DimensionComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ExpirationComponent.h"

class LaserEntity :
	public BaseEntity
{
public:
	LaserEntity(int, int);
	LaserEntity(int, int, BaseEntity*);
};

