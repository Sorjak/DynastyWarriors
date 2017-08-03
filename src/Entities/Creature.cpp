#import "Creature.h"

Creature::Creature(int w, int h) {
    this->creatureWidth     = w;
    this->creatureHeight    = h;
    this->position          = { 0, 0 };

    // GenerateBody();
    // MakeSprite();
}

Creature::Creature(SDL_Texture* tex) {
    SDL_QueryTexture(tex, NULL, NULL, &creatureWidth, &creatureHeight);

    this->texture = tex;
    this->bounds = {0, 0, creatureWidth, creatureHeight};
}

Creature::Creature(SDL_Texture* tex, int w, int h) {
    this->creatureWidth     = w;
    this->creatureHeight    = h;

    this->texture           = tex;
    this->bounds = {0, 0, creatureWidth, creatureHeight};
}

Creature::~Creature() {
    // cout << "Deleting creature" << endl;
}

void Creature::Render(SDL_Renderer* ren, SDL_Rect* drawRect) {
    if (texture == nullptr){
        MakeSprite(ren);
    }


    SDL_Rect sprect = { position.x - drawRect->x, position.y - drawRect->y, drawRect->w, drawRect->h };
    SDL_RenderCopy(ren, texture, NULL, &sprect);
}

void Creature::MoveTo(int x, int y) {
    position = { x, y };
}

void Creature::GenerateBody(int width, int height, bool* bodyPoints, SDL_Rect* bounds) {
    float noiseScale = 300.0;
    SDL_Point noiseOffset = { getRand(10000), getRand(10000) };

    int numBodyPoints = 0;

    SDL_Point* enclosurePoints = new SDL_Point[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            float sampleX = (x + noiseOffset.x) / noiseScale;
            float sampleY = (y + noiseOffset.y) / noiseScale;

            float r = max(-1.0, noiseModule.GetValue(sampleX, sampleY, 1.0));
            float sample = (r + 1) / 2;

            // Get x an y values between -1 and 1
            float horizontal = (x / (float)width) * 2 - 1;
            float vertical = 1 - (y / (float)height);

            // Which one is closer to the edge?
            float val = max(abs(horizontal), abs(vertical));

            // Gradual increase curve from 0 to 1
            float smoothed = smoothGradient(val, 3.0, 2.0);

            bool isBodyPart = sample - smoothed > 0;

            if (isBodyPart) {
                SDL_Point p = { x, y };
                enclosurePoints[numBodyPoints++] = p;
            }

            bodyPoints[x + width * y] = isBodyPart;
        }
    }

    SDL_EnclosePoints(enclosurePoints, numBodyPoints, NULL, bounds);

    delete enclosurePoints;
}

void Creature::MakeSprite(SDL_Renderer* ren) {
    texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STATIC, bounds.w, bounds.h);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_Color spriteColor = { getRand01() * 255, getRand01() * 255, getRand01() * 255, SDL_ALPHA_OPAQUE };

    unsigned char* pixels = new unsigned char[bounds.w * bounds.h * 4];

    int eyeCenterX = bounds.w / 2;
    int eyeCenterY = bounds.h / 2 ;

    Circle eyeball = { eyeCenterX, eyeCenterY, bounds.w * .1 };
    Circle pupil = { eyeCenterX, eyeCenterY, bounds.w * .02 };

    for (int y = 0; y < bounds.h; y++) {
        for (int x = 0; x < bounds.w; x++) {
            
            SDL_Color pixelColor = { 0, 0, 0, SDL_ALPHA_TRANSPARENT };
            bool isBodyPart = bodyPoints[(x + bounds.x) + this->creatureWidth * (y + bounds.y)];

            if (isBodyPart) pixelColor = spriteColor;

            pixelColor = eyeball.CheckPoint(x, y) ? white : pixelColor;
            pixelColor = pupil.CheckPoint(x, y) ? black : pixelColor;

            // Get the pixel offset taking into account all color channels.
            const unsigned int offset = (bounds.w * 4 * y) + x * 4;

            pixels[offset + 0] = pixelColor.b;  // b
            pixels[offset + 1] = pixelColor.g;  // g
            pixels[offset + 2] = pixelColor.r;  // r

            pixels[offset + 3] = pixelColor.a;  // alpha
        }
    }

    SDL_UpdateTexture(texture, NULL, &pixels[0], bounds.w * 4);

    // bounds = {0, 0, bounds.w, bounds.h};

    delete pixels;
    delete bodyPoints;
}
