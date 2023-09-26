#include "Level.h"
#include "Renderer.h"
#include "EventLoop.h"
#include <iostream>
#include <fstream>
#include <thread>
#include "GameObjects.h"



Level::Level(std::string layoutFilePath) {
	this->width = 20;
	this->height = 15;
	this->status = 0; //0 - played, 1 - won, 2 - lost 
	int size = (width + 2) * height - 2;// +-2 to account for line breaks

	std::ifstream layoutFile(layoutFilePath, std::ios::binary);
	this->levelLayout = new char[size + 1];// for line temanation
	layoutFile.read(this->levelLayout, size);
	this->levelLayout[size] = '\0';  // terminate the string

	this->eventLoop = new EventLoop(this);
	this->renderer = new Renderer(this);
	this->objectList = new std::list<GameObject*>();
	this->eventListeningObjectList = new std::list<GameObject*>();
}


Level::~Level() {
	delete this->eventLoop;
	delete this->renderer;
	std::list<GameObject*>::iterator it = this->objectList->begin();
	
	while (it != this->objectList->end()) {
		delete* it;
		it = this->objectList->erase(it);
	}
	delete this->objectList;
	delete this->eventListeningObjectList;
	


}

void Level::load() {
	int i = 0;
	char c;

	for (int y = 0; y < this->height; y++) {//loads the level
		for (int x = 0; x < this->width + 2; x++) {
			c = levelLayout[x + y * (this->width + 2)];
			if (c == ' ' || c == '\n' || c == '\r') {//skip for empty files
				continue;
			}
			GameObject* newObj;

			//Parses level text files to game objects
			if (c == 'P') {
				newObj = new ObjPlayer();
			}
			else if (c == 'X') {
				newObj = new ObjWall();
			}
			else if (c == '.') {
				newObj = new ObjPoint();
			}
			else if (c == '#') {
				newObj = new ObjMonster();
			}
			else {
				newObj = new ObjDeco(c);
			}

			newObj->addLevelPointer(this);
			newObj->x = x;
			newObj->y = y;
			this->objectList->push_back(newObj);
			if (newObj->listensToEvents) {
				this->eventListeningObjectList->push_back(newObj);
			}
		}
	}
}

bool Level::isFinished() {
	for (GameObject* obj : *(this->objectList)) {
		if (obj->typeId == 5) {
			return false;
		}
	}
	return true;
}

bool Level::play() {
	/// <summary>
	/// Loads the level - processes layout string into sorted object list;
	/// </summary>
	
	this->load();
	
	this->eventLoop->startIHThread();
	while (true) {
		this->eventLoop->processQueue();//begin-step processing
		this->step();
		this->renderer->render();
		if (this->isFinished()) {
			this->status = 1;
		}
		if (this->status) {
			break;
		}
		
		std::this_thread::sleep_for(std::chrono::microseconds(200 * 1000));
	}


	if (this->status==1){
		return true;
	}
	else {
		return false;
	}
}

void Level::removeFlaggedObjects() {
	std::list<GameObject*>::iterator it = this->objectList->begin();
	while (it != this->objectList->end()) {
		if ((*it)->flagRm) {
			this->eventListeningObjectList->remove(*it);
			it = this->objectList->erase(it);// When object is deleted, Iterator already points to the next one	
		}
		else {
			it++;
		}
	}
}


void Level::step() {
	/// <summary>
	/// Steps the time in the level
	/// </summary>
	
	for (std::list<GameObject*>::iterator it = this->objectList->begin(); it != this->objectList->end(); it++) {
		(*it)->step();
	}

	this->removeFlaggedObjects();

	objectList->sort([](const GameObject* a, const GameObject* b) -> bool {
		return a->y < b->y || (a->y == b->y && a->x < b->x);
		});



}

GameObject* Level::isObjAt(int x, int y, int typeId) {
	for (GameObject* go : *this->objectList) {
		if (go->x == x && go->y == y && go->typeId == typeId) {
			return go;
		}
	}
	return NULL;
};

