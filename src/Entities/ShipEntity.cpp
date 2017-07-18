#include "ShipEntity.h"


ShipEntity::ShipEntity(long id) {
	mID = id;

	systemFlags.push_back("player_input");
	systemFlags.push_back("render");
	systemFlags.push_back("move");
	systemFlags.push_back("bounce");
	systemFlags.push_back("collides");
	systemFlags.push_back("gravity");

	componentMap["texture"] = new TextureComponent("media/ship.png");
	componentMap["dimension"] = new DimensionComponent(1, 1, 32, 32, 1);
	componentMap["velocity"] = new VelocityComponent(0, 0);
	
}

