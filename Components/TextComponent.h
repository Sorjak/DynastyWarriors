#pragma once
#include "../Components/basecomponent.h"
#include <SDL2/SDL_ttf.h>

class TextComponent :
	public BaseComponent
{
public:
	TextComponent(const char*);
	~TextComponent();

	SDL_Texture* mTexture;
	TTF_Font* mFont;
};

