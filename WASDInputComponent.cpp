#include "WASDInputComponent.h"

WASDInputComponent::WASDInputComponent(){}

WASDInputComponent::~WASDInputComponent(){}

void WASDInputComponent::setInput(const char* command, BaseEntity *entity) {
	VelocityComponent *vel = (VelocityComponent*) entity->componentMap["velocity"];
	Vector2D *velocity = vel->getVelocity();
	if (strcmp(command, "w") == 0) {
		velocity->y()--;
	}
	if (strcmp(command, "s") == 0) {
		velocity->y()++;
	}
	if (strcmp(command, "a") == 0) {
		velocity->x()--;
	}
	if (strcmp(command, "d") == 0) {
		velocity->x()++;
	}
	if (strcmp(command, "space") == 0) {
		
	}
}
