#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>
#include <ctime>
#include <cstdlib>

using std::vector;
using std::cout;
using std::endl;

class Algorithms {

public:

	vector<int> *grid;
	int width, height;
	int sx, sy, ex, ey;
	std::array<char, 4> directions;

	Algorithms();

	void resetGrid();
	int xyToIndex(int x, int y);
	vector<int> indexToxy(int index);
	bool inBounds(int x, int y);
	void backtrackRecursively(int sx, int sy);
	bool helper(int sx, int sy);
	void printGrid();

	int randomInt(int max);
};

#endif