#pragma once

#include "../Animation.h"
#include "BaseEntity.h"

#include "../Components/AnimationComponent.h"
#include "../Components/StateComponent.h"
class DummyEntity :
	public BaseEntity
{
public:
	DummyEntity(long id);
	~DummyEntity();
};

