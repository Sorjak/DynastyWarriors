#include "AnimationSystem.h"


AnimationSystem::AnimationSystem(){}


AnimationSystem::~AnimationSystem(){}


void AnimationSystem::update() {
	for (size_t i = 0; i < entityList.size(); i++) {
		BaseEntity* current = entityList[i];


		if (current->hasComponent("animation") ) {
			AnimationComponent* ac = (AnimationComponent*) current->getComponent("animation");
			if (current->hasComponent("player_motion") ){
				PlayerMotionComponent* pmc = (PlayerMotionComponent*) current->getComponent("player_motion");
				ac->setState(pmc->fighterState);
			}
			if (ac->currentFrame == ac->getTotalFrames() - 1) {
				ac->currentFrame = 0;
			} else {
				ac->currentFrame++;
			}
		}
	}
}