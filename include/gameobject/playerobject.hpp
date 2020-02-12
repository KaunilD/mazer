#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
#include "gameobject/gameobject.hpp"

class PlayerObject : public GameObject{

public:
	PlayerObject(bool npc);
	virtual void updateObject(int frames, QKeyEvent * event, const shared_ptr<Algorithms> & mazeGrid);
};

#endif