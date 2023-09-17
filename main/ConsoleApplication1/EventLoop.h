#pragma once

#include <string>
#include "Renderer.h"

class Level;
class GameObject;
class EventLoop
{	
public:
	Level* level;
	//std::list<Event*> eventQueue;
	EventLoop(Level* level);
	void processQueue();
};

class Event {
public:
	std::string type;
	GameObject* target;
	Event(std::string type, GameObject* target);
};

