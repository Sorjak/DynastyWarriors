#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Utils.h"

#include "BaseSystem.h"
#include "InputSystem.h"
#include "PlayerInputSystem.h"
#include "RenderSystem.h"
#include "MoveSystem.h"
#include "BounceSystem.h"

#include "BaseEntity.h"
#include "ShipEntity.h"
#include "LaserEntity.h"




using namespace std;

class Engine
{
public:
	Engine();
	~Engine();

	void startGame();
	//void handleInputs();
	void setRunning(bool);
	void endGame();
	void addEntity(BaseEntity*);


private:
	void initGame();
	void initSystems();
	void initEntities();
	void addEntitiesToSystems();

	int running;
	map<string, BaseSystem*> systemList;
	map<BaseEntity*, int> entityList;
};
