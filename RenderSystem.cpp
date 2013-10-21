#include "RenderSystem.h"


void outlineRect(SDL_Renderer* renderer, SDL_Rect rect) {
	SDL_Color mColor;
	SDL_GetRenderDrawColor(renderer, &mColor.r, &mColor.g, &mColor.b, &mColor.a);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
}

RenderSystem::RenderSystem(int width, int height, const char* title)
{
	const int SCREEN_WIDTH  = width;
	const int SCREEN_HEIGHT = height;
	mWindow = SDL_CreateWindow(title, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}


RenderSystem::~RenderSystem()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

void RenderSystem::update() {
	SDL_RenderClear(mRenderer);
	for (size_t i = 0; i < entityList.size(); i++) {
		TextureComponent *tex = (TextureComponent*) entityList[i]->componentMap["texture"];
		DimensionComponent *dim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
		SDL_RenderCopy(mRenderer, tex->getTexture(mRenderer), NULL, dim->getRect());
	}
	SDL_RenderPresent(mRenderer);
}


