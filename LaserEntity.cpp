#include "LaserEntity.h"


LaserEntity::LaserEntity(){
	systemFlags.push_back("render");
	systemFlags.push_back("move");

	componentMap["texture"] = new TextureComponent("media/redlaser.png");
	componentMap["dimension"] = new DimensionComponent(200, 200, 64, 32);
	componentMap["velocity"] = new VelocityComponent(0, 0);
	
}




