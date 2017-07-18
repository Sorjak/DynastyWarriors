#pragma once
#include "basecomponent.h"
class ExpirationComponent :
	public BaseComponent
{
public:
	ExpirationComponent(int);
	~ExpirationComponent();

	int mStart;
	int mDuration;
};

