#pragma once
#include <string>

class GameObject {
public:
	char sprite;
	int x;
	int y;
	int zIndex;
	bool isDyn;
	GameObject();
	virtual void step();

};

class DynGameObject :public GameObject {
public:
	int dir; // 0 - still, 1 - right, 2 - up, 3 - left, 4 - down
	DynGameObject();
	void step() override;
};

class ObjDeco :public GameObject {
public:
	ObjDeco(char sprite);
};