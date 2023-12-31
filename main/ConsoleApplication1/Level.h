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
	int status;
	EventLoop* eventLoop;
	Renderer* renderer;
	std::list<GameObject*>* objectList;
	std::list<GameObject*>* eventListeningObjectList;
	Level(std::string layoutFilePath);
	~Level();
	GameObject* isObjAt(int x, int y, int typeId);

	void removeFlaggedObjects();
	void load();
	bool play();
	void step();
	bool isFinished();

}; 

