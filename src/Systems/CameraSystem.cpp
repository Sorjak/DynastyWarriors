#include "CameraSystem.h"

CameraSystem::CameraSystem(int screenWidth, int screenHeight) {
	view = { 0, 0, screenWidth, screenHeight };
}

CameraSystem::~CameraSystem() {}

void CameraSystem::init(Engine* e) {
    mEngine = e;

    input = static_pointer_cast<InputSystem>(mEngine->getSystem("input"));
}

void CameraSystem::update() {
    SDL_Point delta = {0, 0};

    if (input->isDown("Q")) {
        mEngine->setRunning(false);
    }

    if (input->isDown("A")) {
        delta.x -= moveAmount;
    }

    if (input->isDown("D")) {
        delta.x += moveAmount;
    }

    if (input->isDown("W")) {
        delta.y -= moveAmount;
    }

    if (input->isDown("S")) {
        delta.y += moveAmount;
    }

    moveView(delta);
}

void CameraSystem::moveView(SDL_Point delta) {
    view.x += delta.x;
    view.y += delta.y;
}