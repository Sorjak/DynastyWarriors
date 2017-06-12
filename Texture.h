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

class Texture {
    private:
        std::string Filename;

        int Width = 0;
        int Height = 0;

        SDL_Renderer* Renderer = NULL;
        SDL_Texture* SDLTexture = NULL;


        void PutPixelColor(SDL_Surface*, int, int, Uint32);

    public:
        Texture();
        ~Texture();

        SDL_Surface* GetSurface(SDL_Renderer*, int, int, int);

        bool Create(SDL_Renderer*, SDL_Surface*);
        bool Create(SDL_Renderer*, int, int, int);
        bool Load(SDL_Renderer* Renderer, std::string Filename);

        void Render(int X, int Y);

        void Render(int X, int Y, int Width, int Height);

        void Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight);

        int GetWidth();
        int GetHeight();
};

#endif