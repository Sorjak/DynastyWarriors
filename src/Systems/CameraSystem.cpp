#include "CameraSystem.h"

CameraSystem::CameraSystem(int screenWidth, int screenHeight) {
	view = { 0, 0, screenWidth, screenHeight };

}

CameraSystem::~CameraSystem() {}

void CameraSystem::update() {

}

void CameraSystem::moveView(SDL_Point delta) {
    view.x += delta.x;
    view.y += delta.y;
}