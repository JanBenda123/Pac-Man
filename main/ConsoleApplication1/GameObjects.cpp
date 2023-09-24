#include "GameObjects.h"
#include "EventLoop.h"
#include <cstdlib>


GameObject::GameObject() {
	this->listensToEvents = false;
	this->sprite = ' ';
	this->zIndex = 1;
	this->isDyn = false;
	this->typeId = 0;
	this->flagRm = false;
}

void GameObject::addLevelPointer(Level* level) {
	this->level = level;
}

void GameObject::step() {
	
}

void GameObject::processEvent(Event* e)
{
}

GameObject* GameObject::checkDirectCollision(int typeId) {
	//Kontroluje pøímé kolize a vrátí pøíslušný objekt
	return this->level->isObjAt(this->x, this->y, typeId);
};

void GameObject::remove() {
	this->flagRm = true;
}


ObjWall::ObjWall() {
	this->sprite = 'X';
	this->zIndex = 1;
	this->typeId = 4;
}



DynGameObject::DynGameObject() {
	this->dir = 1;
	this->sprite = 'D';
	this->zIndex = 2;
	this->isDyn = true;
	this->typeId = 2;
	this->listensToEvents = false;
}

void DynGameObject::move()
{
	switch (this->dir)
	{
	case 1:this->x++; break;
	case 2:this->y--; break;
	case 3:this->x--; break;
	case 4:this->y++; break;
	}
}

 void DynGameObject::step(){
	 if (this->checkForwardCollision(4) == NULL) {
		 this->move();
	 }
	 else {
		 dir = 0;
	 }
}





 GameObject* DynGameObject::checkForwardCollision(int typeId) {
	 int cx = this->x;
	 int cy = this->y;

	 switch (this->dir)
	 {
		case 0: return NULL;
		case 1:cx++; break;
		case 2:cy--; break;
		case 3:cx--; break;
		case 4:cy++; break;
	 }

	 return this->level->isObjAt(cx, cy, typeId);
 
 };



ObjPlayer::ObjPlayer() {
	 this->sprite = 'P';
	 this->typeId = 3;
	 this->listensToEvents = true;
 }

void ObjPlayer::step() {
	 
	 GameObject* obj = this->checkDirectCollision(6);
	 if (obj != NULL) {
		 Event* e = new Event(2, 'L');
		 this->level->eventLoop->appendEvent(e);
	 }
	DynGameObject::step();

	 if (this->checkDirectCollision(6) != NULL) {
		 Event* e = new Event(2, 'L');
		 this->level->eventLoop->appendEvent(e);

	 }
	 
 }

 void ObjPlayer::processEvent(Event* e)
 {
	 switch (e->type)
	 {
	 case 1:
		 switch (e->data) {
			case 'w':this->dir = 2; break;
			case 'a':this->dir = 3; break;
			case 's':this->dir = 4; break;
			case 'd':this->dir = 1; break;
		 }
	 }
 }



ObjDeco::ObjDeco(char sprite) {
	this->sprite = sprite;
	this->typeId = 1;
}

ObjPoint::ObjPoint()
{
	this->sprite = '.';
	this->typeId = 5;
}

void ObjPoint::step() {
	if (this->checkDirectCollision(3) != NULL) {
		this->remove(); //removing while still being pointed at in Level causes shit go haywire. Fix ASAP 
	}
}



ObjMonster::ObjMonster() {
	this->sprite = '#';
	this->typeId = 6;
	this->dir = 0;
}

void ObjMonster::step()
{
	int tryCounter = 0;
	while (this->checkForwardCollision(6) != NULL || this->checkForwardCollision(4) != NULL || this->dir == 0) {
		tryCounter++;
		this->dir = 1 + std::rand() % 4;
		if (tryCounter > 100) {// trapped monster condition
			this->dir = 0;
			break;
		}
	}
	this->move();
}
