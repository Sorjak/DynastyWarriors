#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../TerrainGenerator/Noise.h"
#include "../TerrainGenerator/HeightMap.h"
#include "../Texture.h"

using namespace std;


// SDL_Texture* generateTexture(SDL_Renderer* renderer, HeightMap* heightMap) {
//     int height = heightMap->getMapHeight();
//     int width = heightMap->getMapWidth();

//     SDL_Texture* mainTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
//         SDL_TEXTUREACCESS_STREAMING, width, height);

//     unsigned char* pixels = new unsigned char[width * height * 4];

//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             const unsigned int offset = ( width * 4 * y ) + x * 4;
//             double value = heightMap->getHeightAt(x, y);

//             SDL_Color* current = &water;
//             if (value < .15) { current = &deep_water; }
//             if (value >= .15 && value < .3) { current = &water; }
//             if (value >= .3 && value < .4) { current = &sand; }
//             if (value >= .4 && value < .7) { current = &grass; }
//             if (value >= .7 && value < .9) { current = &mountain; }
//             if (value > .9) { current = &snow; }

//             pixels[ offset + 0 ] = current->b;        // b
//             pixels[ offset + 1 ] = current->g;        // g
//             pixels[ offset + 2 ] = current->r;        // r
//             pixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a

//             // cout << to_string(x) << ", " << to_string(y) << ": " << to_string() << "\n";
//         }
//     }

//     SDL_UpdateTexture( mainTex, NULL, &pixels[0], width * 4);


//     return mainTex;
// }


int main( int argc, char* args[] ) 
{ 

    cout << "starting test" << endl;
    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Event       mEvent;


    bool running = true;
    int screenWidth = 1280;
    int screenHeight = 720;

    int mapWidth = 3200;
    int mapHeight = 2400;

    int seed = 0;

    int currentFPS = 60;
    int frameStartTime;
    // int frameEndTime;
    int fpsTimer = SDL_GetTicks();
    int framesElapsed = 0;

    float submapScale = .2;
    int scaledWidth = screenWidth * submapScale;
    int scaledHeight = screenHeight * submapScale;

    SDL_Rect FPS_rect = {5, 5, 36, 24};
    SDL_Rect map_rect = {0, 0, screenWidth, screenHeight};
    SDL_Rect view_rect = {0, 0, screenWidth, screenHeight};
    // SDL_Rect submap_rect = {screenWidth / 2, screenHeight / 2, scaledWidth, scaledHeight};

    Vector2D* center = new Vector2D(0, 0);

    SDL_Init(SDL_INIT_EVERYTHING);

    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return 1;
    }
    TTF_Font* mFont = TTF_OpenFont("../media/SourceSansPro-Regular.ttf", 24 );
    if(!mFont) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL2 Window", 100, 100, screenWidth, screenHeight + 100, SDL_WINDOW_SHOWN);
    if(window==NULL)
    {   
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // cout << mainTex->GetWidth() << ", " << mainTex->GetHeight() << endl;

    Noise* n = new Noise(seed);
    HeightMap* heightMap = n->generateHeightMap(mapWidth, mapHeight, center);
    HeightMap* submap = n->generateSubMap(heightMap, &map_rect);
    Texture* mainTex = new Texture();//generateTexture(renderer, submap); 
    mainTex->Create(renderer, screenWidth, screenHeight);
    mainTex->Update(submap);
    // SDL_Texture* subTex = NULL;

    bool fullMap = true;

    // int view_x = 0;
    // int view_y = 0;

    while (running) {
        
        frameStartTime = SDL_GetTicks();
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

                if (mEvent.key.keysym.sym == SDLK_a) {
                    view_rect.x = max(-mapWidth, view_rect.x - 10);
                    changed = true;
                }

                if (mEvent.key.keysym.sym == SDLK_d) {
                    view_rect.x = min(mapWidth, view_rect.x + 10);
                    changed = true;
                }

                if (mEvent.key.keysym.sym == SDLK_w) {
                    view_rect.y = max(-mapHeight, view_rect.y - 10);
                    changed = true;
                }

                if (mEvent.key.keysym.sym == SDLK_s) {
                    view_rect.y = min(mapHeight, view_rect.y + 10);
                    changed = true;
                }


                // changed = true;
            }

            //If user clicks the mouse
            if (mEvent.type == SDL_MOUSEBUTTONDOWN) {
            //     if (fullMap) {
            //         cout << "Switching to submap" << endl;
            //         int x = min(max(scaledWidth / 2, mEvent.motion.x), screenWidth - (scaledWidth / 2)); 
            //         int y = min(max(scaledHeight / 2, mEvent.motion.y), screenHeight - (scaledHeight / 2)); 

            //         SDL_Rect trim = {x - (scaledWidth / 2), y - (scaledHeight / 2), scaledWidth, scaledHeight};

            //         cout << "Rect x: " << trim.x << " y: " << trim.y << ", w: " << trim.w << " h: " << trim.h << endl;

            //         HeightMap* temp = n->generateSubMap(submap, &trim);
            //         subTex = generateTexture(renderer, temp);
            //     }

            //     fullMap = !fullMap;
            }

        }



        if (changed) {
            n->updateSubMap(heightMap, submap, &view_rect);
            mainTex->Update(submap);
        }

        mainTex->Render(map_rect.x, map_rect.y); 


        //Calculate FPS
        if (frameStartTime - fpsTimer >= 1000) {
            currentFPS = framesElapsed;
            framesElapsed = 0;
            fpsTimer = SDL_GetTicks();
        } else {
            framesElapsed++;
        }

        // cout << to_string(currentFPS) << endl;
        SDL_Color color; color.r = 255; color.b = 255; color.g = 255;
        string fpsString = "FPS: ";

        fpsString += to_string(currentFPS);

        SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, fpsString.c_str(), color );
        SDL_Texture* renderTex = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_RenderCopy( renderer, renderTex, NULL, &FPS_rect );
        SDL_FreeSurface( textSurface );
        SDL_free( renderTex );

        SDL_RenderPresent(renderer);
    }


    SDL_DestroyWindow(window); 

    SDL_Quit(); 

    return 0;   
}