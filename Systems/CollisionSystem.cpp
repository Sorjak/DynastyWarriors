#include "CollisionSystem.h"


CollisionSystem::CollisionSystem() {}


CollisionSystem::~CollisionSystem() {}


// Just going to do this the most simple, naive way for now.
void CollisionSystem::update() {
	map<BaseEntity*, vector<BaseEntity*>> colliding;

	for (size_t i = 0; i < entityList.size(); i++) {
		DimensionComponent *adim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
		SDL_Rect *arect = adim->getRect();
		

		for (size_t j = i; j < entityList.size(); j++) {
			if (i != j) {
				int collide = 0;
				DimensionComponent *bdim = (DimensionComponent*) entityList[j]->componentMap["dimension"];

				SDL_Rect *brect = bdim->getRect();

				//Collide A from topleft of B
				if (arect->x + arect->w >= brect->x &&
					arect->y + arect->h >= brect->y) {
						collide++;
				}

				//Collide A from bottomleft of B
				if (arect->x + arect->w >= brect->x &&
					arect->y <= brect->y) {
						collide++;
				}

				//Collide A from topright of B
				if (arect->x <= brect->x + brect->w &&
					arect->y + arect->h >= brect->y) {
						collide++;
				}

				//Collide A from bottomright of B
				if (arect->x <= brect->x + brect->w &&
					arect->y <= brect->y + brect->h) {
						collide++;
				}

				if (collide > 0) {
					colliding[entityList[i]].push_back(entityList[j]);
				}
			}
		}
	}

	for(map<BaseEntity*, vector<BaseEntity*>>::iterator it = colliding.begin(); it != colliding.end(); ++it) {
		cout << it->first->mID << ":" << endl;
		for (size_t i = 0; i < it->second.size(); i++) {
			cout << "     " << it->second[i]->mID << endl;
		}
	}
}
