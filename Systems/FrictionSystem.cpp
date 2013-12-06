#include "FrictionSystem.h"


FrictionSystem::FrictionSystem(){}

FrictionSystem::~FrictionSystem(){}

void FrictionSystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		BaseEntity* current = entityList[i];
		if (current->hasComponent("collision") && current->hasComponent("velocity") ) {
			CollisionComponent* cc = (CollisionComponent*)current->getComponent("collision");
			VelocityComponent* vc = (VelocityComponent*)current->getComponent("velocity");
			for( vector <pair <BaseEntity*,int> >::iterator c = cc->mCollidingWith->begin(); c != cc->mCollidingWith->end(); c++ ) {
				BaseEntity* collidee = c->first;
				if (collidee->hasComponent("friction") ) {
					FrictionComponent* fc = (FrictionComponent*) collidee->getComponent("friction");
					Vector2D* velocity = vc->getVelocity();
					if ( abs(velocity->x()) >= 1 ) {
						velocity->x() += fc->mStrength * -vc->mFacing;
					} else if ( abs(velocity->x()) < 1 && abs(velocity->x()) > 0) {
						velocity->x() += (fc->mStrength / 2) * -vc->mFacing;
					}
				}
			}
		}
	}
}
