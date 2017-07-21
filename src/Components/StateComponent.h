#pragma once
#include "BaseComponent.h"
class StateComponent :
	public BaseComponent
{
public:
	StateComponent();
	~StateComponent();

	string lastUpdated;
};

