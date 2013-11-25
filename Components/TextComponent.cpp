#include "TextComponent.h"


TextComponent::TextComponent(const char* text){
	mFont = TTF_OpenFont( "../media/SourceSansPro-Regular.ttf", 28 );
}


TextComponent::~TextComponent(){}
