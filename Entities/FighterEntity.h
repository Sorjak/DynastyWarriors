#pragma once

#include <string>
#include "baseentity.h"

#include "../Components/TextureComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/DimensionComponent.h"
#include "../Components/PlayerMotionComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/AnimationComponent.h"



class FighterEntity :
	public BaseEntity
{
public:
	FighterEntity(long);
};

