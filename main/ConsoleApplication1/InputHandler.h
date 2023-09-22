#pragma once
#include "EventLoop.h"
class InputHandler
{
public:
	EventLoop* eventLoop;
	InputHandler(EventLoop* eventLoop);
	void startListeningLoop();
};

