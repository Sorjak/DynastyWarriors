//==============================================================================
/*
    Texture class for wrapping SDL Textures
    3/13/2014
    SDLTutorials.com
    Tim Jones
    Modified by Uli
*/
//==============================================================================
#ifndef __TEXTURE_H__
    #define __TEXTURE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <memory>

#include "TerrainGenerator/HeightMap.h"



class Texture {
    private:
        std::string Filename;

        int Width = 0;
        int Height = 0;

        SDL_Renderer* Renderer = NULL;
        SDL_Texture* SDLTexture = NULL;


        void PutPixelColor(SDL_Surface*, int, int, Uint32);

        SDL_Color deep_water = {0,0,205};
        SDL_Color water = {0,191,255};
        SDL_Color sand = {245,222,179};
        SDL_Color grass = {0, 128, 0};
        SDL_Color mountain = {139, 69, 19};
        SDL_Color snow = {255, 250, 250};

    public:
        Texture();
        ~Texture();

        SDL_Surface* GetSurface(SDL_Renderer*, int, int, int);

        bool Create(SDL_Renderer*, SDL_Surface*);
        bool Create(SDL_Renderer*, int, int);

        bool Update(std::shared_ptr<HeightMap>);
        bool Load(SDL_Renderer* Renderer, std::string Filename);

        void Render(int X, int Y);

        void Render(int X, int Y, int Width, int Height);

        void Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight);

        int GetWidth();
        int GetHeight();
};

#endif