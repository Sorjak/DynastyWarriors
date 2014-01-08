#pragma once
#include "BaseComponent.h"
class StateComponent :
	public BaseComponent
{
public:
	StateComponent(string hState, string vState, string aState);
	~StateComponent();

	string lastUpdated;

	string mVerticalState;
	string mHorizontalState;
	string mAttackState;

	string getVerticalState();
	string getHorizonalState();
	string getAttackState();

	void setVerticalState(string state);
	void setHorizontalState(string state);
	void setAttackState(string state);
};

