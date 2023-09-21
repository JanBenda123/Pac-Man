#pragma once
#include <string>
#include <list>
#include "GameObjects.h"


class Renderer; 
class EventLoop;
class GameObject;

class Level
{
private:
	char* levelLayout;
public:
	int width;
	int height;
	EventLoop* eventLoop;
	Renderer* renderer;
	std::list<GameObject*> objectList;
	Level(std::string layoutFilePath);
	GameObject* isObjAt(int x, int y, int typeId);

	
	void load();
	void step();
	

}; 

