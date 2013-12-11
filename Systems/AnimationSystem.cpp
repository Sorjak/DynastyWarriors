#include "AnimationSystem.h"


AnimationSystem::AnimationSystem(int aps){
	framesPassed = 0;
	animationsPerSecond = aps;
}


AnimationSystem::~AnimationSystem(){}


void AnimationSystem::update() {
	if (framesPassed >=  60.f / animationsPerSecond) {
		for (size_t i = 0; i < entityList.size(); i++) {
			BaseEntity* current = entityList[i];

			if (current->hasComponent("animation") ) {
				AnimationComponent* ac = (AnimationComponent*) current->getComponent("animation");

				if (current->hasComponent("player_motion") ){
					PlayerMotionComponent* pmc = (PlayerMotionComponent*) current->getComponent("player_motion");

					if (pmc->fighterAttackState != "") {
						ac->setState(pmc->fighterAttackState);
					} else {
						ac->setState(pmc->fighterState);
					}
				}

				if (ac->currentFrame == ac->getTotalFrames() - 1) {

					if (!ac->isRepeat()) {
						ac->setState(ac->getNextAnimation());

						if (current->hasComponent("player_motion") ){
							PlayerMotionComponent* pmc = (PlayerMotionComponent*) current->getComponent("player_motion");
							if (pmc->fighterAttackState != "") {
								pmc->fighterAttackState = "";
							} else {
								pmc->fighterState = ac->getNextAnimation();
							}
						}
					} else {
						ac->currentFrame = 0;
					}	
				} else {
					ac->currentFrame++;
				}
			}
		}
		framesPassed = 0;
	} else {
		framesPassed++;
	}


}