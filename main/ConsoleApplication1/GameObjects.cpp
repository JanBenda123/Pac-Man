#include "GameObjects.h"

GameObject::GameObject() {
	this->sprite = ' ';
	this->zIndex = 1;
	this->isDyn = false;
}

void GameObject::step() {
	
}




DynGameObject::DynGameObject() {
	this->dir = 0;
	this->sprite = 'D';
	this->zIndex = 2;
	this->isDyn = true;
}

 void DynGameObject::step(){
	 switch (this->dir)
	 {
		 case 1:this->x++; break;
		 case 2:this->y--; break;
		 case 3:this->x--; break;
		 case 4:this->y++; break;
	 }
	

}


 ObjPlayer::ObjPlayer() {
	 this->dir = 0;
	 this->sprite = 'D';
	 this->zIndex = 2;
	 this->isDyn = true;
 }


ObjDeco::ObjDeco(char sprite) {
	this->sprite = sprite;
}

