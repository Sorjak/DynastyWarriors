#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "basesystem.h"
#include "../Components/TextureComponent.h"
#include "../Components/DimensionComponent.h"

class RenderSystem : public BaseSystem
{
public:
	RenderSystem(int width, int height, const char* title);
	~RenderSystem();

	void update();
	

	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
	TTF_Font* mFont;
	int frameStartTime;
	int frameEndTime;
	int fpsTimer;
	int framesElapsed;
	int currentFPS;

private:
	void displayFPSTexture();
	void displayText(SDL_Color, SDL_Rect*, string);

};

