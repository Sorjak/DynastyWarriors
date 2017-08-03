#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <memory>
#include <time.h>
#include <random>
#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <noise/noise.h>

#include "../src/Entities/Creature.h"
#include "../src/Utils.h"

using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;


SDL_Rect view_rect = { 0, 0, screenWidth, screenHeight };
SDL_Rect FPS_rect = { 5, 5, 100, 24 };

int currentFPS = 60;
int frameStartTime;

int fpsTimer = 0;
int framesElapsed = 0;


int main( int argc, char* args[] ) 
{ 
    cout << "starting test" << endl;

    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Event       mEvent;

    bool running = true;

    fpsTimer = SDL_GetTicks();

    SDL_Init(SDL_INIT_EVERYTHING);

    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return 1;
    }


    TTF_Font* mFont = TTF_OpenFont("media/SourceSansPro-Regular.ttf", 24 );
    if(!mFont) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        //return 1;
    }

    window = SDL_CreateWindow("SDL2 Window", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if(window==NULL)
    {   
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	srand(static_cast<unsigned int>(time(0)));

    bool mouseIsDown = false;
    bool raise = false;

	Creature guy(128, 128);
    bool* bodyPoints = new bool[128 * 128];
    SDL_Rect* bodyBounds;

    guy.GenerateBody(128, 128, bodyPoints, bodyBounds);
	guy.MakeSprite(renderer);

    while (running) {
        frameStartTime = SDL_GetTicks();
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, NULL);
        
        SDL_Point mousePos;
        
        //Event polling
        while (SDL_PollEvent(&mEvent)){

            //If user closes the window
            if (mEvent.type == SDL_QUIT) {
                running = false;
            }

            //If user presses any key
            if (mEvent.type == SDL_KEYDOWN) {
                if (mEvent.key.keysym.sym == SDLK_q) {
                    running = false;
                }

            }

            //If user clicks the mouse
            if (mEvent.type == SDL_MOUSEBUTTONDOWN) {
                mousePos.x = mEvent.button.x;
                mousePos.y = mEvent.button.y;
                mouseIsDown = true;

				//SDL_DestroyTexture(spriteTex);
				guy.GenerateBody();
				guy.MakeSprite(renderer);
            }

            if (mEvent.type == SDL_MOUSEBUTTONUP) {
                mouseIsDown = false;
            }

            if (mEvent.type == SDL_MOUSEMOTION && mouseIsDown) {
                mousePos.x = mEvent.motion.x;
                mousePos.y = mEvent.motion.y;
            }

        }
		
		guy.Render(renderer, screenWidth / 2, screenHeight / 2);

		//Calculate FPS
		if (frameStartTime - fpsTimer >= 1000) {
			currentFPS = framesElapsed;
			framesElapsed = 0;
			fpsTimer = SDL_GetTicks();
		}
		else {
			framesElapsed++;
		}

		// cout << to_string(currentFPS) << endl;
		SDL_Color color; color.r = 255; color.b = 128; color.g = 255;
		string ui_string = "X:" + to_string(view_rect.x) + ", Y:" + to_string(view_rect.y);

		ui_string += " | FPS: " + to_string(currentFPS);

		if (mFont) {
			SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, ui_string.c_str(), color);
			SDL_Texture* renderTex = SDL_CreateTextureFromSurface(renderer, textSurface);
			SDL_RenderCopy(renderer, renderTex, NULL, &FPS_rect);
			SDL_FreeSurface(textSurface);
			SDL_DestroyTexture(renderTex);
		}

		SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window); 

    SDL_Quit(); 

    return 0;   
}
