#include "Engine.h"


Engine::Engine() {
	initGame();
	initSystems();
	// initEntities();
}

Engine::~Engine() {
	//for (map<string, shared_ptr<BaseSystem>>::iterator it = systemList.begin(); it != systemList.end(); ++it) {
	//	delete it->second;
	//}

	//for (size_t i = 0; i < entityList.size(); i++) {
	//	delete entityList[i];
	//}

}

void Engine::startGame() {
	running = true;
	srand(static_cast<unsigned int>(time(0)));
	
	cout << "Starting game" << endl;
	while (running) {
		// Now let's iterate through the systems map and update everyone
		for(auto it = systemList.begin(); it != systemList.end(); ++it) {
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
	cout << "Ending Game" << endl;
	SDL_Quit();
}

void Engine::initGame() {
	SDL_Init(SDL_INIT_EVERYTHING);
	lastID = 0;
}

void Engine::initSystems() {
	cout << "Initializing Systems" << endl;

	shared_ptr<BaseSystem> input(new InputSystem());
	systemList["input"] = input;

	// BaseSystem *player_input = new PlayerInputSystem();
	// player_input->init(this);
	// systemList["player_input"] = player_input;

	//Here we add the different input types;
	// InputSystem* myinput = (InputSystem*)systemList["input"];
	// input->inputList.push_back(input);

	// BaseSystem *animation = new AnimationSystem(12);
	// systemList["animation"] = animation;



	shared_ptr<BaseSystem> Terrain(new TerrainSystem(screenWidth, screenHeight));
	systemList["terrain"] = Terrain;

	shared_ptr<BaseSystem> Camera(new CameraSystem(screenWidth, screenHeight));
	systemList["camera"] = Camera;

	shared_ptr<BaseSystem> Creature(new CreatureSystem());
	systemList["creature"] = Creature;

	shared_ptr<BaseSystem> Plant(new PlantSystem());
	systemList["plant"] = Plant;


	shared_ptr<BaseSystem> render(new RenderSystem(screenWidth, screenHeight, "Dynasty Warriors"));
	systemList["render"] = render;

	for(auto it = systemList.begin(); it != systemList.end(); ++it) {
		it->second->init(this);
	}
}

void Engine::initEntities() {
	// int wallwidth = 32;
	// int wallheight = 32;

	//addEntity(new FighterEntity(getNextId()));
	//addEntity(new DummyEntity(getNextId()));

	//SDL_Rect leftwall = {250, 330, 180, 32};
	//addEntity(new WallEntity(getNextId(), &leftwall));

	//SDL_Rect rightwall = { 835, 330, 180, 32 };
	//addEntity(new WallEntity(getNextId(), &rightwall));

	//SDL_Rect  topwall = {540, 250, 200, 32};
	//addEntity(new WallEntity(getNextId(), &topwall));

	//SDL_Rect  bottomwall = {140, 490, 1000, 32};
	//addEntity(new WallEntity(getNextId(), &bottomwall));

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
		auto it = entityList.begin()+pos;
		entityList.erase(it);

		for(auto itx = systemList.begin(); itx != systemList.end(); ++itx) {
			itx->second->removeEntity(e);
		}
		delete e;
	}

}

long Engine::getNextId() {
	return lastID++;
}

float Engine::getFPS() {
	shared_ptr<RenderSystem> rs = static_pointer_cast<RenderSystem>(systemList["render"]);
	return rs->getCurrentFPS();
}

shared_ptr<BaseSystem> Engine::getSystem(string get) {
	return systemList[get];
}
