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

		if (velocity->x() > MAX_H_SPEED) 
			velocity->x() = MAX_H_SPEED;
		if (velocity->x() < -MAX_H_SPEED) 
			velocity->x() = -MAX_H_SPEED;
		if (velocity->y() > MAX_V_SPEED) 
			velocity->y() = MAX_V_SPEED;

		float timeStep = mEngine->getdt();

		float temp_x_vel = velocity->x()*timeStep>=0 ? floor(velocity->x()*timeStep+0.5) : ceil(velocity->x()*timeStep-0.5);
		float temp_y_vel = velocity->y()*timeStep>=0 ? floor(velocity->y()*timeStep+0.5) : ceil(velocity->y()*timeStep-0.5);

		cout << temp_x_vel << " : " << temp_y_vel << endl;

		position->x() += temp_x_vel;
		position->y() += temp_y_vel;

		dim->setLastRect(rect);

		rect->x  = (int) position->x();
		rect->y = (int) position->y();



	}
}
