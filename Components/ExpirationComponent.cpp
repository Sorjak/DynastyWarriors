#include "ExpirationComponent.h"


ExpirationComponent::ExpirationComponent(int duration) {
	mStart = SDL_GetTicks();
	mDuration = duration;
}


ExpirationComponent::~ExpirationComponent(void){}


