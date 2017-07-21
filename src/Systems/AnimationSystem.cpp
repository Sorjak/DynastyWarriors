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

			if (current->hasComponent("animation") && current->hasComponent("state")) {
				mAnimation = (AnimationComponent*) current->getComponent("animation");
				mState = (StateComponent*)current->getComponent("state");
				
				// if (mState->lastUpdated == "HORIZONTAL") {
				// 	mAnimation->setState(mState->getHorizonalState());
				// }
				// else if (mState->lastUpdated == "VERTICAL") {
				// 	if (mState->getVerticalState() == "GROUND") {
				// 		mAnimation->setState("IDLE");
				// 	}
				// 	else {
				// 		mAnimation->setState(mState->getVerticalState());
				// 	}
				// }
				// else if (mState->lastUpdated == "ATTACK") {
				// 	mAnimation->setState(mState->getAttackState());
				// }

				if (mAnimation->currentFrame == mAnimation->getTotalFrames() - 1) {

					if (!mAnimation->isRepeat()) {
						string next = mAnimation->getNextAnimation();
						mAnimation->setState(next);
						if (mState->lastUpdated == "HORIZONTAL") {
							// mState->setHorizontalState(next);
						}
						else if (mState->lastUpdated == "VERTICAL") {
							// mState->setVerticalState(next);
						}
						else if (mState->lastUpdated == "ATTACK") {
							// mState->setAttackState(next);
						}

					} else {
						mAnimation->currentFrame = 0;
					}	
				} else {
					mAnimation->currentFrame++;
				}
			}
		}
		framesPassed = 0;
	} else {
		framesPassed++;
	}


}