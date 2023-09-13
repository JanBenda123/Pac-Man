#pragma once
#include <string>
#include <list>
#include "GameObjects.h"

class Level
{
private:
	char* levelLayout;
public:
	int width;
	int height;
	std::list<GameObject*> objectList;
	Level(std::string layoutFilePath);
	
	void load();
	void step();
	

}; 

