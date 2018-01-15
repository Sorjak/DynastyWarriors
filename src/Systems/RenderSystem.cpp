#include "RenderSystem.h"


void outlineRect(SDL_Renderer* renderer, SDL_Rect* rect) {
	SDL_Color mColor;
	SDL_GetRenderDrawColor(renderer, &mColor.r, &mColor.g, &mColor.b, &mColor.a);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, rect);
	SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
}

RenderSystem::RenderSystem(int width, int height, const char* title) //const char* background_file)
{
	mWidth  = width;
	mHeight = height;
	mWindow = SDL_CreateWindow(title, 100, 100, mWidth, mHeight, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	// mBackground = IMG_LoadTexture(mRenderer, background_file);

	if( TTF_Init() == -1 ) {
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	mFont = TTF_OpenFont("media/SourceSansPro-Regular.ttf", 24 );

	fpsTimer = SDL_GetTicks();
	framesElapsed = 0;
	currentFPS = 60;
}

void RenderSystem::init(Engine* e) {
	cout << "Initializing Render System" << endl;
	mEngine = e;

	terrain = static_pointer_cast<TerrainSystem>(mEngine->getSystem("terrain"));
	cam = static_pointer_cast<CameraSystem>(mEngine->getSystem("camera"));
	creature = static_pointer_cast<CreatureSystem>(mEngine->getSystem("creature"));
	plant = static_pointer_cast<PlantSystem>(mEngine->getSystem("plant"));
}


RenderSystem::~RenderSystem()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

void RenderSystem::update() {
	frameStartTime = SDL_GetTicks();
	SDL_RenderClear(mRenderer);
	
	auto islands = terrain->getIslandsInRect(&cam->view, cam->scale);

    for (auto i = islands.begin(); i != islands.end(); ++i)
    {
        (*i)->Render(mRenderer, &cam->view, cam->scale);
    }

    auto plants = plant->GetPlantsInRect(&cam->view);

    for (auto i = plants.begin(); i != plants.end(); ++i)
    {
        (*i)->Render(mRenderer, &cam->view, cam->scale);
    }

	// cout << "Rendering creatures" << endl;
    if (!creature->hasTemplate)
    	creature->CreateCreatureTemplate(mRenderer, 512, 512);

    auto creatures = creature->GetCreaturesInRect(&cam->view);

    for (auto i = creatures.begin(); i != creatures.end(); ++i)
    {
    	SDL_Rect drawRect = { cam->view.x, cam->view.y, 16, 16 };
        (*i)->Render(mRenderer, &drawRect, cam->scale);
    }


	for (size_t i = 0; i < entityList.size(); i++) {
		SDL_Texture* renderTex;
		SDL_Rect* sourceRect = NULL;
		SDL_Rect* renderRect;
		SDL_RendererFlip flip = SDL_FLIP_NONE;

		if ( entityList[i]->hasComponent("texture")  ) {
			TextureComponent *tex = (TextureComponent*) entityList[i]->getComponent("texture");
			renderTex = tex->getTexture(mRenderer);
		}
		
		SDL_RenderCopyEx(mRenderer, renderTex, sourceRect, renderRect, 0, NULL, flip);

	}
	//Calculate FPS
	if (frameStartTime - fpsTimer >= 1000) {
		currentFPS = framesElapsed * 1.0;
		framesElapsed = 0;
		fpsTimer = SDL_GetTicks();
	} else {
		framesElapsed++;
	}
	
	displayFPSTexture();
	displayInfo();
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 205, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(mRenderer);
	frameEndTime = SDL_GetTicks();
}

void RenderSystem::displayFPSTexture() {
	SDL_Color color; color.r = 255; color.b = 255; color.g = 255;
	string fpsString = "FPS: ";

	fpsString += to_string((int) getCurrentFPS());

	SDL_Rect rect = {5, 5, 60, 24};

	displayText(color, &rect, fpsString);
}

void RenderSystem::displayInfo() {
	SDL_Color color; color.r = 255; color.b = 255; color.g = 255;
	// string infoString = terrain->getCurrentChunkInfo();
	string infoString = to_string(cam->view.x + (cam->view.w / 2));
	infoString += ", " + to_string(cam->view.y + (cam->view.h / 2));

	SDL_Rect rect = {65, 5, 52, 24};

	displayText(color, &rect, infoString);	
}

void RenderSystem::displayText(SDL_Color color, SDL_Rect *rect, string text) {
	SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, text.c_str(), color );
	SDL_Texture* renderTex = SDL_CreateTextureFromSurface( mRenderer, textSurface );
	SDL_FreeSurface( textSurface );

	SDL_RenderCopy( mRenderer, renderTex, NULL, rect );
	
	SDL_DestroyTexture( renderTex );
}

float RenderSystem::getCurrentFPS() {
	return currentFPS;
}


