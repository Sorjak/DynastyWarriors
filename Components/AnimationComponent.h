#pragma once
#include "basecomponent.h"
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

class AnimationComponent :
	public BaseComponent
{
public:
	AnimationComponent(const string, map<string, pair<int, int>>, int);
	~AnimationComponent();

	SDL_Surface* mSurface;
	int mSpriteSize;
	SDL_Rect* mIndexRect;
	SDL_Texture* mCurrentTexture;
	map<string, pair<int, int>> mStateMap;

	int currentTotalFrames;
	int currentFrame;
	string currentState;

	SDL_Texture* getCurrentTexture(SDL_Renderer*);
	SDL_Rect* getIndexRect();
	int getTotalFrames();
	void setState(string);
};

