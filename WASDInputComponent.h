#pragma once
#include "inputcomponent.h"

#include "Vector2D.h"
#include "VelocityComponent.h"

class WASDInputComponent :
	public InputComponent
{
public:
	WASDInputComponent();
	~WASDInputComponent();

	void setInput(const char*, BaseEntity*);
};

