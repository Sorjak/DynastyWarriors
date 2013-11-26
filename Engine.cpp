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

	BaseSystem *move =  new MoveSystem();
	move->init(this);
	systemList["move"] = move;

	BaseSystem *bounce =  new BounceSystem(800, 600);
	bounce->init(this);
	systemList["bounce"] = bounce;

	ExpiresSystem *expires = new ExpiresSystem();
	expires->init(this);
	systemList["expires"] = expires;

	CollisionSystem *collision = new CollisionSystem();
	collision->init(this);
	systemList["collides"] = collision;

	BaseSystem *render = new RenderSystem(800, 600, "Dynasty Warriors");
	render->init(this);
	systemList["render"] = render;
}

void Engine::initEntities() {
	addEntity(new ShipEntity(getNextId()));

	int wallwidth = 33;
	int wallheight = 32;

	//for (size_t i = 0; i < (800 / wallwidth); i++) {
	//	addEntity(new WallEntity(getNextId(), i*wallwidth, 600 - wallheight));
	//}
	addEntity(new WallEntity(getNextId(), wallwidth, 600 - wallheight));
}

void Engine::addEntitiesToSystems() {
	for(size_t i = 0; i < toadd.size(); i++) {
		vector<string> entitySystems = toadd[i]->systemFlags;
		for (size_t j = 0; j < entitySystems.size(); j++) {
			systemList[entitySystems[j]]->registerEntity(toadd[i]);
		}
	}
	toadd.clear();
}

void Engine::addEntity(BaseEntity* e) {
	toadd.push_back(e); // 0 means not yet added to proper systems
	entityList.push_back(e);
}

void Engine::removeEntity(BaseEntity* e) {
	int pos = -1;
	for (size_t i = 0; i < entityList.size(); i++) {
		if (entityList[i] == e)
			pos = i;
	}

	if (pos >= 0) {
		vector<BaseEntity*>::iterator it = entityList.begin()+pos;
		entityList.erase(it);

		for(map<string,BaseSystem*>::iterator itx = systemList.begin(); itx != systemList.end(); ++itx) {
			itx->second->removeEntity(e);
		}
		delete e;
	}

}

long Engine::getNextId() {
	if (entityList.size() < 0) {
		return 0;
	} 

	return entityList.size();
}
