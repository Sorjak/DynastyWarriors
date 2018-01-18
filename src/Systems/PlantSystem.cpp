#include "PlantSystem.h"


PlantSystem::PlantSystem(){
}

void PlantSystem::init(Engine* e) {
    cout << "Initializing Plant System" << endl;
    mEngine = e;

    terrain = static_pointer_cast<TerrainSystem>(mEngine->getSystem("terrain"));
}


PlantSystem::~PlantSystem(){}

void PlantSystem::update() {
    if (plants.size() < 10 && terrain->islandsInView.size() > 0) {
        auto island = terrain->islandsInView.at(0);
        auto chunk = island->FindChunk(.3, .7);
        if (chunk != NULL) {
            SDL_Point chunkPos = chunk->getWorldPosition();
        
            shared_ptr<Plant> p(new Plant(plantTemplate, chunkPos.x, chunkPos.y));
            plants.push_back(p);
        }
    }

    for (auto it = plants.begin(); it != plants.end(); ++it) {
        auto plant = (*it);

        plant->Update();

        if (plant->isDead()) {
            KillPlant(plant);
        }

    }

    for (auto it = plantsToRemove.begin(); it != plantsToRemove.end(); ++it) { 
        auto plant = (*it);
        cout << "Removing plant" << endl;
        auto index = std::find(plants.begin(), plants.end(), plant);

        if (index != plants.end()) {
            plants.erase(index);
        }

        // creatures.erase(std::remove(creatures.begin(), creatures.end(), creature), creatures.end());
    }

    plantsToRemove.clear();
}

vector<shared_ptr<Plant>> PlantSystem::GetPlantsInRect(SDL_Rect* rect) {
    vector<shared_ptr<Plant>> plantsVisible;

    for (auto it = plants.begin(); it != plants.end(); ++it) {
        auto plant = (*it);
        float radius = plant->GetAge();
        SDL_Rect plant_rect = {plant->position.x - radius, plant->position.y - radius, radius * 2, radius * 2};

        if (SDL_HasIntersection(rect, &plant_rect)) {
            plantsVisible.push_back(plant);
        }
    }

    return plantsVisible;
}

shared_ptr<Plant> PlantSystem::GetPlantFromPoint(float x, float y) {
    Vector2 origin = {x, y};
    float min_distance = 100000;
    shared_ptr<Plant> closest = nullptr;

    for (auto it = plants.begin(); it != plants.end(); ++it) {
        auto plant = (*it);
        float distance = origin.distance(plant->position);
        if (distance < min_distance) {
            min_distance = distance;
            closest = plant;
        }
    }

    return closest;
}

void PlantSystem::KillPlant(shared_ptr<Plant> plant) {
    plantsToRemove.push_back(plant);
}


