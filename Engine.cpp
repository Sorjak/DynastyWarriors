#include "Engine.h"


Engine::Engine() {
	initGame();
	initSystems();
	// initEntities();
}

Engine::~Engine() {
	//for (map<string, BaseSystem*>::iterator it = systemList.begin(); it != systemList.end(); ++it) {
	//	delete it->second;
	//}

	//for (size_t i = 0; i < entityList.size(); i++) {
	//	delete entityList[i];
	//}

}

void Engine::startGame() {
	running = true;
	
	cout << "Starting game" << endl;
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
	cout << "Initializing Systems" << endl;

	BaseSystem *input = new InputSystem();
	input->init(this);
	systemList["input"] = input;

	// BaseSystem *player_input = new PlayerInputSystem();
	// player_input->init(this);
	// systemList["player_input"] = player_input;

	//Here we add the different input types;
	InputSystem* myinput = (InputSystem*)systemList["input"];
	myinput->inputList.push_back(input);

	// GravitySystem *gravity = new GravitySystem(7.f);
	// gravity->init(this);
	// systemList["gravity"] = gravity;

	// BaseSystem *move =  new MoveSystem();
	// move->init(this);
	// systemList["move"] = move;

	// BaseSystem *bounce = new BounceSystem(SCREEN_WIDTH, SCREEN_HEIGHT);
	// bounce->init(this);
	// systemList["bounce"] = bounce;

	// ExpiresSystem *expires = new ExpiresSystem();
	// expires->init(this);
	// systemList["expires"] = expires;

	// CollisionDetectionSystem *collisionD = new CollisionDetectionSystem();
	// collisionD->init(this);
	// systemList["collides"] = collisionD;

	// PlayerCollisionResolutionSystem *collisionR = new PlayerCollisionResolutionSystem();
	// collisionR->init(this);
	// systemList["player_resolves"] = collisionR;

	// BaseSystem *friction = new FrictionSystem();
	// friction->init(this);
	// systemList["friction"] = friction;

	// BaseSystem *animation = new AnimationSystem(12);
	// animation->init(this);
	// systemList["animation"] = animation;

	BaseSystem *Terrain = new TerrainSystem(screenWidth, screenHeight);
	Terrain->init(this);
	systemList["terrain"] = Terrain;

	BaseSystem *Camera = new CameraSystem(screenWidth, screenHeight);
	Camera->init(this);
	systemList["camera"] = Camera;

	BaseSystem *render = new RenderSystem(screenWidth, screenHeight, "Dynasty Warriors");//"media/aztlan_bg_2x.png");
	render->init(this);
	systemList["render"] = render;
}

void Engine::initEntities() {
	int wallwidth = 32;
	int wallheight = 32;

	addEntity(new FighterEntity(getNextId()));
	addEntity(new DummyEntity(getNextId()));

	SDL_Rect leftwall = {250, 330, 180, 32};
	addEntity(new WallEntity(getNextId(), &leftwall));

	SDL_Rect rightwall = { 835, 330, 180, 32 };
	addEntity(new WallEntity(getNextId(), &rightwall));

	SDL_Rect  topwall = {540, 250, 200, 32};
	addEntity(new WallEntity(getNextId(), &topwall));

	SDL_Rect  bottomwall = {140, 490, 1000, 32};
	addEntity(new WallEntity(getNextId(), &bottomwall));

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

float Engine::getFPS() {
	RenderSystem* rs = (RenderSystem*)systemList["render"];
	return rs->getCurrentFPS();
}

BaseSystem* Engine::getSystem(string get) {
	return systemList[get];
}
