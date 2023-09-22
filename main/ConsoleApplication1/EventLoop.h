#pragma once

#include <string>
#include <list>
#include "Renderer.h"


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
public:
	bool queueUnlocked;
	Level* level;
	InputHandler* inputHandler;
	std::list<Event*> eventQueue;
	EventLoop(Level* level);
	void processQueue();
	void clear();
	void startIHThread();
	void appendEvent(Event e);

};



