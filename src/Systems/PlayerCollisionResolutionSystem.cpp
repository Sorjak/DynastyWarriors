#include "PlayerCollisionResolutionSystem.h"


PlayerCollisionResolutionSystem::PlayerCollisionResolutionSystem(){}

PlayerCollisionResolutionSystem::~PlayerCollisionResolutionSystem(){}

void PlayerCollisionResolutionSystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		BaseEntity* current = entityList[i];
		CollisionComponent *cc = (CollisionComponent*) current->getComponent("collision");

		if (cc->isColliding()) {
			VelocityComponent *vel = (VelocityComponent*) current->getComponent("velocity");
			DimensionComponent *dim = (DimensionComponent*) current->getComponent("dimension");
			SDL_Rect *rect = dim->getRect();
			Vector2D *velocity = vel->getVelocity();

			for( vector <pair <BaseEntity*,int> >::iterator collidee = cc->mCollidingWith->begin(); collidee != cc->mCollidingWith->end(); collidee++ ) {
				DimensionComponent *collideedim = (DimensionComponent*) collidee->first->componentMap["dimension"];
				StateComponent *sc = (StateComponent*)current->getComponent("state");
				SDL_Rect * collideerect = collideedim->getRect();
				Vector2D* position = dim->getPosition();

				
				if (collidee->second == TOP ) { 
					position->y() = collideerect->y - rect->h + 1; 
					velocity->y() = 0;
					sc->setVerticalState("GROUND");
					if (current->hasComponent("player_motion")){
						PlayerMotionComponent* pmc = (PlayerMotionComponent*)current->getComponent("player_motion");
						pmc->jumpsLeft = 2;
					}
				}
				if (collidee->second == BOTTOM) { 
					position->y() = collideerect->y + collideerect->h;
					velocity->y() = 0; 
					sc->setVerticalState("FALLING");
				}
				if (collidee->second == LEFT ) { 
					position->x() = collideerect->x - rect->w;
					velocity->x() = 0;
					sc->setHorizontalState("IDLE");
				}
				if (collidee->second == RIGHT) { 
					position->x() = collideerect->x + collideerect->w;
					velocity->x() = 0;
					sc->setHorizontalState("IDLE");
				}
			}
		}
	}
		
}

string PlayerCollisionResolutionSystem::getPrettyDirection(int input) {
	switch (input) {
		case LEFT:
			return "LEFT";
		case TOP:
			return "TOP";
		case RIGHT:
			return "RIGHT";
		case BOTTOM:
			return "BOTTOM";
	}

	return "";
}