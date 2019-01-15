#pragma once
#include <vector>
class Pattern
{
private:
	std::vector<std::vector<std::vector<bool>>> seed;
public:
	Pattern();
	friend class Grid;
	enum {
		glider,
		blinker,
		dakota,
		gosper,
		rpent,
		croc,
		fountain,
		copperhead
	};
};

