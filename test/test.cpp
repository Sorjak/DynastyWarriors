#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../TerrainGenerator/Noise.h"
#include "../TerrainGenerator/HeightMap.h"
#include "../TerrainGenerator/MapChunk.h"
#include "../TerrainGenerator/Island.h"
#include "../Texture.h"

using namespace std;

int main( int argc, char* args[] ) 
{ 
    cout << "starting test" << endl;

    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Event       mEvent;

    bool running = true;
    int screenWidth = 800;
    int screenHeight = 600;

    int mapWidth = 1600;
    int mapHeight = 1200;

    int currentFPS = 60;
    int frameStartTime;

    int fpsTimer = SDL_GetTicks();
    int framesElapsed = 0;

    SDL_Rect FPS_rect = {5, 5, 200, 24};
    SDL_Rect view_rect = {0, 0, screenWidth, screenHeight};

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

    window = SDL_CreateWindow("SDL2 Window", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if(window==NULL)
    {   
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    map<pair<int, int>, Island*> islands;

    // for (int x = 0; x < (mapWidth / screenWidth); ++x) {
    //     for (int y = 0; y < (mapHeight / screenHeight); ++y) {
    //         Vector2D* coord = new Vector2D(x, y);
    //         Noise* n = new Noise(0, 1000);

    //         SDL_Rect islandBounds = {x, y, screenWidth, screenHeight};
    //         Island* island = new Island(islandBounds, n, 40);   
    //         islands[coord] = island;   
    //     }
    // }


    pair<int, int> coord = make_pair(0, 0);
    Noise* n = new Noise(0, 1000);

    SDL_Rect islandBounds = {0, 0, screenWidth, screenHeight};
    Island* island = new Island(islandBounds, n, 40);   
    islands[coord] = island;

    while (running) {
        
        frameStartTime = SDL_GetTicks();
        bool selectAction = false;
        SDL_Point mousePos;
        
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
                    // view_rect.x = max(0, view_rect.x - 10);
                    view_rect.x -= 10;
                }

                if (mEvent.key.keysym.sym == SDLK_d) {
                    // view_rect.x = min(mapWidth - view_rect.w, view_rect.x + 10);
                    view_rect.x += 10;
                }

                if (mEvent.key.keysym.sym == SDLK_w) {
                    // view_rect.y = max(0, view_rect.y - 10);
                    view_rect.y -= 10;
                }

                if (mEvent.key.keysym.sym == SDLK_s) {
                    // view_rect.y = min(mapHeight - view_rect.h, view_rect.y + 10);
                    view_rect.y += 10;
                }
            }

            //If user clicks the mouse
            if (mEvent.type == SDL_MOUSEBUTTONDOWN) {
                
                mousePos.x = mEvent.button.x;
                mousePos.y = mEvent.button.y;
                selectAction = true;
            }

        }

        int leftEdge = view_rect.x  / screenWidth;
        int topEdge = view_rect.y / screenHeight;

        for (int x = leftEdge - 1 ; x < leftEdge + 2; ++x)
        {
            for (int y = topEdge - 1; y < topEdge + 2; ++y)
            {
                pair<int, int> current = make_pair(x, y);
                if (islands.count(current) == 0) {
                    Noise* n = new Noise(0, 1000);

                    SDL_Rect islandBounds = {x, y, screenWidth, screenHeight};
                    Island* island = new Island(islandBounds, n, 40);   
                    islands[current] = island;
                }
            }
        }

        for (auto i = islands.begin(); i != islands.end(); ++i)
        {
            Island* island = i->second;

            island->Update(&view_rect);

            if (selectAction) {
                SDL_Rect islandBounds = island->getWorldRect();
                SDL_Point worldMouse = {mousePos.x + view_rect.x, mousePos.y + view_rect.y};

                if (SDL_PointInRect(&worldMouse, &islandBounds)) {
                    cout << "Island coords: " << islandBounds.x << ", " << islandBounds.y << endl;
                    MapChunk* c = island->GetChunkAtPoint(worldMouse);
                    if (c != NULL)
                        c->Select(true);
                }
            }

            island->Render(renderer, &view_rect);
        }

        //Calculate FPS
        if (frameStartTime - fpsTimer >= 1000) {
            currentFPS = framesElapsed;
            framesElapsed = 0;
            fpsTimer = SDL_GetTicks();
        } else {
            framesElapsed++;
        }

        // cout << to_string(currentFPS) << endl;
        SDL_Color color; color.r = 255; color.b = 128; color.g = 128;
        string ui_string = "X:" + to_string(view_rect.x) + ", Y:" + to_string(view_rect.y);

        ui_string += " | FPS: " + to_string(currentFPS);

        SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, ui_string.c_str(), color );
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