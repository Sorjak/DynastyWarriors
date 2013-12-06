#include "BaseEntity.h"


BaseEntity::~BaseEntity()
{
	for(map<string, BaseComponent*>::iterator it = componentMap.begin(); it != componentMap.end(); ++it) {
		delete it->second;
	}
}

bool BaseEntity::hasComponent(string search) {
	return ( componentMap.find(search) != componentMap.end() );
}

BaseComponent* BaseEntity::getComponent(string get) {
	if ( hasComponent(get) ) {
		return componentMap[get];
	}
	return NULL;
}
