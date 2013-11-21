#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

};

