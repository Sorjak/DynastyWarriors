#pragma once
#include "basesystem.h"

#include "../Components/AnimationComponent.h"
#include "../Components/PlayerMotionComponent.h"

class AnimationSystem :
	public BaseSystem
{
public:
	AnimationSystem();
	~AnimationSystem();

	void update();
};

