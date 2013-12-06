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
	LaserEntity(long, int, int, int);
	LaserEntity(long, int, int, int, BaseEntity*);
};

