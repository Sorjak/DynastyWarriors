#pragma once

#include <string>

class Animation
{
public:
	Animation(int column, int numframes, bool repeat, std::string nextAnimation);
	Animation(int column, int numframes);
	~Animation();

	int mColumn;
	int mNumFrames;
	bool mRepeat;
	std::string mNextAnimation;
};

