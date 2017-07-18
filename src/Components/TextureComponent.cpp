#include "TextureComponent.h"
#include <assert.h>

TextureComponent::TextureComponent(const string filename)
{
	mFilename = filename;
	mTexture = NULL;
}


TextureComponent::~TextureComponent()
{
	//delete mTexture;
}

SDL_Texture* TextureComponent::getTexture(SDL_Renderer *renderer) {
	if (mTexture == NULL) {
		const char *realname =  mFilename.c_str();
		mTexture = IMG_LoadTexture(renderer, realname);
	}
	
	return mTexture;
	
}
