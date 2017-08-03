#include "CreatureSystem.h"


CreatureSystem::CreatureSystem(){
}

void CreatureSystem::init(Engine* e) {
    mEngine = e;

    terrain = static_pointer_cast<TerrainSystem>(mEngine->getSystem("terrain"));
    input = static_pointer_cast<InputSystem>(mEngine->getSystem("input"));
}


CreatureSystem::~CreatureSystem(){}

void CreatureSystem::update() {
    bool createNew = input->isClicked("C");

    if (createNew && terrain->islandsInView.size() > 0) {
        auto island = terrain->islandsInView.at(0);
        auto chunk = island->FindChunk(.3, .7);
        if (chunk != NULL) {
            SDL_Point chunkPos = chunk->getWorldPosition();
            cout << "x: " << chunkPos.x << "y: " << chunkPos.y;
        
            shared_ptr<Creature> guy(new Creature(512, 512));
            // guy->MoveTo(chunkPos.x, chunkPos.y);

            cout << creatures.size() << endl;
            // creatures.push_back(guy);
        }
    }

    // for (auto it = creatures.begin(); it != creatures.end(); ++it) {
    //     auto creature = (*it);

    //     creature->MoveTo(creature->position.x + 1, creature->position.y + 1);
    // }
}

vector<shared_ptr<Creature>> CreatureSystem::GetCreaturesInRect(SDL_Rect* rect) {
    return creatures;
}


