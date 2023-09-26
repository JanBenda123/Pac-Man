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
	this->eventQueue = new std::list<Event*>();
	this->queueUnlocked = true;
	this->toBeTerminated = false;
}
bool EventLoop::checkIfTerminated() {
	return this->toBeTerminated;
}


EventLoop::~EventLoop() {
	this->toBeTerminated = true;
	this->clear();
	delete this->eventQueue; 
	//this->inputHandlerThread->~thread();

}

void EventLoop::lockQueue() {
	this->queueUnlocked = false;
}

void EventLoop::unlockQueue() {
	this->queueUnlocked = true;
}

void EventLoop::clear() {
	this->eventQueue->clear();

}

void EventLoop::processQueue() {
	//add data lock for processing part
	this->lockQueue();
	for (Event* e : *(this->eventQueue)) {
		if (e->type == 2) {
			if (e->data == 'W') {//check for game ending events
				this->level->status = 1;
			}
			else {
				this->level->status = 2;
			}
			break;
		}
		for (GameObject* obj : *this->level->eventListeningObjectList) {
			obj->processEvent(e);
		}
	}
	this->clear();
	this->unlockQueue();
}

void EventLoop::appendEvent(Event* e) {
	if (this->queueUnlocked) {
		this->eventQueue->push_back(e); //Eventy možná budou mizet - zaniknou s ukonèením bìhu funkce v IH
	}
}



void inputListeningThread(EventLoop& el) {
	InputHandler* ih = new InputHandler(&el);
	ih->startListeningLoop();
	delete ih; //after it is signalled TBT, delete and finisth the thread
}

void EventLoop::startIHThread() {
	std::thread inputThread(inputListeningThread, std::ref(*this));
	this->inputHandlerThread = &inputThread;
	inputThread.detach();  
}
/*
1 - Keypress
2 - change of level status
*/


Event::Event(int type, char data) {
	this->type = type;
	this->data = data;
}



