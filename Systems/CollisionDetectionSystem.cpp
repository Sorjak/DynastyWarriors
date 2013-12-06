#include "CollisionDetectionSystem.h"

CollisionDetectionSystem::CollisionDetectionSystem() {}

CollisionDetectionSystem::~CollisionDetectionSystem() {}

// Just going to do this the most simple, naive way for now.
// We'll iteratively loop through all collidable entities, and write out to the entity's collision component
// The component will hold a vector of all the entities it collides with, as well as a 
// number indicating what direction it collided from

// left = 1
// top = 2
// right = 4
// bottom = 8
// topleft = left + top = 3, and so on

void CollisionDetectionSystem::update() {

	for (size_t i = 0; i < entityList.size(); i++) {
		if (entityList[i]->hasComponent("velocity") ) {
			CollisionComponent *cc = (CollisionComponent*) entityList[i]->componentMap["collision"];
			DimensionComponent *adim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
			SDL_Rect *arect = adim->getRect();
			SDL_Rect *aLastRect = adim->getLastRect();
			cc->clearCollisions();
		
			for (size_t j = 0; j < entityList.size(); j++) {
				if (i != j) {
					DimensionComponent *bdim = (DimensionComponent*) entityList[j]->componentMap["dimension"];
					SDL_Rect *brect = bdim->getRect();

					if (isColliding(arect, brect) == 1) {
						int direction = collidedFrom(aLastRect, brect);
						cc->mCollidingWith->push_back(make_pair(entityList[j], direction));
					}
				}
			}
		}
	}

	
}

SDL_bool CollisionDetectionSystem::isColliding(SDL_Rect* A, SDL_Rect* B) {
	
	//return (
	////Is A to the bottomright of B?
	//(A->x + A->w > B->x && A->y + A->h > B->y) &&

	////Is A to the topright of B?
	//(A->x + A->w > B->x && A->y < B->y + B->h) &&

	////Is A to the bottomleft of B?
	//(A->x < B->x + B->w && A->y + A->h > B->y) &&

	////Is A to the topleft of B?
	//(A->x < B->x + B->w && A->y < B->y + B->h) );

	return SDL_HasIntersection(A, B);

}

int CollisionDetectionSystem::collidedFrom(SDL_Rect* A, SDL_Rect* B) {
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


