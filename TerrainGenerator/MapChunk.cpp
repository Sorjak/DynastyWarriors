#include "MapChunk.h"

MapChunk::MapChunk(SDL_Rect rect, SDL_Rect islandBounds) {
    this->width         = rect.w;
    this->height        = rect.h;
    this->coord         = new Vector2D(rect.x, rect.y);
    this->localPosition = new Vector2D(rect.x * rect.w, rect.y * rect.h);
    this->worldPosition = new Vector2D(
        (islandBounds.x * islandBounds.w) + localPosition->x(),
        (islandBounds.y * islandBounds.h) + localPosition->y()
    );
}

MapChunk::MapChunk(int width, int height, shared_ptr<HeightMap> hm) {
    this->width     = width;
    this->height    = height;
    this->heightMap = hm;
}

MapChunk::~MapChunk() {
    // delete this->heightMap;
}


/*
*   Load a heightmap into this chunk, and update the texture if it has already been created.
*   We don't create a new texture because we don't get the renderer till later.
*/
void MapChunk::Load(std::shared_ptr<HeightMap> heightMap) {
    this->heightMap = heightMap;
    this->hasHeightMap = true;

    if (hasTexture) {
        chunkTex->Update(this->heightMap);
    }
}

void MapChunk::Render(SDL_Renderer* ren) {
    this->Render(ren, 0, 0);
}

void MapChunk::Render(SDL_Renderer* ren, int offsetX, int offsetY) {
    if (!hasTexture && hasHeightMap) {
        chunkTex = new Texture();
        chunkTex->Create(ren, this->width, this->height);
        chunkTex->Update(this->heightMap);
        hasTexture = true;
    } 

    else {

        chunkTex->Render(worldPosition->x() + offsetX, worldPosition->y() + offsetY); 

        if (selected) {
            SDL_Rect r = getWorldRect();
            r.x += offsetX;
            r.y += offsetY;
            SDL_RenderDrawRect(ren, &r);
        }
    }
}

void MapChunk::Select(bool val) {
    this->selected = val;
}

shared_ptr<HeightMap> MapChunk::getHeightMap() {
    if (hasHeightMap)
        return this->heightMap;

    return NULL;
}

std::string MapChunk::getName() {
    return to_string(coord->x()) + ", " + to_string(coord->y());
}

Vector2D* MapChunk::getLocalPosition() {
    return this->localPosition;
}

Vector2D* MapChunk::getWorldPosition() {
    return this->worldPosition;
}

int MapChunk::getWidth() {
    return this->width;
}

int MapChunk::getHeight() {
    return this->height;
}

SDL_Rect MapChunk::getLocalRect() {
    SDL_Rect out = {(int)localPosition->x(), (int)localPosition->y(), width, height};
    return out;
}

SDL_Rect MapChunk::getWorldRect() {
    SDL_Rect out = {(int)worldPosition->x(), (int)worldPosition->y(), width, height};
    return out;
}

