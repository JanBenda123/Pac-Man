#include <iostream>
#include <string>
#include "Level.h"
#include "Renderer.h"


int main()
{
	Level level("l1.txt");
	level.load();
	Renderer renderer(&level);
	renderer.render();
	level.step();
	renderer.render();
	level.step();
	renderer.render();
	level.step();
	renderer.render();
	level.step();
	renderer.render();
	level.step();
	renderer.render();
	level.step();
	renderer.render();
}

