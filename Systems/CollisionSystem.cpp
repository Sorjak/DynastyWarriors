#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() {}

CollisionSystem::~CollisionSystem() {}

// Just going to do this the most simple, naive way for now.
// We'll iteratively loop through all collidable entities, and place them in this "colliding" map
// The map will hold each entity and a vector of all the entities it collides with, as well as a 
// number indicating what direction it collided from

// left = 1
// top = 2
// right = 4
// bottom = 8
// topleft = left + top = 3, and so on

void CollisionSystem::update() {
	map<BaseEntity*, vector<pair<BaseEntity*, int>>> colliding;

	for (size_t i = 0; i < entityList.size(); i++) {
		DimensionComponent *adim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
		SDL_Rect *arect = adim->getRect();
		SDL_Rect *aLastRect = adim->getLastRect();
		
		for (size_t j = 0; j < entityList.size(); j++) {
			if (i != j) {
				DimensionComponent *bdim = (DimensionComponent*) entityList[j]->componentMap["dimension"];
				SDL_Rect *brect = bdim->getRect();

				if (isColliding(arect, brect) == 1) {
					int direction = collidedFrom(aLastRect, brect);
					colliding[entityList[i]].push_back(make_pair(entityList[j], direction));
				}
			}
		}

	}

	for(map<BaseEntity*, vector<pair<BaseEntity*, int>>>::iterator it = colliding.begin(); it != colliding.end(); ++it) {
		if ( it->first->componentMap.find("velocity") != it->first->componentMap.end()  ) {
			VelocityComponent *vel = (VelocityComponent*) it->first->componentMap["velocity"];
			DimensionComponent *dim = (DimensionComponent*) it->first->componentMap["dimension"];
			SDL_Rect *rect = dim->getRect();
			Vector2D *velocity = vel->getVelocity();

			string output = "";
			output += to_string(it->first->mID) + " is to the ";
			for (size_t i = 0; i < it->second.size(); i++) {
				vector<pair<BaseEntity*, int>>temp = it->second;
				DimensionComponent *subdim = (DimensionComponent*) temp[i].first->componentMap["dimension"];
				SDL_Rect * subrect = subdim->getRect();

				if (temp[i].second == TOP ) { 
					rect->y = subrect->y - rect->h - 1; 
					velocity->y() = 0;
					if (it->first->componentMap.find("player_motion") != it->first->componentMap.end() ) {
						PlayerMotionComponent *motion = (PlayerMotionComponent*) it->first->componentMap["player_motion"];
						motion->isOnGround = true;
					}
				}
				if (temp[i].second == BOTTOM) { 
					rect->y = subrect->y + subrect->h + 1; 
					velocity->y() = 0; 
				}
				if (temp[i].second == LEFT ) { 
					rect->x = subrect->x - rect->w - 1; 
					velocity->x() = 0;
				}
				if (temp[i].second == RIGHT) { 
					rect->x = subrect->x + subrect->w + 1; 
					velocity->x() = 0;
				}

				output += getPrettyDirection(temp[i].second) + " of ";
				output += to_string(temp[i].first->mID) + " | ";

			}

			cout << output << endl;
		}
	}
}

bool CollisionSystem::isColliding(SDL_Rect* A, SDL_Rect* B) {
	
	return (
	//Is A to the bottomright of B?
	(A->x + A->w > B->x && A->y + A->h > B->y) &&

	//Is A to the topright of B?
	(A->x + A->w > B->x && A->y < B->y + B->h) &&

	//Is A to the bottomleft of B?
	(A->x < B->x + B->w && A->y + A->h > B->y) &&

	//Is A to the topleft of B?
	(A->x < B->x + B->w && A->y < B->y + B->h) );

}

int CollisionSystem::collidedFrom(SDL_Rect* A, SDL_Rect* B) {
	int cLeft = 0;
	int cTop = 0;
	int cRight = 0;
	int cBottom = 0;
	int direction = 0;

	//Is A to the bottomright of B?
	if (A->x + A->w > B->x && A->y + A->h > B->y) {
		cRight++;
		cBottom++;
	}

	//Is A to the topright of B?
	if (A->x + A->w > B->x && A->y < B->y + B->h) {
		cRight++;
		cTop++;
	}

	//Is A to the bottomleft of B?
	if (A->x < B->x + B->w && A->y + A->h > B->y) {
		cLeft++;
		cBottom++;
	}

	//Is A to the topleft of B?
	if(A->x < B->x + B->w && A->y < B->y + B->h) {
		cLeft++;
		cTop++;
	}

	if (cLeft == 2) {
		direction += LEFT;
	}

	if (cTop == 2) {
		direction += TOP;
	}

	if (cRight == 2) {
		direction += RIGHT;
	}

	if (cBottom == 2) {
		direction += BOTTOM;
	}

	return direction;
}

string CollisionSystem::getPrettyDirection(int input) {
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
