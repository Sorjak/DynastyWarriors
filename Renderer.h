#pragma once

#include <iostream>
#include <thread>
#include <SDL2/SDL.h>

class Renderer
{
    public:
        Renderer(SDL_Window* window);

    private:
        void renderJob();
        void render();

        SDL_GLContext mContext;
        SDL_Renderer* mRenderer;
        SDL_Window* mWindow;
        bool mFirstRun;
};

