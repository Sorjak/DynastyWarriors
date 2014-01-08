#include "FrictionSystem.h"


FrictionSystem::FrictionSystem(){}

FrictionSystem::~FrictionSystem(){}

void FrictionSystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		BaseEntity* current = entityList[i];
		if (current->hasComponent("collision") && current->hasComponent("velocity") && current->hasComponent("state")) {
			CollisionComponent* cc = (CollisionComponent*)current->getComponent("collision");
			VelocityComponent* vc = (VelocityComponent*)current->getComponent("velocity");
			DimensionComponent* dc = (DimensionComponent*)current->getComponent("dimension");
			StateComponent* sc = (StateComponent*)current->getComponent("state");

			for (vector <pair <BaseEntity*, int> >::iterator c = cc->mCollidingWith->begin(); c != cc->mCollidingWith->end(); c++) {
				BaseEntity* collidee = c->first;

				if (collidee->hasComponent("friction")) {
					FrictionComponent* fc = (FrictionComponent*)collidee->getComponent("friction");
					Vector2D* velocity = vc->getVelocity();


					if (sc->getHorizonalState() == "SLOWING") {
						if (abs(velocity->x()) > 0) {
							if (abs(velocity->x()) > fc->mStrength) {
								velocity->x() += fc->mStrength * -dc->mFacing;
							}
							else {
								velocity->x() = 0;
							}
						}
						if (velocity->x() == 0) {
							sc->setHorizontalState("IDLE");
						}
					}
				}
			}
		}
	}
}
