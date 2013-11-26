#pragma once
#include "baseentity.h"

#include "../Components/TextureComponent.h"
#include "../Components/DimensionComponent.h"

class WallEntity :
	public BaseEntity
{
public:
	WallEntity(long, int, int);
};

