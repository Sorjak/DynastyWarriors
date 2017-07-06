#include <iostream>
#include <string>
#include <memory>
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

void RaiseLand(shared_ptr<MapChunk> chunk, int amountToRaise) {
    shared_ptr<HeightMap> originalMap = chunk->getHeightMap();
    cout << originalMap->getHeightAt(0, 0) << endl;
    if (originalMap != NULL) {
        int width = originalMap->getMapWidth();
        int height = originalMap->getMapHeight();
        shared_ptr<HeightMap> newMap(new HeightMap(width, height));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float oldValue = originalMap->getHeightAt(x, y);
                float newValue = oldValue + (amountToRaise * .001);
                // cout << "Setting new value: " << newValue << endl;
                newMap->setHeightAt(x, y, newValue);
            }
        }


        chunk->Load(newMap);
    } else {
        cout << "Failed to raise land" << endl;
    }
}


int main( int argc, char* args[] ) 
{ 
    cout << "starting test" << endl;

    SDL_Window     *window;
    SDL_Renderer   *renderer;
    SDL_Event       mEvent;

    bool running = true;
    int screenWidth = 800;
    int screenHeight = 600;

    int islandWidth = screenWidth * 2;
    int islandHeight = screenHeight * 2;

    int chunksPerIsland = 10 * 10;

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

    map<pair<int, int>, shared_ptr<Island>> islands;

    pair<int, int> coord = make_pair(0, 0);
    // Noise* n = new Noise(0, 1000);
    shared_ptr<Noise> n(new Noise(0, 1000));

    SDL_Rect islandBounds = {0, 0, islandWidth, islandHeight};
    // Island* island = new Island(islandBounds, n, 40);
    shared_ptr<Island> island(new Island(islandBounds, n, chunksPerIsland));
    islands[coord] = island;

    bool mouseIsDown = false;

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
                mouseIsDown = true;
            }

            if (mEvent.type == SDL_MOUSEBUTTONUP) {
                mouseIsDown = false;
            }

            if (mEvent.type == SDL_MOUSEMOTION && mouseIsDown) {
                mousePos.x = mEvent.motion.x;
                mousePos.y = mEvent.motion.y;
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
                    shared_ptr<Noise> n(new Noise(0, 1000));

                    SDL_Rect islandBounds = {x, y, islandWidth, islandHeight};
                    shared_ptr<Island> island(new Island(islandBounds, n, chunksPerIsland));   
                    islands[current] = island;
                }
            }
        }

        for (auto i = islands.begin(); i != islands.end(); ++i)
        {
            shared_ptr<Island> island = i->second;

            island->Update(&view_rect);

            if (selectAction) {
                SDL_Rect islandBounds = island->getWorldRect();
                SDL_Point worldMouse = {mousePos.x + view_rect.x, mousePos.y + view_rect.y};

                if (SDL_PointInRect(&worldMouse, &islandBounds)) {
                    cout << "Island coords: " << islandBounds.x << ", " << islandBounds.y << endl;
                    shared_ptr<MapChunk> c = island->GetChunkAtPoint(worldMouse);
                    if (c != NULL) {
                        // c->Select(true);
                        RaiseLand(c, 5);
                    }
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