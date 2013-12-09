#include "FighterEntity.h"


FighterEntity::FighterEntity(long id){
	mID = id;

	systemFlags.push_back("player_input");
	systemFlags.push_back("render");
	systemFlags.push_back("move");
	systemFlags.push_back("bounce");
	systemFlags.push_back("collides");
	systemFlags.push_back("player_resolves");
	systemFlags.push_back("gravity");
	systemFlags.push_back("friction");

	componentMap["texture"] = new TextureComponent("media/fighter.png");
	componentMap["dimension"] = new DimensionComponent(50, 400, 32, 32);
	componentMap["velocity"] = new VelocityComponent(0, 0);
	componentMap["player_motion"] = new PlayerMotionComponent(100, 200, 2); // X velocity, Y velocity, number of jumps
	componentMap["collision"] = new CollisionComponent();
}
