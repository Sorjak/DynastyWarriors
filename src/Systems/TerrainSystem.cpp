#include "TerrainSystem.h"


TerrainSystem::TerrainSystem(int screenWidth, int screenHeight){
    this->islandWidth = 1200; //screenWidth * islandSizeMod;
    this->islandHeight = 1200; //screenHeight * islandSizeMod;

	landMorphBox = { 0, 0, 150, 150 };
    currentThreads = 0;
}

void TerrainSystem::init(Engine* e) {
    cout << "Initializing Terrain System" << endl;
    mEngine = e;

    cam = static_pointer_cast<CameraSystem>(mEngine->getSystem("camera"));
    input = static_pointer_cast<InputSystem>(mEngine->getSystem("input"));

    pair<int, int> originCoord = make_pair(0, 0);
    SDL_Rect islandBounds = {0, 0, islandWidth, islandHeight};

    MakeIsland(originCoord, islandBounds);
}


TerrainSystem::~TerrainSystem(){}

void TerrainSystem::update() {
    SDL_Point mousePos = input->mousePosition;

    int leftEdge = (cam->view.x + (cam->view.w / 2)) / mEngine->screenWidth;
    int topEdge = (cam->view.y + (cam->view.h / 2)) / mEngine->screenHeight;

    // vector<thread> islandThreads;
    for (int x = leftEdge - 1 ; x < leftEdge + 2; ++x)
    {
        for (int y = topEdge - 1; y < topEdge + 2; ++y)
        {
            pair<int, int> current = make_pair(x, y);
            const bool islandGenerating = islandsGenerating.find(current) != islandsGenerating.end();
            const bool islandExists = islands.find(current) != islands.end();

            if (!islandExists && !islandGenerating) {
                cout << "Need to generate island " << x << ", " << y << endl;
                GenerateIsland(x, y);
            }
        }
    }

    if (!islandsToGenerate.empty()) {
        while (currentThreads < maxThreads) {
            auto coord = islandsToGenerate.front();
            SDL_Rect islandBounds = {coord.first, coord.second, islandWidth, islandHeight};

            thread t1(&TerrainSystem::MakeIsland, this, coord, islandBounds);
            t1.detach();

            currentThreads++;
            islandsToGenerate.pop();
        }
    }


    islandsInView = getIslandsInRect(&cam->view, cam->scale);

    for (auto i = islandsInView.begin(); i != islandsInView.end(); ++i)
    {
        shared_ptr<Island> island = (*i);

        island->Update(&cam->view, cam->scale);

        if (input->mouseIsDown) {
            SDL_Point worldMouse = {
                (mousePos.x + cam->view.x) / cam->scale, 
                (mousePos.y + cam->view.y) / cam->scale
            };

            auto chunk = getChunkFromPoint(worldMouse.x, worldMouse.y);
            // currentChunk = chunk;

            cout << chunk->getName() << endl;

            // SDL_Rect mouseBox = {
            //     worldMouse.x - (landMorphBox.w / 2), 
            //     worldMouse.y - (landMorphBox.h / 2),
            //     landMorphBox.w,
            //     landMorphBox.h
            // };

            // vector<shared_ptr<MapChunk>> chunks = island->GetChunksInRect(&mouseBox, 1);
            // for (auto c = chunks.begin(); c != chunks.end(); ++c) {
            //     (*c)->dirty = true;
            //     MorphLand((*c), worldMouse, input->mouseLeft);
            // }
        }
        
    }
}

vector<shared_ptr<Island>> TerrainSystem::getIslandsInRect(SDL_Rect* view_rect, int scale) {
    vector<shared_ptr<Island>> islands_in_rect;

    SDL_Rect scaledViewRect = {
        view_rect->x * scale, 
        view_rect->y * scale,
        view_rect->w * scale,
        view_rect->h * scale
    };

    for (auto i = islands.begin(); i != islands.end(); ++i)
    {
        shared_ptr<Island> island = i->second;

        if (island != NULL) {
            SDL_Rect islandRect = island->getScaledWorldRect(scale);

            if (SDL_HasIntersection(&scaledViewRect, &islandRect)) {
                islands_in_rect.push_back(island);
            }
        }
    }

    return islands_in_rect;
}

shared_ptr<Island> TerrainSystem::getIslandFromCoord(int x, int y) {
    pair<int, int> islandCoord = make_pair(x, y);

    auto search = islands.find(islandCoord);
    if (search != islands.end()) {
        return search->second;
    }

    return NULL;
}

shared_ptr<Island> TerrainSystem::getIslandFromPoint(int x, int y) {
    return getIslandFromCoord(x / this->islandWidth, y / this->islandHeight);
}

shared_ptr<MapChunk> TerrainSystem::getChunkFromPoint(int x, int y) {
    auto island = getIslandFromPoint(x, y);
    return island->GetChunkFromPosition(x, y);
}

float TerrainSystem::GetElevationAtPoint(int x, int y) {
    auto chunk = getChunkFromPoint(x, y);

    return chunk->getElevation();
}

shared_ptr<MapChunk> TerrainSystem::getCurrentChunk() {
    return currentChunk;
}

string TerrainSystem::getCurrentChunkInfo() {
    string chunkInfo = "Chunk Info: " + currentChunk->getName();

    return chunkInfo;
}

void TerrainSystem::GenerateIsland(int x, int y) {
    // thread t1(&TerrainSystem::MakeIsland, this, x, y);
    // t1.detach();

    pair<int, int> coord = make_pair(x, y);
    islandsToGenerate.push(coord);

    islandsGenerating.insert(coord);
}

void TerrainSystem::MakeIsland(pair<int, int> coord, SDL_Rect islandBounds) {
    int seed = rand() * 1000;
    shared_ptr<Noise> n(new Noise(seed, .5, 2.0, 300.0));

    cout << "Making Island (" << coord.first << ", " << coord.second << ")" << endl; 
    shared_ptr<Island> island(new Island(islandBounds, n, chunksPerIsland));
    cout << "Created Island (" << coord.first << ", " << coord.second << ")" << endl;

    islands[coord] = island;
    if (islandsGenerating.find(coord) != islandsGenerating.end()) {
        islandsGenerating.erase(coord);
    }

    currentThreads = max(0, currentThreads - 1);
}


void TerrainSystem::MorphLand(shared_ptr<MapChunk> chunk, SDL_Point point, bool raise) {
    // shared_ptr<HeightMap> originalMap = chunk->getHeightMap();
    SDL_Rect chunkRect = chunk->getScaledWorldRect(cam->scale);
    Circle c = {point.x, point.y, landMorphBox.w / 2};

    cout << "Chunk Rect: " << chunkRect.x << ", " << chunkRect.y << ", " << chunkRect.w << endl;
    // cout << "Morph Circle: " << c.x << ", " << c.y << ", " << c.r << endl;

    if (chunk->hasHeightMap) {
        int width = chunk->getWidth(); // originalMap->getMapWidth();
        int height = chunk->getHeight(); //originalMap->getMapHeight();
        shared_ptr<HeightMap> newMap(new HeightMap(width, height));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float oldValue = chunk->getHeightAt(x, y);

                if (c.CheckPoint(chunkRect.x + x, chunkRect.y + y)) {
                    float val = 1 - (c.DistanceFromCenter(chunkRect.x + x, chunkRect.y + y) / c.r);
                    float curved = smoothGradient(val, 2.7, 4.5);
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
