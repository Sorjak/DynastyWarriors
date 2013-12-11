#include "BaseSystem.h"

BaseSystem::~BaseSystem() {
	for (size_t i = 0; i < entityList.size(); i++) {
		//delete entityList[i];
	}
}

void BaseSystem::init(Engine* e) {
	mEngine = e;
}

void BaseSystem::registerEntity(BaseEntity* entity) {
	entityList.push_back(entity);
}

void BaseSystem::removeEntity(BaseEntity* entity) {
	int pos = -1;
	for (size_t i = 0; i < entityList.size(); i++) {
		if (entityList[i] == entity) {
			pos = i;
		}
	}

	if (pos >= 0) {
		vector<BaseEntity*>::iterator it = entityList.begin()+pos;
		entityList.erase(it);
	}
}

void BaseSystem::update() {}
