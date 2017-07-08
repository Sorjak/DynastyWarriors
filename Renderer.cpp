#include "Renderer.h"

Renderer::Renderer(SDL_Window* window): 
{
    this->mWindow   = window;
    this->mRenderer = nullptr;
    this->mFirstRun = true;
    this->mContext  = SDL_GL_GetCurrentContext();

    SDL_GL_MakeCurrent(window, nullptr);

    std::thread t(&Renderer::renderJob, this);

    t.detach();
}


void Renderer::render()
{
    // Clear
    if (SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255) < 0)
    {
        std::cerr << "Error clearing: " << SDL_GetError() << std::endl;
    }

    // Draw
    

    
    // Display
    SDL_RenderPresent(mRenderer);
}

void Renderer::renderJob()
{
    while (true)
    {
        if (mFirstRun)
        {
            SDL_GL_MakeCurrent(mWindow, mContext);

            mFirstRun = false;
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
        if (mRenderer != nullptr)
        {
            render();
        }
    }
}

