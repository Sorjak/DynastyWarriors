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

void BaseSystem::update() {}
