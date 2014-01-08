#pragma once
#include "basesystem.h"

#include "../Engine.h"

#include "../Components/AnimationComponent.h"
#include "../Components/PlayerMotionComponent.h"
#include "../Components/StateComponent.h"

class AnimationSystem :
	public BaseSystem
{
public:
	AnimationSystem(int);
	~AnimationSystem();

	AnimationComponent* mAnimation;
	StateComponent* mState;

	void update();

	int framesPassed;
	int animationsPerSecond;
};

