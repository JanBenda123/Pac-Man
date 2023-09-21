#pragma once
#include <string>
#include "Level.h"

class Level;

class GameObject {
public:
	char sprite;
	int x;
	int y;
	int zIndex;
	bool isDyn;
	int typeId;
	Level* level;
	GameObject();
	virtual void step();
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
};

class ObjDeco :public GameObject {
public:
	ObjDeco(char sprite);
};