#include "CollisionComponent.h"




CollisionComponent::CollisionComponent(){
	mCollidingWith = new vector<pair<BaseEntity*, int>>();
}


CollisionComponent::~CollisionComponent(){}

bool CollisionComponent::isColliding() {
	return (mCollidingWith->size() > 0);
}

void CollisionComponent::clearCollisions() {
	mCollidingWith->clear();
}
