#include "WallEntity.h"


WallEntity::WallEntity(long id, SDL_Rect* dimensions){
	mID = id;

	systemFlags.push_back("render");
	systemFlags.push_back("collides");

	componentMap["texture"] = new TextureComponent("media/wall.png");
	componentMap["dimension"] = new DimensionComponent(dimensions->x, dimensions->y, dimensions->w, dimensions->h);
}

