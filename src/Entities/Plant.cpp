#include "Plant.h"

Plant::Plant(SDL_Texture* tex, int x, int y) {
    this->texture       = tex;
    this->position      = {x, y};
    this->hasTexture    = false;
}

Plant::~Plant() {
    // SDL_DestroyTexture(texture);
}

void Plant::Render(SDL_Renderer* ren, SDL_Rect* drawRect, int scale) {
    SDL_Rect sprect = { 
        (position.x - drawRect->x) * scale, 
        (position.y - drawRect->y) * scale, 
        drawRect->w * scale, drawRect->h * scale
    };

    if (hasTexture) {
        SDL_RenderCopy(ren, texture, NULL, &sprect);
    } else {
        Circle c = {sprect.x, sprect.y, (ageValue / 5) * scale};
        SDL_Color color = {255, 0, 0, 255};
        c.DrawCircle(ren, color);
    }
}
void Plant::Update() {
    ageValue = min(ageValue + .03f, 100.0f);
}

float Plant::GetEaten(float amount) {
    if (ageValue - amount > 0) {
        ageValue -= amount;
        return amount;
    }
    
    ageValue -= amount;
    return 0;
}