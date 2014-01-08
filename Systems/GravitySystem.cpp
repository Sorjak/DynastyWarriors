#include "GravitySystem.h"


GravitySystem::GravitySystem(float strength){
	mStrength = new Vector2D(0.f, strength);
}


GravitySystem::~GravitySystem(){}


void GravitySystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		BaseEntity* current = entityList[i];
		VelocityComponent *vel = (VelocityComponent*)current->getComponent("velocity");
		StateComponent* sc = (StateComponent*)current->getComponent("state");
		CollisionComponent *cc = (CollisionComponent*)current->getComponent("collision");
		Vector2D *velocity = vel->getVelocity();

		if (!cc->isColliding()) {
			velocity->y() += mStrength->y();
			sc->setVerticalState("FALLING");
		}
	}
}