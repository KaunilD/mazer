#include "algorithms.hpp"
#include <QDebug>
using std::vector;
using std::cout;
using std::endl;

Algorithms::Algorithms():directions({ {'N', 'E', 'W', 'S'} }) {
}

Algorithms::~Algorithms() {
	delete grid;
}
int Algorithms::randomInt(int max) {
	srand(time(0));
	return rand() % max;
}

void Algorithms::resetGrid() {
	for (int i = 0; i < width*height; i++) {
		grid->at(i) = 1;
	}
}

int Algorithms::xyToIndex(int x, int y) {
	return width * y + x;
}

vector<int> Algorithms::indexToxy(int index) {
	vector<int> location(2, 0);
	location[1] = (int)index / width;
	location[0] = index - (location[1] * width);
	return location;
}

bool Algorithms::inBounds(int x, int y) {
	if (x >= width || x < 0) return false;
	if (y >= height || y < 0) return false;

	return true;
}

bool Algorithms::helper(int w, int h) {
	grid = new vector<int>(w*h, 1);

	width = w;
	height = h;

	sx = randomInt(width);
	sy = randomInt(height);

	solved = false;
	
	backtrackRecursively(sx, sy);

	return true;
}

void Algorithms::backtrackRecursively(int sx, int sy) {
	
	qDebug() << sx << " " << sy;

	grid->at(xyToIndex(sx, sy)) = 0;
	
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
			if (grid->at(xyToIndex(xn, yn)) == 1) {
				ex = xn;
				ey = yn;
				grid->at(xyToIndex(xn - dx, yn - dy)) = 0;
				this->backtrackRecursively(xn, yn);
			}
		}
	}
}

void Algorithms::printGrid() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			qDebug() << grid[xyToIndex(j, i)];
		}
		qDebug() << "";
	}
}