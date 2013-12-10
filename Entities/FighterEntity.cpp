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
	componentMap["dimension"] = new DimensionComponent(50, 400, 32, 32); // x, y, w, h
	componentMap["velocity"] = new VelocityComponent(0, 0);
	componentMap["player_motion"] = new PlayerMotionComponent(100, 200, 2); // X velocity, Y velocity, number of jumps
	componentMap["collision"] = new CollisionComponent();

	// Set up animation states. Map has the state as a key, and an animation object which needs a column position, 
	// number of frames, and whether it's repeating. If it's repeating, it needs a next state as well.
	map<string, Animation*> state_map;
	state_map["IDLE"] = new Animation(18, 8);
	state_map["IDLE_READY"] = new Animation(19, 8);
	state_map["RUNNING"] = new Animation(32, 8);
	state_map["SLOWING"] = new Animation(32, 8);
	state_map["FALLING"] = new Animation(23, 6);
	state_map["JUMPING"] = new Animation(24, 4, true, "FALLING");

	componentMap["animation"] = new AnimationComponent("media/fighter-spritesheet.png", state_map, 120); //sprite sheet location, sprite size
}
