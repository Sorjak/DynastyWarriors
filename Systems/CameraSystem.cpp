#include "CameraSystem.h"

CameraSystem::CameraSystem(int screenWidth, int screenHeight) {
    view.w = screenWidth;
    view.h = screenHeight;

}

CameraSystem::~CameraSystem() {}

void CameraSystem::update() {

}

void CameraSystem::moveView(SDL_Point delta) {
    view.x += delta.x;
    view.y += delta.y;

    cout << "Current view is x: " << view.x << ", y: " << view.y << endl;
}