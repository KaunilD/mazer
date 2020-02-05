#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>

using std::vector;
using std::cout;
using std::endl;

class Algorithms {

public:

	vector<int> grid;
	int width, height;
	int sx, sy;
	std::array<char, 4> directions;

	Algorithms(unsigned int h, unsigned int w);

	void resetGrid();
	int xyToIndex(int x, int y);
	vector<int> indexToxy(int index);
	bool inBounds(int x, int y);
	void backtrackRecursively(int sx, int sy);
	bool helper(int sx, int sy);
	void printGrid();
};

#endif