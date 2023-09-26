#pragma once

#include <string>
#include <list>
#include "Renderer.h"
#include <thread>

class Level;
class GameObject;
class InputHandler;

class Event {
public:
	int type;
	char data;
	Event(int type, char data);
};


class EventLoop{	
private:
	void lockQueue();
	void unlockQueue();
	bool toBeTerminated;
	std::thread* inputHandlerThread;

public:
	bool checkIfTerminated();
	bool queueUnlocked;
	Level* level;
	InputHandler* inputHandler;
	std::list<Event*>* eventQueue;
	EventLoop(Level* level);
	~EventLoop();
	void processQueue();
	void clear();
	void startIHThread();
	void appendEvent(Event* e);

};



