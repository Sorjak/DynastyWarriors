#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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
#include "Systems/CollisionDetectionSystem.h"
#include "Systems/PlayerCollisionResolutionSystem.h"
#include "Systems/GravitySystem.h"
#include "Systems/FrictionSystem.h"
#include "Systems/AnimationSystem.h"

#include "Entities/BaseEntity.h"
#include "Entities/ShipEntity.h"
#include "Entities/LaserEntity.h"
#include "Entities/WallEntity.h"
#include "Entities/FighterEntity.h"




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
	float getFPS();

private:
	void initGame();
	void initSystems();
	void initEntities();
	void addEntitiesToSystems();

	int running;
	int lastID;
	map<string, BaseSystem*> systemList;
	vector<BaseEntity*> entityList;
	vector<BaseEntity*> toadd;
};

