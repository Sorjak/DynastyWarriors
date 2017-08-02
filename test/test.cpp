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

noise::module::Perlin noiseModule;

float getRand01() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}


float getRand(float maxNum) {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * maxNum;
}


class GenSprite {

public:
	int width;
	int height;

	SDL_Point* bodyPoints;

	SDL_Rect bounds;

	SDL_Renderer* renderer;
	SDL_Texture* texture;

	GenSprite(SDL_Renderer* ren, int w, int h) {
		this->width = w;
		this->height = h;

		texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, w, h);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

		this->renderer = ren;

		GenerateBody();
		MakeSprite();
	}

	void Render(int x, int y) {
		int posX = x - width / 2;
		int posY = y - height / 2;

		SDL_Rect sprect = { posX, posY, width, height };
		SDL_RenderCopy(renderer, texture, NULL, &sprect);

		SDL_Rect outline = { posX + bounds.x, posY + bounds.y, bounds.w, bounds.h };
		SDL_SetRenderDrawColor(this->renderer, red.r, red.g, red.b, red.a);
		SDL_RenderDrawRect(this->renderer, &outline);
	}

	void GenerateBody() {

		bodyPoints = new SDL_Point[width * height];
		float noiseScale = 300.0;
		SDL_Point noiseOffset = { getRand(10000), getRand(10000) };

		int numBodyPoints = 0;

		SDL_Point* enclosurePoints = new SDL_Point[width * height];

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				float sampleX = (x + noiseOffset.x) / noiseScale;
				float sampleY = (y + noiseOffset.y) / noiseScale;

				float r = max(-1.0, noiseModule.GetValue(sampleX, sampleY, 1.0));
				float sample = (r + 1) / 2;

				// Get x an y values between -1 and 1
				float horizontal = (x / (float)width) * 2 - 1;
				float vertical = 1 - (y / (float)height);

				// Which one is closer to the edge?
				float val = max(abs(horizontal), abs(vertical));

				// Gradual increase curve from 0 to 1
				float smoothed = smoothGradient(val, 3.0, 2.0);

				bool isBodyPart = sample - smoothed > 0;

				if (isBodyPart) {
					SDL_Point p = { x, y };
					enclosurePoints[numBodyPoints++] = p;
					bodyPoints[x + width * y] = p;
				}
				else {
					SDL_Point p = { -1, -1 };
					bodyPoints[x + width * y] = p;
				}
			}
		}

		SDL_EnclosePoints(enclosurePoints, numBodyPoints, NULL, &bounds);

		delete enclosurePoints;

		cout << "Body Bounds: {" << bounds.x << ", " << bounds.y << ", " << bounds.w << ", " << bounds.h << "}" << endl;
	}

	void MakeSprite() {
		SDL_Color spriteColor = { getRand01() * 255, getRand01() * 255, getRand01() * 255 };

		unsigned char* pixels = new unsigned char[width * height * 4];

		int eyeCenterX = bounds.x + (bounds.w / 2);
		int eyeCenterY = bounds.y < height ? bounds.y + 30 : bounds.h / 2;

		Circle eyeball = { eyeCenterX, eyeCenterY, 10 };
		Circle pupil = { eyeCenterX, eyeCenterY, 2 };

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				const unsigned int offset = (width * 4 * y) + x * 4;
				SDL_Color pixelColor = { 0, 0, 0, SDL_ALPHA_OPAQUE };
				SDL_Point p = bodyPoints[x + this->width * y];
				bool isBodyPart = SDL_PointInRect(&p, &bounds);

				pixels[offset + 0] = isBodyPart ? spriteColor.b : 0;		// b
				pixels[offset + 1] = isBodyPart ? spriteColor.g : 0;		// g
				pixels[offset + 2] = isBodyPart ? spriteColor.r : 0;		// r

				pixels[offset + 3] = SDL_ALPHA_OPAQUE;  // alpha

				if (eyeball.CheckPoint(x, y)) {
					pixels[offset + 0] = white.b;
					pixels[offset + 1] = white.g;
					pixels[offset + 2] = white.r;
					pixels[offset + 3] = white.a;
				}

				if (pupil.CheckPoint(x, y)) {
					pixels[offset + 0] = black.b;
					pixels[offset + 1] = black.g;
					pixels[offset + 2] = black.r;
					pixels[offset + 3] = black.a;
				}
			}
		}

		SDL_UpdateTexture(texture, NULL, &pixels[0], width * 4);

		delete pixels;
		delete bodyPoints;
	}
};

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

	GenSprite* guy = new GenSprite(renderer, 128, 128);
	//guy->MakeSprite();

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
				guy->GenerateBody();
				guy->MakeSprite();
            }

            if (mEvent.type == SDL_MOUSEBUTTONUP) {
                mouseIsDown = false;
            }

            if (mEvent.type == SDL_MOUSEMOTION && mouseIsDown) {
                mousePos.x = mEvent.motion.x;
                mousePos.y = mEvent.motion.y;
            }

        }
		
		guy->Render(screenWidth / 2, screenHeight / 2);

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
