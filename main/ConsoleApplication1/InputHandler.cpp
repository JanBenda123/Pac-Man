#include "InputHandler.h"
#include <conio.h>
#include <iostream>

InputHandler::InputHandler(EventLoop* eventLoop) {
	this->eventLoop = eventLoop;
}
void InputHandler::startListeningLoop() {
	char ch;
	while (true) {
		if (_kbhit()) {
			ch = _getch();
			Event e = Event(1, ch);
			this->eventLoop->appendEvent(e);
		}
	}
}