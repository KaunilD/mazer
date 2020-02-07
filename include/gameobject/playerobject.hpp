#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include "gameobject/gameobject.hpp"

class PlayerObject : public GameObject{

public:
	PlayerObject(bool npc, const QString & objPath, const QString & textureFile,  QVector3D color);
	virtual void updateObject(int frames, QKeyEvent * event, Algorithms * mazeGrid);
};

#endif