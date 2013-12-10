#pragma once
#include "basesystem.h"

#include "../Engine.h"

#include "../Components/AnimationComponent.h"
#include "../Components/PlayerMotionComponent.h"

class AnimationSystem :
	public BaseSystem
{
public:
	AnimationSystem(int);
	~AnimationSystem();

	void update();

	int framesPassed;
	int animationsPerSecond;
};

