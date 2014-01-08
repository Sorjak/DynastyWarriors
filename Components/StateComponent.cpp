#include "StateComponent.h"


StateComponent::StateComponent(string hState, string vState, string aState){
	lastUpdated = "HORIZONTAL";
	mVerticalState = vState;
	mHorizontalState = hState;
	mAttackState = aState;
}


StateComponent::~StateComponent(){}

string StateComponent::getVerticalState() {
	return mVerticalState;
}
string StateComponent::getHorizonalState() {
	return mHorizontalState;
}
string StateComponent::getAttackState() {
	return mAttackState;
}

void StateComponent::setVerticalState(string state) {
	lastUpdated = "VERTICAL";
	mVerticalState = state;
}
void StateComponent::setHorizontalState(string state) {
	lastUpdated = "HORIZONTAL";
	mHorizontalState = state;
}
void StateComponent::setAttackState(string state) {
	lastUpdated = "ATTACK";
	mAttackState = state;
}