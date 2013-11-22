#include "ExpiresSystem.h"


ExpiresSystem::ExpiresSystem(){}

ExpiresSystem::~ExpiresSystem(){}

void ExpiresSystem::update() {
	BaseEntity* remove = NULL;
	for (size_t i = 0; i < entityList.size(); i++) {
		ExpirationComponent *exp = (ExpirationComponent*) entityList[i]->componentMap["expiration"];
		int start = exp->mStart;
		int duration = exp->mDuration;
		int current = SDL_GetTicks();
		if (start + duration < current) {
			mEngine->removeEntity(entityList[i]);
			remove = entityList[i];
			cout << remove << endl;
		}
	}

	if (remove)
		removeEntity(remove);
}

