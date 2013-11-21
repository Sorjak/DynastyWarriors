#include "Engine.h"

Engine::Engine() {
	initGame();
	initSystems();
	initEntities();
}

Engine::~Engine() {}

void Engine::startGame() {
	running = true;
	
	while (running) {
		// Now let's iterate through the systems map and update everyone
		for(map<string,BaseSystem*>::iterator it = systemList.begin(); it != systemList.end(); ++it) {
			it->second->update();
		}

		// Add any newly created entities to their proper systems
		addEntitiesToSystems();
	}
	endGame();
}

void Engine::setRunning(bool set) {
	running = set;
}

void Engine::endGame() {
	SDL_Quit();
}

void Engine::initGame() {
	SDL_Init(SDL_INIT_EVERYTHING);
}

void Engine::initSystems() {
	BaseSystem *input = new PlayerInputSystem();
	input->init(this);
	systemList["input"] = input;

	BaseSystem *render = new RenderSystem(800, 600, "Dynasty Warriors");
	render->init(this);
	systemList["render"] = render;

	BaseSystem *move =  new MoveSystem();
	move->init(this);
	systemList["move"] = move;

	BaseSystem *bounce =  new BounceSystem(800, 600);
	bounce->init(this);
	systemList["bounce"] = bounce;

	ExpiresSystem *expires = new ExpiresSystem();
	expires->init(this);
	systemList["expires"] = expires;
}

void Engine::initEntities() {
	addEntity(new ShipEntity());
}

void Engine::addEntitiesToSystems() {
	for(map<BaseEntity*, int>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
		if (it->second == 0) {
			vector<string> entitySystems = it->first->systemFlags;
			for (size_t j = 0; j < entitySystems.size(); j++) {
				systemList[entitySystems[j]]->registerEntity(it->first);
			}
			it->second = 1; //change to 1 so we don't update it again
		}
	}
	entityList.clear();
}

void Engine::addEntity(BaseEntity* e) {
	entityList[e] = 0; // 0 means not yet added to proper systems
}

void Engine::removeEntity(BaseEntity* e) {
	map<BaseEntity*, int>::iterator todel = entityList.find(e);
	entityList.erase(todel);  
}
