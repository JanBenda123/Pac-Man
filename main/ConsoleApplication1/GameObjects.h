#pragma once
#include <string>
#include "Level.h"
#include "EventLoop.h"

class Level;
class Event;

class GameObject {
public:
	char sprite;
	int x;
	int y;
	int zIndex;
	bool isDyn;
	bool listensToEvents;
	int typeId;
	Level* level;
	GameObject();
	virtual void step();
	virtual void processEvent(Event* e);
	void addLevelPointer(Level* level);
	
};

class DynGameObject :public GameObject {
public:
	int dir; // 0 - still, 1 - right, 2 - up, 3 - left, 4 - down
	DynGameObject();
	void step() override;
	GameObject* checkDirectCollision(int typeId);
	GameObject* checkForwardCollision(int typeId);
};

class ObjWall :public GameObject {
public:
	ObjWall();
};

class ObjPlayer :public DynGameObject {
public:
	ObjPlayer();
	void step() override;
	void processEvent(Event* e) override;
};

class ObjDeco :public GameObject {
public:
	ObjDeco(char sprite);
};