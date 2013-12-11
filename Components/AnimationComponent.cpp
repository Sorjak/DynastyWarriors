#include "AnimationComponent.h"


AnimationComponent::AnimationComponent(const string filename, map<string, Animation*> state_map, int img_size){
	mSurface = IMG_Load(filename.c_str());
	mStateMap = state_map;
	mSpriteSize = img_size;


	mIndexRect = new SDL_Rect();
	mIndexRect->x = 0; mIndexRect->y = 0; mIndexRect->w = img_size; mIndexRect->h = img_size;
	mCurrentTexture = NULL;

	currentState = "IDLE";
	currentFrame = 0;
}

AnimationComponent::~AnimationComponent(){}

SDL_Texture* AnimationComponent::getCurrentTexture(SDL_Renderer* ren) {
	if (mCurrentTexture == NULL) {
		mCurrentTexture = SDL_CreateTextureFromSurface(ren, mSurface);
	}
	return mCurrentTexture; 
}

SDL_Rect* AnimationComponent::getIndexRect() {
	mIndexRect->x = currentFrame * mSpriteSize;
	mIndexRect->y = mStateMap[currentState]->mColumn * mSpriteSize;
	return mIndexRect;
}

int AnimationComponent::getTotalFrames() {
	return mStateMap[currentState]->mNumFrames;
}

void AnimationComponent::setState(string state) {
	printf("Changing state to %s\n", state.c_str());
	if (state != currentState) {
		currentFrame = 0;
	}
	currentState = state;
	
}

bool AnimationComponent::isRepeat() {
	return mStateMap[currentState]->mRepeat;
}

string AnimationComponent::getNextAnimation() {
	return mStateMap[currentState]->mNextAnimation;
}

