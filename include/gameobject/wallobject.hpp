#ifndef WALLOBJECT_H
#define WALLOBJECT_H

#include "gameobject/gameobject.hpp"

class WallObject : public GameObject {

public:
	WallObject(bool npc);
	virtual void updateObject(int frames, QKeyEvent * event, const shared_ptr<Algorithms> & mazeGrid);
};

#endif