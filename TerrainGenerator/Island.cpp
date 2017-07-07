#include "Island.h"

Island::Island(SDL_Rect bounds, shared_ptr<Noise> n, int totalChunks) {
    this->width     = bounds.w;
    this->height    = bounds.h;
    this->coord     = new Vector2D(bounds.x, bounds.y);
    this->position  = new Vector2D(bounds.x * bounds.w, bounds.y * bounds.h);
    this->noise     = n;

    chunksPerLine = sqrt(totalChunks);
    int chunkWidth  = this->width / this->chunksPerLine;
    int chunkHeight = this->height / this->chunksPerLine;

    for (int x = 0; x < chunksPerLine; ++x)
    {
        for (int y = 0; y < chunksPerLine; ++y)
        {
            SDL_Rect chunkRect = {x, y, chunkWidth, chunkHeight};
            AddChunk(chunkRect);
        }
    }
}

Island::~Island() {
    delete coord;
    delete position;
}

void Island::Update(SDL_Rect* view_rect) {
    chunksVisible = GetChunksInRect(view_rect);
    
    if (chunksToLoad > 0) {

        vector<thread> chunksLoading;
        for (auto i = chunksVisible.begin(); i != chunksVisible.end(); ++i) {
            shared_ptr<MapChunk> chunk = (*i);
            if (!chunk->hasHeightMap){
                thread t1(&Island::LoadChunk, this, chunk);
                chunksLoading.push_back(move(t1));
                // LoadChunk(chunk);
            }
        }

        for (auto i = chunksLoading.begin(); i != chunksLoading.end(); ++i) {
            i->join();
        }
    }
}

void Island::LoadChunk(shared_ptr<MapChunk> chunk) {
    SDL_Rect bounds = getLocalRect();
    shared_ptr<HeightMap> heightMap(
        noise->generateHeightMap(chunk->getWidth(), chunk->getHeight(), chunk->getLocalPosition(), &bounds)
    );
    chunk->Load(heightMap);
    chunksToLoad--;
}

void Island::Render(SDL_Renderer* ren, SDL_Rect* view_rect) {

    for (auto i = chunksVisible.begin(); i != chunksVisible.end(); ++i)
    {
        shared_ptr<MapChunk> chunk = (*i);
        chunk->Render(ren, -view_rect->x, -view_rect->y);
    }
}

shared_ptr<MapChunk> Island::GetChunkAtPoint(SDL_Point point) {
    int islandX = point.x - position->x();
    int islandY = point.y - position->y();


    return GetChunkFromPosition(islandX, islandY);
}

vector<shared_ptr<MapChunk>> Island::GetChunksInRect(SDL_Rect* area) {
    vector<shared_ptr<MapChunk>> output;

    for (auto i = chunks.begin(); i != chunks.end(); ++i)
    {
        shared_ptr<MapChunk> chunk = i->second;

        SDL_Rect chunkRect = chunk->getWorldRect(); 

        bool inRect = SDL_HasIntersection(area, &chunkRect);
        if (inRect)
            output.push_back(chunk);
    }

    return output;
}

int Island::getWidth() {
    return this->width;
}

int Island::getHeight() {
    return this->height;
}

void Island::AddChunk(SDL_Rect chunkRect) {
    auto chunkCoord = make_pair(chunkRect.x, chunkRect.y);

    SDL_Rect islandBounds = getLocalRect();
    shared_ptr<MapChunk> chunk(new MapChunk(chunkRect, islandBounds));

    chunks[chunkCoord] = chunk;
    chunksToLoad++;
}


shared_ptr<MapChunk> Island::GetChunkFromCoord(int x, int y) {
    if ((x >= 0 && x < width) && (y >= 0 && y < height)) {

        pair<int, int> chunkCoord = make_pair(x, y);

        auto search = chunks.find(chunkCoord);
        if (search != chunks.end()) {
            return search->second;
        }
    } 

    return NULL;
}

shared_ptr<MapChunk> Island::GetChunkFromPosition(int x, int y) {
    int chunkWidth = this->width / this->chunksPerLine;
    int chunkHeight = this->height / this->chunksPerLine;

    return GetChunkFromCoord(x / chunkWidth, y / chunkHeight);
}

SDL_Rect Island::getLocalRect() {
    SDL_Rect out = {(int)coord->x(), (int)coord->y(), width, height};
    return out;
}

SDL_Rect Island::getWorldRect() {
    SDL_Rect out = {(int)position->x(), (int)position->y(), width, height};
    return out;
}

