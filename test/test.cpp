#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../TerrainGenerator/Noise.h"
#include "../TerrainGenerator/HeightMap.h"
#include "../Texture.h"

using namespace std;

SDL_Color deep_water = {0,0,205};
SDL_Color water = {0,191,255};
SDL_Color sand = {245,222,179};
SDL_Color grass = {0, 128, 0};
SDL_Color mountain = {139, 69, 19};
SDL_Color snow = {255, 250, 250};

SDL_Texture* generateTexture(SDL_Renderer* renderer, HeightMap* heightMap) {
    int height = heightMap->getMapHeight();
    int width = heightMap->getMapWidth();

    SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, width, height);

    unsigned char* pixels = new unsigned char[width * height * 4];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const unsigned int offset = ( width * 4 * y ) + x * 4;
            double value = heightMap->getHeightAt(x, y);

            SDL_Color* current = &water;
            if (value < .15) { current = &deep_water; }
            if (value >= .15 && value < .3) { current = &water; }
            if (value >= .3 && value < .4) { current = &sand; }
            if (value >= .4 && value < .7) { current = &grass; }
            if (value >= .7 && value < .9) { current = &mountain; }
            if (value > .9) { current = &snow; }

            pixels[ offset + 0 ] = current->b;        // b
            pixels[ offset + 1 ] = current->g;        // g
            pixels[ offset + 2 ] = current->r;        // r
            pixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a

            // cout << to_string(x) << ", " << to_string(y) << ": " << to_string() << "\n";
        }
    }

    SDL_UpdateTexture( tex, NULL, &pixels[0], width * 4);


    return tex;
}


int main( int argc, char* args[] ) 
{ 

    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Event       mEvent;
    bool running = true;
    int Width = 800;
    int Height = 600;

    Noise* n = new Noise();

    int seed = 100;

    double scale = 100.0;
    int octaves = 5;
    double persistance = .5;
    double lacunarity = 2.0;
    Vector2D* center = new Vector2D(0, 0);

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 Window", 100, 100, Width, Height, 0);
    if(window==NULL)
    {   
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // cout << tex->GetWidth() << ", " << tex->GetHeight() << endl;

    HeightMap* heightMap = n->generateHeightMap( Width, Height, seed, scale, octaves, persistance, lacunarity, center);
    SDL_Texture* tex = generateTexture(renderer, heightMap);


    while (running) {
        
        bool changed = false;
        SDL_RenderClear(renderer);

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

                if (mEvent.key.keysym.sym == SDLK_d) {
                    Vector2D* temp = new Vector2D(center->x() + 1, center->y());
                    center = temp;
                    delete(temp);

                    // cout << "New center x: " << center->x() << ", y: " << center->y() << endl;
                    heightMap = n->generateHeightMap( Width, Height, seed, scale, octaves, persistance, lacunarity, center);
                }

                if (mEvent.key.keysym.sym == SDLK_a) {
                    Vector2D* temp = new Vector2D(center->x() - 1, center->y());
                    center = temp;
                    delete(temp);

                    // cout << "New center x: " << center->x() << ", y: " << center->y() << endl;
                    heightMap = n->generateHeightMap( Width, Height, seed, scale, octaves, persistance, lacunarity, center);
                }

                changed = true;
            }

            //If user clicks the mouse
            if (mEvent.type == SDL_MOUSEBUTTONDOWN) {
                double height = heightMap->getHeightAt(mEvent.motion.x, mEvent.motion.y);
                cout << "Height at location: " << to_string(height) << endl;
            }

        }

        if (changed) {
            SDL_DestroyTexture(tex);
            SDL_Texture* tex = generateTexture(renderer, heightMap);
            SDL_RenderCopy( renderer, tex, NULL, NULL );
        } else {
            SDL_RenderCopy( renderer, tex, NULL, NULL );
        }

        SDL_RenderPresent(renderer);
    }


    SDL_DestroyWindow(window); 

    SDL_Quit(); 

    return 0;   
}