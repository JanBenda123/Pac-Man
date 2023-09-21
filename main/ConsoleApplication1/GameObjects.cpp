#include "GameObjects.h"

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




ObjWall::ObjWall() {
	this->sprite = 'X';
	this->zIndex = 1;
	this->isDyn = false;
	this->typeId = 4;
}



DynGameObject::DynGameObject() {
	this->dir = 1;
	this->sprite = 'D';
	this->zIndex = 2;
	this->isDyn = true;
	this->typeId = 2;
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

 GameObject* DynGameObject::checkDirectCollision(int typeId) {
	 return this->level->isObjAt(this->x, this->y, typeId);
 };

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
	 this->dir = 0;
	 this->sprite = 'P';
	 this->zIndex = 2;
	 this->isDyn = true;
	 this->typeId = 3;
 }

 void ObjPlayer::step() {
	
 }



ObjDeco::ObjDeco(char sprite) {
	this->sprite = sprite;
	this->typeId = 1;
}

