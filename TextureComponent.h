#pragma once

#include <SDL2/SDL_image.h>

#include "basecomponent.h"
class TextureComponent : public BaseComponent
{
public:
	TextureComponent(const std::string filename);
	~TextureComponent();

	SDL_Texture* getTexture(SDL_Renderer*);

	std::string mFilename;
	SDL_Texture* mTexture;
};

