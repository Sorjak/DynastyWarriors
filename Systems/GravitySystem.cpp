#include "GravitySystem.h"


GravitySystem::GravitySystem(float strength){
	mStrength = new Vector2D(0.f, strength);
}


GravitySystem::~GravitySystem(){

}


void GravitySystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		VelocityComponent *vel = (VelocityComponent*) entityList[i]->componentMap["velocity"];
		PlayerMotionComponent *motion = (PlayerMotionComponent*) entityList[i]->componentMap["player_motion"];
		Vector2D *velocity = vel->getVelocity();

		if (!motion->isOnGround) {
			velocity->y() += mStrength->y();
		}
	}
}