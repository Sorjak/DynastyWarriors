#include "Animation.h"


Animation::Animation(int column, int numframes, bool repeat, std::string nextAnimation) {
	mColumn = column;
	mNumFrames = numframes;
	mRepeat = repeat;
	mNextAnimation = nextAnimation;
}

Animation::Animation(int column, int numframes) {
	mColumn = column;
	mNumFrames = numframes;
	mRepeat = true;
}

Animation::~Animation(){}

bool Animation::isRepeat() {
	return mRepeat;
}
