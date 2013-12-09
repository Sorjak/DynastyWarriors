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
	systemFlags.push_back("animation");

	//componentMap["texture"] = new TextureComponent("media/fighter.png");
	componentMap["dimension"] = new DimensionComponent(50, 400, 120, 120); // x, y, w, h
	componentMap["velocity"] = new VelocityComponent(0, 0);
	componentMap["player_motion"] = new PlayerMotionComponent(100, 200, 2); // X velocity, Y velocity, number of jumps
	componentMap["collision"] = new CollisionComponent();

	// Set up animation states. Map has the state as a key, and a pair holding the position of the animation, and how long it is in frames
	map<string, pair<int, int>> state_map;
	state_map["IDLE"] = make_pair<int, int>(18, 8);
	state_map["IDLE_READY"] = make_pair<int, int>(19, 8);
	state_map["RUNNING"] = make_pair<int, int>(32, 8);

	componentMap["animation"] = new AnimationComponent("media/fighter-spritesheet.png", state_map, 120); //sprite sheet location, sprite size
}
