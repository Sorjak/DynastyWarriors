#include "PlayerCollisionResolutionSystem.h"


PlayerCollisionResolutionSystem::PlayerCollisionResolutionSystem(){
	
}


PlayerCollisionResolutionSystem::~PlayerCollisionResolutionSystem(){}



void PlayerCollisionResolutionSystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		CollisionComponent *cc = (CollisionComponent*) entityList[i]->componentMap["collision"];

		if (cc->isColliding()) {
			VelocityComponent *vel = (VelocityComponent*) entityList[i]->componentMap["velocity"];
			DimensionComponent *dim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
			SDL_Rect *rect = dim->getRect();
			Vector2D *velocity = vel->getVelocity();

			string output = "";
			output += to_string(entityList[i]->mID) + " is to the ";
			for( vector <pair <BaseEntity*,int> >::iterator collidee = cc->mCollidingWith->begin(); collidee != cc->mCollidingWith->end(); collidee++ ) {
				DimensionComponent *collideedim = (DimensionComponent*) collidee->first->componentMap["dimension"];
				SDL_Rect * collideerect = collideedim->getRect();

				if (collidee->second == TOP ) { 
					rect->y = collideerect->y - rect->h + 1; 
					velocity->y() = 0;
					PlayerMotionComponent *motion = (PlayerMotionComponent*) entityList[i]->componentMap["player_motion"];
					motion->isOnGround = true;
					motion->jumpsLeft = 2;
				}
				if (collidee->second == BOTTOM) { 
					rect->y = collideerect->y + collideerect->h; 
					velocity->y() = 0; 
				}
				if (collidee->second == LEFT ) { 
					rect->x = collideerect->x - rect->w;
					velocity->x() = 0;
				}
				if (collidee->second == RIGHT) { 
					rect->x = collideerect->x + collideerect->w; 
					velocity->x() = 0;
				}

				output += getPrettyDirection(collidee->second) + " of ";
				output += to_string(collidee->first->mID) + " | ";

			}

			cout << output << endl;
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