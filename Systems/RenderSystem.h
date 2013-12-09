#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "basesystem.h"
#include "../Components/TextureComponent.h"
#include "../Components/DimensionComponent.h"
#include "../Components/AnimationComponent.h"

class RenderSystem : public BaseSystem
{
public:
	RenderSystem(int width, int height, const char* title);
	~RenderSystem();

	void update();
	int getCurrentFPS();
	

	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
	TTF_Font* mFont;

	

private:
	void displayFPSTexture();
	void displayText(SDL_Color, SDL_Rect*, string);
	int currentFPS;
	int frameStartTime;
	int frameEndTime;
	int fpsTimer;
	int framesElapsed;

};

