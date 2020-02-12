#include "gameobject/playerobject.hpp"


PlayerObject::PlayerObject(bool npc) : GameObject(npc) {
	initializeOpenGLFunctions();
}

void PlayerObject::updateObject(
	int frames, QKeyEvent * event, const shared_ptr<Algorithms> & mazeGrid
) {
	int x = translation[0];
	int y = translation[1];
	

	if (event->key() == Qt::Key_W) {
	
		if (mazeGrid->inBounds(x, y + 1) && mazeGrid->isFree(x, y + 1)) {
			
			modelMatrix->translate(QVector3D(0.0f, 1.0f, 0.0f));
			translation += QVector3D(0.0f, 1.0f, 0.0f);
		}
	}
	if (event->key() == Qt::Key_S) {
		if (mazeGrid->inBounds(x, y - 1) && mazeGrid->isFree(x, y - 1)) {
			modelMatrix->translate(QVector3D(0.0f, -1.0f, 0.0f));
			translation += QVector3D(0.0f, -1.0f, 0.0f);
		}
	}
	if (event->key() == Qt::Key_A) {
		if (mazeGrid->inBounds(x - 1, y) && mazeGrid->isFree(x - 1, y)) {
			modelMatrix->translate(QVector3D(-1.0f, 0.0f, 0.0f));
			translation += QVector3D(-1.0f, 0.0f, 0.0f);
		}
	}
	if (event->key() == Qt::Key_D) {
		if (mazeGrid->inBounds(x + 1, y) && mazeGrid->isFree(x + 1, y)) {
			modelMatrix->translate(QVector3D(1.0f, 0.0f, 0.0f));
			translation += QVector3D(1.0f, 0.0f, 0.0f);
		}
	}

	x = translation[0];
	y = translation[1];

	if (x == mazeGrid->ex && y == mazeGrid->ey) {
		mazeGrid->solved = true;
		return;
	}

}
