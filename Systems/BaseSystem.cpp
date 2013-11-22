#include "BaseSystem.h"

BaseSystem::~BaseSystem()
{
}

void BaseSystem::init(Engine* e) {
	mEngine = e;
}

void BaseSystem::registerEntity(BaseEntity* entity) {
	entityList.push_back(entity);
}

void BaseSystem::removeEntity(BaseEntity* entity) {
	int pos = 0;
	for (size_t i = 0; i < entityList.size(); i++) {
		if (entityList[i] == entity) {
			pos = i;
		}
	}

    vector<BaseEntity*>::iterator it = entityList.begin()+pos;

    entityList.erase(it);
}

void BaseSystem::update() {}
