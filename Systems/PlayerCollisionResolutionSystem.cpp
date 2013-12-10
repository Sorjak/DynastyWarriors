#include "PlayerCollisionResolutionSystem.h"


PlayerCollisionResolutionSystem::PlayerCollisionResolutionSystem(){
	
}


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

			string output = "";
			output += to_string(entityList[i]->mID) + " is to the ";
			for( vector <pair <BaseEntity*,int> >::iterator collidee = cc->mCollidingWith->begin(); collidee != cc->mCollidingWith->end(); collidee++ ) {
				DimensionComponent *collideedim = (DimensionComponent*) collidee->first->componentMap["dimension"];
				PlayerMotionComponent* pmc = (PlayerMotionComponent*) current->getComponent("player_motion");
				SDL_Rect * collideerect = collideedim->getRect();
				Vector2D* position = dim->getPosition();

				
				if (collidee->second == TOP ) { 
					position->y() = collideerect->y - rect->h + 1; 
					velocity->y() = 0;
					pmc->isOnGround = true;
					pmc->fighterState = "IDLE";
					pmc->jumpsLeft = 2;
				}
				if (collidee->second == BOTTOM) { 
					position->y() = collideerect->y + collideerect->h;
					velocity->y() = 0; 
					pmc->fighterState = "FALLING";
				}
				if (collidee->second == LEFT ) { 
					position->x() = collideerect->x - rect->w;
					velocity->x() = 0;
					pmc->fighterState = "IDLE";
				}
				if (collidee->second == RIGHT) { 
					position->x() = collideerect->x + collideerect->w;
					velocity->x() = 0;
					pmc->fighterState = "IDLE";
				}

				output += getPrettyDirection(collidee->second) + " of ";
				output += to_string(collidee->first->mID) + " | ";

			}

			//cout << output << endl;
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