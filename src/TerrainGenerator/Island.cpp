#include "Island.h"

Island::Island(SDL_Rect bounds, shared_ptr<Noise> n, int totalChunks) {
    this->width     = bounds.w;
    this->height    = bounds.h;
    this->coord     = {bounds.x, bounds.y}; //new Vector2D(bounds.x, bounds.y);
    this->position  = {bounds.x * bounds.w, bounds.y * bounds.h};
    this->noise     = n;

	deep_water = { 0,0,205 };
	water = { 0,191,255 };
	sand = { 245,222,179 };
	grass = { 0, 128, 0 };
	mountain = { 139, 69, 19 };
	snow = { 255, 250, 250 };

    chunksPerLine = (int) sqrt(totalChunks);
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

	islandTex = nullptr;
}

Island::~Island() {

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

	if (!hasTexture) {
		islandTex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
		hasTexture = true;
	}

    for (auto i = chunksVisible.begin(); i != chunksVisible.end(); ++i)
    {
        shared_ptr<MapChunk> chunk = (*i);
        if (chunk->dirty){
		  UpdateTexture(chunk);
          chunk->dirty = false;
        }
        //chunk->Render(ren, -view_rect->x, -view_rect->y);

    }

	SDL_Rect renderRect = { position.x - view_rect->x, position.y - view_rect->y, width, height };

	if (hasTexture && chunksVisible.size() > 0)
		SDL_RenderCopy(ren, islandTex, NULL, &renderRect);
}

shared_ptr<MapChunk> Island::GetChunkAtPoint(SDL_Point point) {
    int islandX = point.x - position.x;
    int islandY = point.y - position.y;


    return GetChunkFromPosition(islandX, islandY);
}

vector<shared_ptr<MapChunk>> Island::GetChunksInRect(SDL_Rect* area) {
    vector<shared_ptr<MapChunk>> output;

    for (auto i = chunks.begin(); i != chunks.end(); ++i)
    {
        shared_ptr<MapChunk> chunk = i->second;

        SDL_Rect chunkRect = chunk->getWorldRect(); 

        if (SDL_HasIntersection(area, &chunkRect) == SDL_TRUE)
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
    SDL_Rect out = {(int) coord.x, (int) coord.y, width, height};
    return out;
}

SDL_Rect Island::getWorldRect() {
    SDL_Rect out = {(int) position.x, (int) position.y, width, height};
    return out;
}


void Island::UpdateTexture(shared_ptr<MapChunk> chunk) {
	SDL_Rect area = chunk->getLocalRect();

	unsigned char* pixels = new unsigned char[area.w * area.h * 4];

	for (int y = 0; y < area.h; y++) {
		for (int x = 0; x < area.w; x++) {
			const unsigned int offset = (area.w * 4 * y) + x * 4;
			double value = chunk->getHeightAt(x, y);

			SDL_Color* current = &water;
			if (value < .15) { current = &deep_water; }
			if (value >= .15 && value < .3) { current = &water; }
			if (value >= .3 && value < .4) { current = &sand; }
			if (value >= .4 && value < .7) { current = &grass; }
			if (value >= .7 && value < .9) { current = &mountain; }
			if (value > .9) { current = &snow; }

			pixels[offset + 0] = current->b;        // b
			pixels[offset + 1] = current->g;        // g
			pixels[offset + 2] = current->r;        // r
			pixels[offset + 3] = SDL_ALPHA_OPAQUE;  // a
		}
	}

	SDL_UpdateTexture(islandTex, &area, &pixels[0], area.w * 4);

	delete pixels;
}

