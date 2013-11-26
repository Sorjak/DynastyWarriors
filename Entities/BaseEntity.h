#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <string>

#include <SDL2\SDL.h>

#include "../Components/BaseComponent.h"

using namespace std;

class BaseEntity
{
public:
	virtual ~BaseEntity();

	long mID;
	std::vector<string> systemFlags;
	std::map<string, BaseComponent*> componentMap;
};

