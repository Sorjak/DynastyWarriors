#include "RenderSystem.h"


void outlineRect(SDL_Renderer* renderer, SDL_Rect* rect) {
	SDL_Color mColor;
	SDL_GetRenderDrawColor(renderer, &mColor.r, &mColor.g, &mColor.b, &mColor.a);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, rect);
	SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
}

RenderSystem::RenderSystem(int width, int height, const char* title)
{
	const int SCREEN_WIDTH  = width;
	const int SCREEN_HEIGHT = height;
	mWindow = SDL_CreateWindow(title, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if( TTF_Init() == -1 ) {
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	mFont = TTF_OpenFont("media/SourceSansPro-Regular.ttf", 24 );
	fpsTimer = SDL_GetTicks();
	framesElapsed = 0;
	currentFPS = 60;
}


RenderSystem::~RenderSystem()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

void RenderSystem::update() {
	frameStartTime = SDL_GetTicks();
	SDL_RenderClear(mRenderer);
	for (size_t i = 0; i < entityList.size(); i++) {
		
		SDL_Texture* renderTex;
		SDL_Rect* renderRect;
		if ( entityList[i]->hasComponent("texture")  ) {
			TextureComponent *tex = (TextureComponent*) entityList[i]->componentMap["texture"];
			DimensionComponent *dim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
			renderTex = tex->getTexture(mRenderer);
			renderRect = dim->getRect();
		}
		
		SDL_RenderCopy(mRenderer, renderTex, NULL, renderRect);
		outlineRect(mRenderer, renderRect);

		SDL_Color idColor; idColor.r = 0; idColor.b = 0; idColor.g = 0;
		SDL_Rect* idRect = new SDL_Rect();
		idRect->x = renderRect->x; idRect->y = renderRect->y; idRect->w = renderRect->w; idRect->h = renderRect->h;
		displayText(idColor, idRect, to_string(entityList[i]->mID));

	}
	//Calculate FPS
	if (frameStartTime - fpsTimer >= 1000) {
		currentFPS = framesElapsed;
		framesElapsed = 0;
		fpsTimer = SDL_GetTicks();
	} else {
		framesElapsed++;
	}
	displayFPSTexture();
	SDL_RenderPresent(mRenderer);
	frameEndTime = SDL_GetTicks();
}

void RenderSystem::displayFPSTexture() {
	SDL_Color color; color.r = 255; color.b = 255; color.g = 255;
	string fpsString = "FPS: ";

	fpsString += to_string(getCurrentFPS());

	SDL_Rect rect = {5, 5, 36, 24};

	displayText(color, &rect, fpsString);
}

void RenderSystem::displayText(SDL_Color color, SDL_Rect *rect, string text) {
	SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, text.c_str(), color );
	SDL_Texture* renderTex = SDL_CreateTextureFromSurface( mRenderer, textSurface );

	SDL_RenderCopy( mRenderer, renderTex, NULL, rect );
	SDL_FreeSurface( textSurface );
	SDL_free( renderTex );
}

int RenderSystem::getCurrentFPS() {
	return currentFPS;
}


