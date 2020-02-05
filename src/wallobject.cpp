#include "gameobject/wallobject.hpp"


WallObject::WallObject(bool npc, QString filePath, QVector3D color):
	GameObject(npc, filePath, color) {

		initializeOpenGLFunctions();
		loadObject(filePath);
}

void WallObject::updateObject(int frames, QKeyEvent * event, Algorithms * mazeGrid) {
	return;
}