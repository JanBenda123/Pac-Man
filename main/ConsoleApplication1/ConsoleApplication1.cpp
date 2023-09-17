#include <iostream>
#include <string>
#include "Level.h"
#include "Renderer.h"
#include "EventLoop.h"


int main()
{
	Level level("l1.txt");
	level.load();
}

