#include "MapChunk.h"

MapChunk::MapChunk(SDL_Rect rect, SDL_Rect islandBounds) {
    this->width         = rect.w;
    this->height        = rect.h;
    this->coord         = {rect.x, rect.y};
    this->localPosition = {rect.x * rect.w, rect.y * rect.h};
    this->worldPosition = {
        (islandBounds.x * islandBounds.w) + localPosition.x,
        (islandBounds.y * islandBounds.h) + localPosition.y
    };
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

    float average = this->heightMap->getAverageValue();
    
    ocean = average <= -.1;

    this->hasHeightMap = true;

    if (hasTexture) {
        this->updateHeightMap = true;
    }
}

void MapChunk::Render(SDL_Renderer* ren, int offsetX, int offsetY) {
    if (!hasTexture) {
        chunkTex = new Texture();
        chunkTex->Create(ren, this->width, this->height);
        if (hasHeightMap)
            chunkTex->Update(this->heightMap);

        hasTexture = true;
    }

    if (updateHeightMap)
        chunkTex->Update(this->heightMap);

    chunkTex->Render(worldPosition.x + offsetX, worldPosition.y + offsetY); 

    if (selected) {
        SDL_Rect r = getWorldRect();
        r.x += offsetX;
        r.y += offsetY;
        SDL_RenderDrawRect(ren, &r);
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


bool MapChunk::isOceanChunk() {
    return ocean;
}

std::string MapChunk::getName() {
    return to_string(coord.x) + ", " + to_string(coord.y);
}

SDL_Point MapChunk::getLocalPosition() {
    return this->localPosition;
}

SDL_Point MapChunk::getWorldPosition() {
    return this->worldPosition;
}

int MapChunk::getWidth() {
    return this->width;
}

int MapChunk::getHeight() {
    return this->height;
}

SDL_Rect MapChunk::getLocalRect() {
    SDL_Rect out = {(int) localPosition.x, (int) localPosition.y, width, height};
    return out;
}

SDL_Rect MapChunk::getWorldRect() {
    SDL_Rect out = {(int) worldPosition.x, (int) worldPosition.y, width, height};
    return out;
}

