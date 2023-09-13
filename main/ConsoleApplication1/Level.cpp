#include "Level.h"
#include <iostream>
#include <fstream>
#include "GameObjects.h"

Level::Level(std::string layoutFilePath) {
	this->width = 10;
	this->height = 10;
	int size = (width + 2) * height - 2;// +-2 to account for line breaks

	std::ifstream layoutFile(layoutFilePath, std::ios::binary);
	this->levelLayout = new char[size + 1];// for line tremanation
	layoutFile.read(this->levelLayout, size);
	this->levelLayout[size] = '\0';  // terminate the string
}

void Level::load() {
	/// <summary>
	/// Loads the level - processes layout string into sorted object list;
	/// </summary>
	
	int i = 0;
	char c;

	for (int y = 0; y < this->height ; y++) {
		for (int x = 0; x < this->width+2; x++) {
			c = levelLayout[x + y * (this->width + 2)];
			if (c == ' ' || c == '\n' || c == '\r') {
				continue;
			}

			GameObject* newObj;
			if (c == 'A') {
				newObj = new DynGameObject();
			}
			else if (c == 'X') {
				newObj = new ObjDeco('X');
			}
			else {
				newObj = new ObjDeco(c);
			}

			newObj->x = x;
			newObj->y = y;
			this->objectList.push_back(newObj);

		}
	}

}

void Level::step() {
	/// <summary>
	/// Steps the time in the level
	/// </summary>
	
	for (std::list<GameObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); it++) {
		(*it)->step();
	}
	objectList.sort([](const GameObject* a, const GameObject* b) -> bool {
		return a->y < b->y || (a->y == b->y && a->x < b->x);
		});



}
