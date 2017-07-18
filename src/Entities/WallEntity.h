#pragma once
#include "baseentity.h"

#include "../Components/TextureComponent.h"
#include "../Components/DimensionComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/FrictionComponent.h"

class WallEntity :
	public BaseEntity
{
public:
	WallEntity(long, SDL_Rect*);
};

