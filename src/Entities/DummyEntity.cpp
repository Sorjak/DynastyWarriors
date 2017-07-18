#include "DummyEntity.h"


DummyEntity::DummyEntity(long id){
	mID = id;

	systemFlags.push_back("render");
	systemFlags.push_back("move");
	systemFlags.push_back("bounce");
	systemFlags.push_back("collides");
	systemFlags.push_back("gravity");
	systemFlags.push_back("friction");
	systemFlags.push_back("animation");
	systemFlags.push_back("player_resolves");

	componentMap["dimension"] = new DimensionComponent(500, 400, 64, 64, -1); // x, y, w, h, facing
	componentMap["velocity"] = new VelocityComponent(0, 0);
	componentMap["collision"] = new CollisionComponent();
	componentMap["state"] = new StateComponent("IDLE", "GROUND", "IDLE");

	map<string, Animation*> state_map;
	state_map["IDLE"] = new Animation(18, 8);
	state_map["IDLE_READY"] = new Animation(19, 8);
	state_map["RUNNING"] = new Animation(32, 8);
	state_map["SLOWING"] = new Animation(32, 8);
	state_map["FALLING"] = new Animation(23, 6);
	state_map["JUMPING"] = new Animation(24, 4, false, "FALLING");
	state_map["PUNCHING"] = new Animation(29, 4, false, "IDLE");
	state_map["KICKING"] = new Animation(26, 5, false, "IDLE");

	componentMap["animation"] = new AnimationComponent("media/fighter-spritesheet.png", state_map, 120); //sprite sheet location, sprite size
}


DummyEntity::~DummyEntity(){}
