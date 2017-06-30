#include "Island.h"

Island::Island(SDL_Rect bounds, Noise* n, int chunksPerLine) {
    this->width     = bounds.w;
    this->height    = bounds.h;
    this->coord     = new Vector2D(bounds.x, bounds.y);
    this->position  = new Vector2D(bounds.x * bounds.w, bounds.y * bounds.h);
    this->noise     = n;

    chunks.reserve(chunksPerLine * chunksPerLine);

    for (int x = 0; x < chunksPerLine; ++x)
    {
        for (int y = 0; y < chunksPerLine; ++y)
        {
            int chunkWidth  = this->width / chunksPerLine;
            int chunkHeight = this->height / chunksPerLine;

            SDL_Rect chunkRect = {x, y, chunkWidth, chunkHeight};
            MapChunk* chunk = new MapChunk(chunkRect, bounds);
            chunks.push_back(chunk);
            chunksToLoad++;
        }
    }
}

Island::Island(SDL_Rect bounds, Noise* n, vector<MapChunk*> chunks) {
    this->width     = bounds.w;
    this->height    = bounds.h;
    this->coord     = new Vector2D(bounds.x, bounds.y);
    this->position  = new Vector2D(bounds.x * bounds.w, bounds.y * bounds.h);
    this->chunks    = chunks;
    this->noise     = n;
}

Island::~Island() {
    delete coord;
    delete position;
}

void Island::Update(SDL_Rect* view_rect) {
    chunksVisible = GetChunksInRect(view_rect);
    
    if (chunksToLoad > 0) {

        vector<thread> chunksLoading;
        for (std::vector<MapChunk*>::iterator i = chunksVisible.begin(); i != chunksVisible.end(); ++i) {
            MapChunk* chunk = (*i);
            if (!chunk->hasHeightMap && !chunk->loadingHeightMap){
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

void Island::LoadChunk(MapChunk* chunk) {
    SDL_Rect bounds = {coord->x(), coord->y(), width, height};
    chunk->Load(noise, bounds);
    chunksToLoad--;
}

void Island::Render(SDL_Renderer* ren, SDL_Rect* view_rect) {

    for (std::vector<MapChunk*>::iterator i = chunksVisible.begin(); i != chunksVisible.end(); ++i)
    {
        MapChunk* chunk = (*i);
        chunk->Render(ren, -view_rect->x, -view_rect->y);
    }
}

MapChunk* Island::GetChunkAtPoint(SDL_Point mousePos) {
    for (std::vector<MapChunk*>::iterator i = chunks.begin(); i != chunks.end(); ++i)
    {
        MapChunk* chunk = (*i);

        SDL_Rect chunkRect = chunk->getWorldRect(); 

        bool inRect = SDL_PointInRect(&mousePos, &chunkRect);
        if (inRect)
            return chunk;
    }

    return NULL;
}

vector<MapChunk*> Island::GetChunksInRect(SDL_Rect* area) {
    vector<MapChunk*> output;

    for (std::vector<MapChunk*>::iterator i = chunks.begin(); i != chunks.end(); ++i)
    {
        MapChunk* chunk = (*i);

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

SDL_Rect Island::getWorldRect() {
    SDL_Rect out = {(int)position->x(), (int)position->y(), width, height};
    return out;
}

