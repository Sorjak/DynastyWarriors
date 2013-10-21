#include "BaseEntity.h"


BaseEntity::~BaseEntity()
{
	for(map<string, BaseComponent*>::iterator it = componentMap.begin(); it != componentMap.end(); ++it) {
		delete it->second;
	}
}
