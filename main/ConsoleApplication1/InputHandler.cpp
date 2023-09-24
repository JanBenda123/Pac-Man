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
			Event* e = new  Event(1, ch);
			this->eventLoop->appendEvent(e);
			if (ch == 'q') {
				Event* e = new  Event(2, 'W');
				this->eventLoop->appendEvent(e);
			}
			if (ch == 'e') {
				Event* e = new  Event(2, 'L');
				this->eventLoop->appendEvent(e);
			}
		}
	}
}