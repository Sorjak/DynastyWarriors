//==============================================================================
#include "Texture.h"
#include "Log.h"

//==============================================================================
Texture::Texture() {
}

//------------------------------------------------------------------------------
Texture::~Texture() {
    if(SDLTexture) {
        SDL_DestroyTexture(SDLTexture);
        SDLTexture = NULL;
    }
}


SDL_Surface* Texture::GetSurface(SDL_Renderer* Renderer, int width, int height, int depth) {
    SDL_Surface* TempSurface = SDL_CreateRGBSurface(0, width, height, depth, 0, 0, 0, 0);
    if(TempSurface == NULL) {
        Log("Unable to create surface");
        return NULL;
    }

    return TempSurface;
}

//==============================================================================
bool Texture::Create(SDL_Renderer* Renderer, int width, int height, int depth) {
    SDL_Surface* surf = GetSurface(Renderer, width, height, depth);

    if((SDLTexture = SDL_CreateTextureFromSurface(Renderer, surf)) == NULL) {
        Log("Unable to create SDL Texture");
        return false;
    }

    // Grab dimensions
    SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);

    SDL_FreeSurface(surf);

    return true;
}


bool Texture::Create(SDL_Renderer* Renderer, SDL_Surface* surf) {
    if((SDLTexture = SDL_CreateTextureFromSurface(Renderer, surf)) == NULL) {
        Log("Unable to create SDL Texture");
        return false;
    }

    // Grab dimensions
    SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);

    SDL_FreeSurface(surf);

    return true;
}


//==============================================================================
bool Texture::Load(SDL_Renderer* Renderer, std::string Filename) {
    if(Renderer == NULL) {
        Log("Bad SDL renderer passed");
        return false;
    }

    this->Renderer = Renderer;
    this->Filename = Filename;

    SDL_Surface* TempSurface = IMG_Load(Filename.c_str());
    if(TempSurface == NULL) {
        Log("Unable to load image : %s : %s", Filename.c_str(), IMG_GetError());
        return false;
    }

    // Convert SDL surface to a texture
    if((SDLTexture = SDL_CreateTextureFromSurface(Renderer, TempSurface)) == NULL) {
        Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
        return false;
    }

    // Grab dimensions
    SDL_QueryTexture(SDLTexture, NULL, NULL, &Width, &Height);

    //Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);

    SDL_FreeSurface(TempSurface);

    return true;
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y) {
    Render(X, Y, Width, Height);
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height) {
    SDL_Rect Destination = {X, Y, Width, Height};

    SDL_RenderCopy(Renderer, SDLTexture, NULL, &Destination);
}

//------------------------------------------------------------------------------
void Texture::Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight) {
    SDL_Rect Source = {SX, SY, SWidth, SHeight};
    SDL_Rect Destination = {X, Y, Width, Height};

    SDL_RenderCopy(Renderer, SDLTexture, &Source, &Destination);
}

//------------------------------------------------------------------------------
int Texture::GetWidth()  { return Width;  }
int Texture::GetHeight() { return Height; }

//==============================================================================


void Texture::PutPixelColor(SDL_Surface * surface, int x, int y, Uint32 color)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint32));
    *((Uint32*)pixel) = color;
}