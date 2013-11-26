#include "ShipEntity.h"


ShipEntity::ShipEntity(long id) {
	mID = id;

	systemFlags.push_back("input");
	systemFlags.push_back("render");
	systemFlags.push_back("move");
	systemFlags.push_back("bounce");
	systemFlags.push_back("collides");

	componentMap["texture"] = new TextureComponent("media/ship.png");
	componentMap["dimension"] = new DimensionComponent(0, 0, 32, 32);
	componentMap["velocity"] = new VelocityComponent(1, 1);
	
}

