#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "gameobject/gameobject.hpp"

class WallObject : public GameObject {

public:
	WallObject(bool npc, QString objPath, QVector3D color);
	virtual void updateObject(int frames, QKeyEvent * event, Algorithms * mazeGrid);
};

#endif