#pragma once
#include <iostream>
#include <vector>
#include <cmath>

#include "../Entities/BaseEntity.h"

using namespace std;

class Engine;

class BaseSystem
{
public:
	virtual ~BaseSystem();
	virtual void init(Engine*);
	void registerEntity(BaseEntity* entity);
	void removeEntity(BaseEntity* entity);
	virtual void update();

	std::vector<BaseEntity*> entityList;
	Engine *mEngine;
};

