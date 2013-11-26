#include "WallEntity.h"


WallEntity::WallEntity(long id, int x, int y){
	mID = id;

	systemFlags.push_back("render");
	systemFlags.push_back("collides");

	componentMap["texture"] = new TextureComponent("media/wall.png");
	componentMap["dimension"] = new DimensionComponent(x, y, 32, 32);
}

