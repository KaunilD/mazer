#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include "gameobject/gameobject.hpp"

class PlayerObject : public GameObject{

public:
	PlayerObject(bool npc, QString objPath, QVector3D color);
	virtual void updateObject(int frames, QKeyEvent * event, Algorithms * mazeGrid);
};

#endif