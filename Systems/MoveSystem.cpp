#include "MoveSystem.h"

MoveSystem::MoveSystem() {}
MoveSystem::~MoveSystem() {}

void MoveSystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		DimensionComponent *dim = (DimensionComponent*) entityList[i]->componentMap["dimension"];
		VelocityComponent *vel = (VelocityComponent*) entityList[i]->componentMap["velocity"];
		SDL_Rect *rect = dim->getRect();
		Vector2D *velocity = vel->getVelocity();
		Vector2D *position = dim->getPosition();

		if (velocity->x() > MAX_H_SPEED) 
			velocity->x() = MAX_H_SPEED;
		if (velocity->x() < -MAX_H_SPEED) 
			velocity->x() = -MAX_H_SPEED;
		if (velocity->y() > MAX_V_SPEED) 
			velocity->y() = MAX_V_SPEED;

		float timeStep = 1.f / mEngine->getFPS();

		double temp_x_vel = velocity->x()>=0 ? floor(velocity->x()+0.5) : ceil(velocity->x()-0.5);
		double temp_y_vel = velocity->y()>=0 ? floor(velocity->y()+0.5) : ceil(velocity->y()-0.5);

		position->x() += temp_x_vel * timeStep;
		position->y() += temp_y_vel * timeStep;

		dim->setLastRect(rect);

		rect->x  = (int) position->x();
		rect->y = (int) position->y();



	}
}
