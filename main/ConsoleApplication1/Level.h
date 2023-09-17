#pragma once
#include <string>
#include <list>
#include "GameObjects.h"


class Renderer; 
class EventLoop;

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
	
	void load();
	void step();
	

}; 

