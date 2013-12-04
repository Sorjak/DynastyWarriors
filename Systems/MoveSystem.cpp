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

		if (velocity->x() > MAX_H_SPEED) velocity->x() = MAX_H_SPEED;
		if (velocity->x() < -MAX_H_SPEED) velocity->x() = -MAX_H_SPEED;
		if (velocity->y() > MAX_V_SPEED) velocity->y() = MAX_V_SPEED;

		float timeStep = mEngine->getdt();

		position->x() += velocity->x() * timeStep;
		position->y() += velocity->y() * timeStep;

		cout << velocity->x() * timeStep << " : " << velocity->y() << endl;

		//position->x() += velocity->x();
		//position->y() += velocity->y();

		dim->setLastRect(rect);
		rect->x = position->x();
		rect->y = position->y();
	}
}
