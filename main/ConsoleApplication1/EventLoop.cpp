#include "EventLoop.h"
#include "Level.h"
#include "GameObjects.h"
//For sleep on Windows
#include <windows.h>
// For sleep on Linux
//#include <unistd.h>

/*
Event loop spravuje Eventy vytvo�en� hern�mi objekty a input handlerem
*/
EventLoop::EventLoop(Level* level) {
	this->level = level;

}

void EventLoop::processQueue() {
	level->step();
	level->renderer->render();
	Sleep(2000);
	this->processQueue();
}