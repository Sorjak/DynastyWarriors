#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Utils.h"

#include "Systems/BaseSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/MoveSystem.h"
#include "Systems/BounceSystem.h"
#include "Systems/ExpiresSystem.h"
#include "Systems/CollisionSystem.h"

#include "Entities/BaseEntity.h"
#include "Entities/ShipEntity.h"
#include "Entities/LaserEntity.h"
#include "Entities/WallEntity.h"




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
	void removeEntity(BaseEntity*);
	long getNextId();

private:
	void initGame();
	void initSystems();
	void initEntities();
	void addEntitiesToSystems();

	int running;
	map<string, BaseSystem*> systemList;
	vector<BaseEntity*> entityList;
	vector<BaseEntity*> toadd;
};

