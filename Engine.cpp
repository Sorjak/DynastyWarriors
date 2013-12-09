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
	lastID = 0;
}

void Engine::initSystems() {
	BaseSystem *input = new InputSystem();
	input->init(this);
	systemList["input"] = input;

	BaseSystem *player_input = new PlayerInputSystem();
	player_input->init(this);
	systemList["player_input"] = player_input;

	//Here we add the different input types;
	InputSystem* myinput = (InputSystem*)systemList["input"];
	myinput->inputList.push_back(player_input);

	GravitySystem *gravity = new GravitySystem(7.f);
	gravity->init(this);
	systemList["gravity"] = gravity;

	BaseSystem *move =  new MoveSystem();
	move->init(this);
	systemList["move"] = move;

	BaseSystem *bounce =  new BounceSystem(800, 600);
	bounce->init(this);
	systemList["bounce"] = bounce;

	ExpiresSystem *expires = new ExpiresSystem();
	expires->init(this);
	systemList["expires"] = expires;

	CollisionDetectionSystem *collisionD = new CollisionDetectionSystem();
	collisionD->init(this);
	systemList["collides"] = collisionD;

	PlayerCollisionResolutionSystem *collisionR = new PlayerCollisionResolutionSystem();
	collisionR->init(this);
	systemList["player_resolves"] = collisionR;

	BaseSystem *friction = new FrictionSystem();
	friction->init(this);
	systemList["friction"] = friction;

	BaseSystem *animation = new AnimationSystem();
	animation->init(this);
	systemList["animation"] = animation;

	BaseSystem *render = new RenderSystem(800, 600, "Dynasty Warriors");
	render->init(this);
	systemList["render"] = render;
}

void Engine::initEntities() {
	int wallwidth = 32;
	int wallheight = 32;

	addEntity(new FighterEntity(getNextId()));

	SDL_Rect topwall = {400 - 32, 300, 64, 32};
	addEntity(new WallEntity(getNextId(), &topwall));

	SDL_Rect  middlewall = {400 + 32, 600 - 128, 32, 96};
	addEntity(new WallEntity(getNextId(), &middlewall));

	SDL_Rect  bottomwall = {0, 600 - 32, 800, 32};
	addEntity(new WallEntity(getNextId(), &bottomwall));
	
	// Turn this on if you want some serious lag
	//SDL_Rect  bottomwall = {0, 600 - 32, 32, 32};

	//for (int i = 0; i < 800 / 32; i++) {
	//	bottomwall.x = i * 32;
	//	addEntity(new WallEntity(getNextId(), &bottomwall));
	//}


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
	return lastID++;
}

float Engine::getdt() {
	RenderSystem* rs = (RenderSystem*)systemList["render"];
	return 1.f / rs->getCurrentFPS();
}
