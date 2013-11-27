#include "MoveSystem.h"


MoveSystem::MoveSystem() {}


MoveSystem::~MoveSystem() {}

void MoveSystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		DimensionComponent *dim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
		VelocityComponent *vel = (VelocityComponent*) entityList[i]->componentMap["velocity"];
		SDL_Rect *rect = dim->getRect();
		Vector2D *velocity = vel->getVelocity();
		Vector2D *position = new Vector2D((float)rect->x, (float)rect->y);

		position->x() = position->x() + velocity->x();
		position->y() = position->y() + velocity->y();

		dim->setLastRect(rect);
		rect->x = position->x();
		rect->y = position->y();
	}
}
