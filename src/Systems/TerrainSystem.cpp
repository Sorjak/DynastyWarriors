#include "TerrainSystem.h"

int distanceSquared(int x1, int y1, int x2, int y2) {
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

struct Circle {
    int x, y;
    int r;

    bool CheckPoint(int x2, int y2) {
        int distanceSqr = distanceSquared(x, y, x2, y2);
        return distanceSqr < (r * r);
    }

    float DistanceFromCenter(int x2, int y2) {
        return sqrt(distanceSquared(x, y, x2, y2));
    }
};


TerrainSystem::TerrainSystem(int screenWidth, int screenHeight){
    this->islandWidth = screenWidth * islandSizeMod;
    this->islandHeight = screenHeight * islandSizeMod;

	landMorphBox = { 0, 0, 150, 150 };

    MakeIsland(0, 0);
}

void TerrainSystem::init(Engine* e) {
    mEngine = e;

    cam = static_pointer_cast<CameraSystem>(mEngine->getSystem("camera"));
    input = static_pointer_cast<InputSystem>(mEngine->getSystem("input"));
}


TerrainSystem::~TerrainSystem(){}

void TerrainSystem::update() {
    SDL_Point mousePos = input->mousePosition;

    int leftEdge = cam->view.x  / mEngine->screenWidth;
    int topEdge = cam->view.y / mEngine->screenHeight;

    for (int x = leftEdge - 1 ; x < leftEdge + 2; ++x)
    {
        for (int y = topEdge - 1; y < topEdge + 2; ++y)
        {
            pair<int, int> current = make_pair(x, y);
            if (islands.count(current) == 0) {
                // float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                // cout << "Random: " << r << endl;
                //if (r > .75) {
                    MakeIsland(x, y);
                //} else {
                //    islands[current] = NULL;
                //}
            }
        }
    }

    auto islands_in_view = getIslandsInRect(&cam->view);

    for (auto i = islands_in_view.begin(); i != islands_in_view.end(); ++i)
    {
        shared_ptr<Island> island = (*i);

        island->Update(&cam->view);

        if (input->mouseIsDown) {
            SDL_Point worldMouse = {mousePos.x + cam->view.x, mousePos.y + cam->view.y};
            SDL_Rect mouseBox = {
                mousePos.x + cam->view.x - (landMorphBox.w / 2), 
                mousePos.y + cam->view.y - (landMorphBox.h / 2),
                landMorphBox.w,
                landMorphBox.h
            };

            vector<shared_ptr<MapChunk>> chunks = island->GetChunksInRect(&mouseBox);
            for (auto c = chunks.begin(); c != chunks.end(); ++c) {
                (*c)->dirty = true;
                MorphLand((*c), worldMouse, input->mouseLeft);
            }
        }
        
    }
}

vector<shared_ptr<Island>> TerrainSystem::getIslandsInRect(SDL_Rect* view_rect) {
    vector<shared_ptr<Island>> islands_in_view;

    for (auto i = islands.begin(); i != islands.end(); ++i)
    {
        shared_ptr<Island> island = i->second;

        if (island != NULL) {
            SDL_Rect islandRect = island->getWorldRect();

            if (SDL_HasIntersection(view_rect, &islandRect)) {
                islands_in_view.push_back(island);
            }
        }
    }

    return islands_in_view;
}


void TerrainSystem::MakeIsland(int x, int y) {
    int seed = rand() * 1000;
    shared_ptr<Noise> n(new Noise(seed, .5, 2.0, 100.0));
    SDL_Rect islandBounds = {x, y, islandWidth, islandHeight};
    pair<int, int> coord = make_pair(x, y);

    shared_ptr<Island> island(new Island(islandBounds, n, chunksPerIsland));
    islands[coord] = island;
}


void TerrainSystem::MorphLand(shared_ptr<MapChunk> chunk, SDL_Point point, bool raise) {
    // shared_ptr<HeightMap> originalMap = chunk->getHeightMap();
    SDL_Rect chunkRect = chunk->getWorldRect();
    Circle c = {point.x, point.y, landMorphBox.w / 2};

    if (chunk->hasHeightMap) {
        int width = chunk->getWidth(); // originalMap->getMapWidth();
        int height = chunk->getHeight(); //originalMap->getMapHeight();
        shared_ptr<HeightMap> newMap(new HeightMap(width, height));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float oldValue = chunk->getHeightAt(x, y);

                if (c.CheckPoint(chunkRect.x + x, chunkRect.y + y)) {
                    float val = 1 - (c.DistanceFromCenter(chunkRect.x + x, chunkRect.y + y) / c.r);
                    float curved = pow(val, 2.7) / (pow(val, 2.7) + pow(4.5 - 4.5 * val, 2.7));
                    float newValue = oldValue;

                    if (raise)
                        newValue += curved * morphPowerMod;
                    else 
                        newValue -= curved * morphPowerMod;

                    newMap->setHeightAt(x, y, newValue);
                } else {
                    newMap->setHeightAt(x, y, oldValue);
                }
            }
        }

        chunk->Load(newMap);
    }
}
