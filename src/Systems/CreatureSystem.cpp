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
    bool createNew = input->isClicked("C") && hasTemplate;
    Vector2 target = {400, 400};

    if (createNew && terrain->islandsInView.size() > 0) {
        auto island = terrain->islandsInView.at(0);
        auto chunk = island->FindChunk(.3, .7);
        if (chunk != NULL) {
            SDL_Point chunkPos = chunk->getWorldPosition();
        
            shared_ptr<Creature> guy(new Creature(creatureTemplate, chunkPos.x, chunkPos.y));
            guy->MoveTo(target.x, target.y);
            creatures.push_back(guy);
        }
    }

    for (auto it = creatures.begin(); it != creatures.end(); ++it) {
        auto creature = (*it);

        creature->Update();
        
        auto island = terrain->getIslandFromPoint(creature->position.x, creature->position.y);
        auto chunk = island->GetChunkFromPosition(creature->position.x, creature->position.y);

        if (chunk->getElevation() < .2) {
            cout << "Creature stepped in water and died" << endl;
            KillCreature(creature);
        }

    }

    for (auto it = creaturesToRemove.begin(); it != creaturesToRemove.end(); ++it) { 
        auto creature = (*it);
        creatures.erase(std::remove(creatures.begin(), creatures.end(), creature), creatures.end());
    }

    creaturesToRemove.clear();

    cout << creatures.size() << endl;
}

vector<shared_ptr<Creature>> CreatureSystem::GetCreaturesInRect(SDL_Rect* rect) {
    return creatures;
}

void CreatureSystem::CreateCreatureTemplate(SDL_Renderer* ren, int width, int height) {
    cout << "Creating creature template" << endl;
    bool* bodyPoints = new bool[width * height];
    SDL_Rect bodyBounds = {0,0,0,0};

    GenerateBody(width, height, bodyPoints, &bodyBounds);
    cout << "Body generated" << endl;

    creatureTemplate = MakeSprite(ren, width, bodyPoints, &bodyBounds);
    hasTemplate = creatureTemplate != nullptr;

}

void CreatureSystem::KillCreature(shared_ptr<Creature> creature) {
    creaturesToRemove.push_back(creature);
}


