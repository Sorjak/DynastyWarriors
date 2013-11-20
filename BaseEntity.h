#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <string>

#include <SDL2\SDL.h>

#include "BaseComponent.h"

using namespace std;

class BaseEntity
{
public:
	virtual ~BaseEntity();

	std::vector<string> systemFlags;
	std::map<string, BaseComponent*> componentMap;
};
