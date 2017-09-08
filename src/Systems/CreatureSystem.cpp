#include "CreatureSystem.h"

// typedef tinyfsm::FsmList<Creature> fsm_list;

// template<typename E>
// void send_event(E const & event)
// {
//     fsm_list::template dispatch<E>(event);
// }

CreatureSystem::CreatureSystem(){}

void CreatureSystem::init(Engine* e) {
    mEngine = e;

    terrain = static_pointer_cast<TerrainSystem>(mEngine->getSystem("terrain"));
    input = static_pointer_cast<InputSystem>(mEngine->getSystem("input"));
    plant = static_pointer_cast<PlantSystem>(mEngine->getSystem("plant"));

}


CreatureSystem::~CreatureSystem(){}

void CreatureSystem::update() {
    bool createNew = input->isClicked("C") && hasTemplate;

    if (createNew && terrain->islandsInView.size() > 0) {
        auto island = terrain->islandsInView.at(0);
        auto chunk = island->FindChunk(.3, .7);
        if (chunk != NULL) {
            SDL_Point chunkPos = chunk->getWorldPosition();
        
            shared_ptr<Creature> guy(new Creature(creatureTemplate, chunkPos.x, chunkPos.y));

            guy->start();

            cout << "Created creature at: " << chunkPos.x << ", " << chunkPos.y << endl;
            creatures.push_back(guy);

        }
    }

    for (auto it = creatures.begin(); it != creatures.end(); ++it) {
        auto creature = (*it);

        shared_ptr<Plant> p = plant->GetPlantFromPoint(creature->position.x, creature->position.y);

        creature->Update();

        cout << creature->get_current_state()->name << endl;

        if (creature->GetHunger() >= 50) {
            cout << "Sending hunger event" << endl;
            GotHungry gh;
            gh.name = "GotHungry";
            creature->dispatch(gh);
        }

        float elevation = terrain->GetElevationAtPoint(creature->position.x, creature->position.y);

        if (elevation < .2) {
            cout << "Creature stepped in water and died" << endl;
            KillCreature(creature);
        }

    }

    for (auto it = creaturesToRemove.begin(); it != creaturesToRemove.end(); ++it) { 
        auto creature = (*it);
        cout << "Removing creature" << endl;
        auto index = std::find(creatures.begin(), creatures.end(), creature);

        if (index != creatures.end()) {
            creatures.erase(index);
        }
    }

    creaturesToRemove.clear();
}

vector<shared_ptr<Creature>> CreatureSystem::GetCreaturesInRect(SDL_Rect* rect) {
    vector<shared_ptr<Creature>> creaturesVisible;

    for (auto it = creatures.begin(); it != creatures.end(); ++it) {
        auto creature = (*it);
        if (SDL_HasIntersection(rect, &creature->bodyBounds)) {
            creaturesVisible.push_back(creature);
        }
    }

    return creaturesVisible;
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

