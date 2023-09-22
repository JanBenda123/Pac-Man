#include "GameObjects.h"
#include "EventLoop.h"


GameObject::GameObject() {
	this->sprite = ' ';
	this->zIndex = 1;
	this->isDyn = false;
	this->typeId = 0;
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
	//Kontroluje pøímé kolitze a vrátí pøíslušný objekt
	return this->level->isObjAt(this->x, this->y, typeId);
};

void GameObject::remove() {
	this->level->objectList.remove(this);
	this->level->eventListeningObjectList.remove(this);
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

 void DynGameObject::step(){
	 if (this->checkForwardCollision(4) == NULL) {
		 switch (this->dir)
		 {
		 case 1:this->x++; break;
		 case 2:this->y--; break;
		 case 3:this->x--; break;
		 case 4:this->y++; break;
		 }
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
	 DynGameObject::step();
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
