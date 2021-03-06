#pragma once
#include "basecomponent.h"

#include "../Entities/BaseEntity.h"

class InputComponent :
	public BaseComponent
{
public:
	InputComponent();
	~InputComponent();

	virtual void setInput(const char*, BaseEntity*);
};

