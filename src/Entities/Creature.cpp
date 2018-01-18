#include "Creature.h"

Creature::Creature(SDL_Texture* tex, float x, float y) {
    SDL_QueryTexture(tex, NULL, NULL, &creatureWidth, &creatureHeight);

    this->texture           = tex;
    this->bodyBounds        = {0, 0, creatureWidth, creatureHeight};
    this->hasTexture        = true;
    this->position          = {x, y};
    this->target            = {x, y};
    this->speed             = max(getRand01(), .5f);
}

Creature::~Creature() {}

void Creature::Render(SDL_Renderer* ren, SDL_Rect* drawRect, int scale) {
    if (hasTexture) {
        bodyBounds.x = position.x; bodyBounds.y = position.y;
        SDL_Rect sprect = { 
            (position.x - drawRect->x) * scale, 
            (position.y - drawRect->y) * scale, 
            drawRect->w * scale, drawRect->h * scale
        };
        SDL_RenderCopy(ren, texture, NULL, &sprect);
    }
}

void Creature::MoveTo(float x, float y){
    target = {x, y};
}

void Creature::Eat(float amount) {
    hungerValue -= amount;
}

// void Creature::Wander() {
//     Circle c = {(int)position.x, (int)position.y, 30};

//     target = c.GetRandomPoint();
//     cout << "Wander target: " << target.x << ", " << target.y << endl;
// }

void Creature::Update() {
    ageValue += .005;
    hungerValue += .1;

    Vector2 moveVector = target - position;

    if (moveVector.length() > 0) {
        Vector2 normalized = moveVector.normalize();

        position.x += normalized.x * speed;
        position.y += normalized.y * speed;
    }
}

/******************************************** Texture creation static methods */

void GenerateBody(int width, int height, bool* bodyPoints, SDL_Rect* bounds) {
    float noiseScale = 300.0;
    SDL_Point noiseOffset = { (int) getRand(10000), (int) getRand(10000) };

    int numBodyPoints = 0;

    SDL_Point* enclosurePoints = new SDL_Point[width * height];

    NoiseModule nm;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            float sampleX = (x + noiseOffset.x) / noiseScale;
            float sampleY = (y + noiseOffset.y) / noiseScale;

            float r = max((float) -1.0,  nm.GetNoise2D(sampleX, sampleY));
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

SDL_Texture* MakeSprite(SDL_Renderer* ren, int fullWidth, bool* bodyPoints, SDL_Rect* bounds) {
    SDL_Texture* textureOutput = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STATIC, bounds->w, bounds->h);
    SDL_SetTextureBlendMode(textureOutput, SDL_BLENDMODE_BLEND);

    SDL_Color spriteColor = { getRand01() * 255, 
         getRand01() * 255, getRand01() * 255, SDL_ALPHA_OPAQUE };

    unsigned char* pixels = new unsigned char[bounds->w * bounds->h * 4];

    int eyeCenterX = bounds->w / 2;
    int eyeCenterY = bounds->h / 2 ;

    Circle eyeball = { eyeCenterX, eyeCenterY, (int) (bounds->w * .1) };
    Circle pupil = { eyeCenterX, eyeCenterY, (int) (bounds->w * .02) };

    for (int y = 0; y < bounds->h; y++) {
        for (int x = 0; x < bounds->w; x++) {
            
            SDL_Color pixelColor = { 0, 0, 0, SDL_ALPHA_TRANSPARENT };
            bool isBodyPart = bodyPoints[(x + bounds->x) + fullWidth * (y + bounds->y)];

            if (isBodyPart) pixelColor = spriteColor;

            pixelColor = eyeball.CheckPoint(x, y) ? white : pixelColor;
            pixelColor = pupil.CheckPoint(x, y) ? black : pixelColor;

            // Get the pixel offset taking into account all color channels.
            const unsigned int offset = (bounds->w * 4 * y) + x * 4;

            pixels[offset + 0] = pixelColor.b;  // b
            pixels[offset + 1] = pixelColor.g;  // g
            pixels[offset + 2] = pixelColor.r;  // r

            pixels[offset + 3] = pixelColor.a;  // alpha
        }
    }

    SDL_UpdateTexture(textureOutput, NULL, &pixels[0], bounds->w * 4);

    delete pixels;

    return textureOutput;
}