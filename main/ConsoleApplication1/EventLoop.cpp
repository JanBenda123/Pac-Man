#include "EventLoop.h"
#include "Level.h"
#include "GameObjects.h"
#include "InputHandler.h"
#include <thread>
#include <chrono>
#include <iostream>

/*
Event loop spravuje Eventy vytvoøené herními objekty a input handlerem
*/
EventLoop::EventLoop(Level* level) {
	this->level = level;
	this->eventQueue = std::list<Event*>();
	
	this->queueUnlocked = true;


}
void EventLoop::lockQueue() {
	this->queueUnlocked = false;
}

void EventLoop::unlockQueue() {
	this->queueUnlocked = true;
}

void EventLoop::clear() {
	this->eventQueue.clear();

}

void EventLoop::processQueue() {
	//add data lock for processing part
	this->lockQueue();
	for (Event* e : this->eventQueue) {
		for (GameObject* obj : this->level->eventListeningObjectList) {
			//std::cout << e->data;
			obj->processEvent(e);
		}
	}
	this->clear();
	this->unlockQueue();
	level->step();
	level->renderer->render();
	std::this_thread::sleep_for(std::chrono::microseconds(500*1000));
}

void EventLoop::appendEvent(Event e) {
	if (this->queueUnlocked) {
		this->eventQueue.push_back(&e); //Eventy možná budou mizet - zaniknou s ukonèením bìhu funkce v IH
	}
}



void inputListeningThread(EventLoop& el) {
	InputHandler ih(&el);
	ih.startListeningLoop();
}

void EventLoop::startIHThread() {
	std::thread inputThread(inputListeningThread, std::ref(*this));
	inputThread.detach();  
}
/*
1 - Keypress
*/


Event::Event(int type, char data) {
	this->type = type;
	this->data = data;
}



