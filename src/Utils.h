#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <SDL2/SDL.h>

#include "Components/BaseComponent.h"

using namespace std;


void logSDLError(ostream &os, const string &msg);

vector<string> getKeysFromMap(map<string, BaseComponent*>);
