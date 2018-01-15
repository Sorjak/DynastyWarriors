#include "Island.h"

Island::Island(SDL_Rect bounds, shared_ptr<Noise> n, int totalChunks) {
    this->width     = bounds.w;
    this->height    = bounds.h;
    this->coord     = {bounds.x, bounds.y};
    this->position  = {bounds.x * bounds.w, bounds.y * bounds.h};
    this->noise     = n;

    black = {0, 0, 0};
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
            shared_ptr<MapChunk> chunk = AddChunk(chunkRect);
            thread t1(&Island::LoadChunk, this, chunk);
            t1.detach();
        }
    }

	islandTex = nullptr;
}

Island::~Island() {

}

void Island::Update(SDL_Rect* view_rect, int scale) {
    chunksVisible = GetChunksInRect(view_rect, scale);
    
    // if (chunksToLoad > 0) {

    //     vector<thread> chunksLoading;
    //     for (auto i = chunksVisible.begin(); i != chunksVisible.end(); ++i) {
    //         shared_ptr<MapChunk> chunk = (*i);
    //         if (!chunk->hasHeightMap){
    //             thread t1(&Island::LoadChunk, this, chunk);
    //             chunksLoading.push_back(move(t1));
    //             // LoadChunk(chunk);
    //         }
    //     }

    //     for (auto i = chunksLoading.begin(); i != chunksLoading.end(); ++i) {
    //         i->join();
    //     }
    // }
}

void Island::LoadChunk(shared_ptr<MapChunk> chunk) {
    SDL_Rect bounds = getLocalRect();
    shared_ptr<HeightMap> heightMap(
        noise->generateHeightMap(chunk->getWidth(), chunk->getHeight(), chunk->getLocalPosition(), &bounds)
    );
    chunk->Load(heightMap);
    chunksToLoad--;
}

void Island::Render(SDL_Renderer* ren, SDL_Rect* view_rect, int scale) {

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
    }

	SDL_Rect renderRect = { 
        (position.x - view_rect->x) * scale, 
        (position.y - view_rect->y) * scale, 
        width * scale, height * scale
    };

	if (hasTexture && chunksVisible.size() > 0)
		SDL_RenderCopy(ren, islandTex, NULL, &renderRect);
}

shared_ptr<MapChunk> Island::FindChunk(float low, float high) {
    vector<shared_ptr<MapChunk>> possibilities;

    for (auto i = chunks.begin(); i != chunks.end(); ++i)
    {
        shared_ptr<MapChunk> chunk = i->second;

        if (chunk->getElevation() >= low && chunk->getElevation() < high) {
            possibilities.push_back(chunk);
        }
    }

    if (possibilities.size() > 0) {
        int randIndex = rand() % possibilities.size();

        return possibilities.at(randIndex);
    }

    return NULL;
}

shared_ptr<MapChunk> Island::GetChunkAtPoint(SDL_Point point) {
    int islandX = point.x - position.x;
    int islandY = point.y - position.y;


    return GetChunkFromPosition(islandX, islandY);
}

vector<shared_ptr<MapChunk>> Island::GetChunksInRect(SDL_Rect* area, int scale) {
    vector<shared_ptr<MapChunk>> output;
    SDL_Rect scaledArea = {
        area->x * scale, 
        area->y * scale,
        area->w * scale,
        area->h * scale
    };

    for (auto i = chunks.begin(); i != chunks.end(); ++i)
    {
        shared_ptr<MapChunk> chunk = i->second;

        SDL_Rect chunkRect = chunk->getScaledWorldRect(scale);

        if (SDL_HasIntersection(&scaledArea, &chunkRect) == SDL_TRUE)
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

shared_ptr<MapChunk> Island::AddChunk(SDL_Rect chunkRect) {
    auto chunkCoord = make_pair(chunkRect.x, chunkRect.y);

    SDL_Rect islandBounds = getLocalRect();
    shared_ptr<MapChunk> chunk(new MapChunk(chunkRect, islandBounds));

    chunks[chunkCoord] = chunk;
    chunksToLoad++;

    return chunk;
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

SDL_Rect Island::getScaledWorldRect(int scale) {
    return {position.x * scale, position.y * scale, width * scale, height * scale};
}

void Island::UpdateTexture(shared_ptr<MapChunk> chunk) {
	SDL_Rect area = chunk->getLocalRect();

	unsigned char* pixels = new unsigned char[area.w * area.h * 4];

	for (int y = 0; y < area.h; y++) {
		for (int x = 0; x < area.w; x++) {

			const unsigned int offset = (area.w * 4 * y) + x * 4;
			
            SDL_Color current = deep_water;
            auto alpha = SDL_ALPHA_OPAQUE;

            if ((x == 0 || y == 0)) {
                current = black;
                // alpha = SDL_ALPHA_TRANSPARENT;
            } else {
                double value = chunk->getHeightAt(x, y);

                if (value >= .15 && value < .3) { current = water; }
                if (value >= .3 && value < .4) { current = sand; }
                if (value >= .4 && value < .7) { current = grass; }
                if (value >= .7 && value < .9) { current = mountain; }
                if (value > .9) { current = snow; }
            }

			pixels[offset + 0] = current.b;        // b
			pixels[offset + 1] = current.g;        // g
			pixels[offset + 2] = current.r;        // r
			pixels[offset + 3] = alpha;            // a
		}
	}

	SDL_UpdateTexture(islandTex, &area, &pixels[0], area.w * 4);

	delete pixels;
}