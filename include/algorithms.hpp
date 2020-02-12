#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "libs.hpp"

class Algorithms {

public:

	unique_ptr<vector<int>> grid;
	int width, height;
	int sx, sy, ex, ey;
	std::array<char, 4> directions;

	Algorithms();
	~Algorithms();

	void resetGrid();
	int xyToIndex(int x, int y);
	vector<int> indexToxy(int index);
	bool inBounds(int x, int y);
	bool isFree(int x, int y);
	void backtrackRecursively(int sx, int sy);
	bool helper(int sx, int sy);
	void printGrid();
	bool solved{ false };

	int randomInt(int max);
};

#endif