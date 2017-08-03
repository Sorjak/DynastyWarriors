#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "basesystem.h"
#include "CameraSystem.h"
#include "TerrainSystem.h"
#include "CreatureSystem.h"

class TerrainSystem;
class CameraSystem;
class CreatureSystem;

#include "../Components/TextureComponent.h"
// #include "../Components/DimensionComponent.h"
#include "../Components/AnimationComponent.h"

class RenderSystem : public BaseSystem
{
public:
	RenderSystem(int width, int height, const char* title);//, const char* background_file);
	~RenderSystem();

	void init(Engine* e);
	void update();
	float getCurrentFPS();
	

	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
	TTF_Font* mFont;
	// SDL_Texture* mBackground;
	
	shared_ptr<TerrainSystem> terrain;
	shared_ptr<CameraSystem> cam;
	shared_ptr<CreatureSystem> creature;

private:
	void displayFPSTexture();
	void displayText(SDL_Color, SDL_Rect*, string);
	float currentFPS;
	int frameStartTime;
	int frameEndTime;
	int fpsTimer;
	int framesElapsed;
	int mWidth;
	int mHeight;
};

