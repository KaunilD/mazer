#include "algorithms.hpp"
using std::vector;
using std::cout;
using std::endl;

Algorithms::Algorithms(unsigned int h, unsigned int w) :width(w), height(h), directions({ {'N', 'E', 'W', 'S'} }) {
	grid = vector<int>(width*height, 1);
}

void Algorithms::resetGrid() {
	for (int i = 0; i < width*height; i++) {
		grid[i] = 1;
	}
}

int Algorithms::xyToIndex(unsigned int x, unsigned int y) {
	return width * x + y;
}

vector<int> Algorithms::indexToxy(int index) {
	vector<int> location(2, 0);
	location[1] = (int)index / height;
	location[0] = index - (location[1] * width);
	return location;
}

bool Algorithms::inBounds(int x, int y) {
	if (x >= width || x < 0) return false;
	if (y >= height || y < 0) return false;

	return true;
}

void Algorithms::backtrackRecursively(int sx, int sy) {
	grid[xyToIndex(sx, sy)] = 0;

	shuffle(directions.begin(), directions.end(), std::default_random_engine(rand()));

	for (int i = 0; i < 4; i++) {
		int dx = 0, dy = 0;
		switch (directions[i]) {
		case 'N': dy = -1; break;
		case 'E': dx = 1; break;
		case 'W': dx = -1; break;
		case 'S': dy = 1; break;
		}

		int xn = sx + (dx << 1);
		int yn = sy + (dy << 1);

		if (inBounds(xn, yn)) {
			if (grid[xyToIndex(xn, yn)] == 1) {
				grid[xyToIndex(xn - dx, yn - dy)] = 0;
				this->backtrackRecursively(xn, yn);
			}
		}
	}
}

void Algorithms::printGrid() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << grid[xyToIndex(j, i)];
		}
		cout << endl;
	}
}