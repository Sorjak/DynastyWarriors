#pragma once
#include "basecomponent.h"
class FrictionComponent :
	public BaseComponent
{
public:
	FrictionComponent(int);
	~FrictionComponent();

	int mStrength;
};

