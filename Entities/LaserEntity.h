#pragma once
#include "baseentity.h"

#include "TextureComponent.h"
#include "DimensionComponent.h"
#include "VelocityComponent.h"
#include "ProjectileComponent.h"

class LaserEntity :
	public BaseEntity
{
public:
	LaserEntity(int, int);
	LaserEntity(int, int, BaseEntity*);
};

