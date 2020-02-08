#include "gameobject/wallobject.hpp"


WallObject::WallObject(bool npc): GameObject(npc) {
	initializeOpenGLFunctions();
}

void WallObject::updateObject(int frames, QKeyEvent * event, Algorithms * mazeGrid) {
	return;
}

