#pragma once
#include "baseentity.h"

#include "../Components/TextureComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/DimensionComponent.h"
#include "../Components/PlayerMotionComponent.h"

class FighterEntity :
	public BaseEntity
{
public:
	FighterEntity(long);
};

