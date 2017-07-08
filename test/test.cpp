#include <iostream>
#include <string>
#include <memory>
#include <random>
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

const int screenWidth = 800;
const int screenHeight = 600;

const int islandWidth = screenWidth * 2;
const int islandHeight = screenHeight * 2;

const int chunksPerIsland = 50 * 50;

const float morphPowerMod = .005;


SDL_Rect landMorphBox = {0, 0, 150, 150};

int currentFPS = 60;
int frameStartTime;

int fpsTimer = 0;
int framesElapsed = 0;

SDL_Rect FPS_rect = {5, 5, 200, 24};
SDL_Rect view_rect = {0, 0, screenWidth, screenHeight};

map<pair<int, int>, shared_ptr<Island>> islands;

int distanceSquared(int x1, int y1, int x2, int y2) {
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

struct Circle {
    int x, y;
    int r;

    bool CheckPoint(int x2, int y2) {
        int distanceSqr = distanceSquared(x, y, x2, y2);
        return distanceSqr < (r * r);
    }

    float DistanceFromCenter(int x2, int y2) {
        return sqrt(distanceSquared(x, y, x2, y2));
    }
};

void MorphLand(shared_ptr<MapChunk> chunk, SDL_Point point, bool raise) {
    shared_ptr<HeightMap> originalMap = chunk->getHeightMap();
    SDL_Rect chunkRect = chunk->getWorldRect();
    Circle c = {point.x, point.y, landMorphBox.w / 2};

    if (originalMap != NULL) {
        int width = originalMap->getMapWidth();
        int height = originalMap->getMapHeight();
        shared_ptr<HeightMap> newMap(new HeightMap(width, height));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float oldValue = originalMap->getHeightAt(x, y);

                if (c.CheckPoint(chunkRect.x + x, chunkRect.y + y)) {
                    float val = 1 - (c.DistanceFromCenter(chunkRect.x + x, chunkRect.y + y) / c.r);
                    float curved = pow(val, 2.7) / (pow(val, 2.7) + pow(4.5 - 4.5 * val, 2.7));
                    float newValue = oldValue;

                    if (raise)
                        newValue += curved * morphPowerMod;
                    else 
                        newValue -= curved * morphPowerMod;

                    newMap->setHeightAt(x, y, newValue);
                } else {
                    newMap->setHeightAt(x, y, oldValue);
                }
            }
        }

        chunk->Load(newMap);
    }
}

void MakeIsland(int x, int y) {
    int seed = rand() * 1000;
    shared_ptr<Noise> n(new Noise(seed));
    SDL_Rect islandBounds = {x, y, islandWidth, islandHeight};
    pair<int, int> coord = make_pair(x, y);

    shared_ptr<Island> island(new Island(islandBounds, n, chunksPerIsland));
    islands[coord] = island;
}

void UpdateAll(bool mouseIsDown, SDL_Point mousePos, bool raise) {
    int leftEdge = view_rect.x  / screenWidth;
    int topEdge = view_rect.y / screenHeight;

    for (int x = leftEdge - 1 ; x < leftEdge + 2; ++x)
    {
        for (int y = topEdge - 1; y < topEdge + 2; ++y)
        {
            pair<int, int> current = make_pair(x, y);
            if (islands.count(current) == 0) {
                MakeIsland(x, y);
            }
        }
    }

    for (auto i = islands.begin(); i != islands.end(); ++i)
    {
        shared_ptr<Island> island = i->second;

        island->Update(&view_rect);

        if (mouseIsDown) {
            SDL_Point worldMouse = {mousePos.x + view_rect.x, mousePos.y + view_rect.y};
            SDL_Rect mouseBox = {
                mousePos.x + view_rect.x - (landMorphBox.w / 2), 
                mousePos.y + view_rect.y - (landMorphBox.h / 2),
                landMorphBox.w,
                landMorphBox.h
            };

            vector<shared_ptr<MapChunk>> chunks = island->GetChunksInRect(&mouseBox);
            for (auto c = chunks.begin(); c != chunks.end(); ++c) {
                MorphLand((*c), worldMouse, raise);
            }
        }
        
    }
}


void RenderAll(SDL_Renderer* renderer, TTF_Font* mFont) {
    
    SDL_RenderClear(renderer);

    for (auto i = islands.begin(); i != islands.end(); ++i)
    {
        i->second->Render(renderer, &view_rect);
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

    MakeIsland(0, 0);

    bool mouseIsDown = false;
    bool raise = false;

    // SDL_Point temp;
    // UpdateAll(mouseIsDown, temp, raise);
    // RenderAll(renderer, mFont);

    while (running) {
        frameStartTime = SDL_GetTicks();

        
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
                mouseIsDown = true;

                raise = mEvent.button.button == SDL_BUTTON_LEFT;
            }

            if (mEvent.type == SDL_MOUSEBUTTONUP) {
                mouseIsDown = false;
            }

            if (mEvent.type == SDL_MOUSEMOTION && mouseIsDown) {
                mousePos.x = mEvent.motion.x;
                mousePos.y = mEvent.motion.y;
            }

        }

        thread update(UpdateAll, mouseIsDown, mousePos, raise);
        update.join();

        thread render(RenderAll, renderer, mFont);
        render.join();
    }

    SDL_DestroyWindow(window); 

    SDL_Quit(); 

    return 0;   
}
