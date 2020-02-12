#include "gameobject/wallobject.hpp"


WallObject::WallObject(bool npc): GameObject(npc) {
	initializeOpenGLFunctions();
}

void WallObject::updateObject(int frames, QKeyEvent * event, const shared_ptr<Algorithms> & mazeGrid) {
	return;
}

