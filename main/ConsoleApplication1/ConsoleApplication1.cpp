#include <iostream>
#include <string>
#include "Level.h"
#include "Renderer.h"
#include "EventLoop.h"


int main(){
	std::string levelList[2] = { "l1.txt", "l2.txt" };
	for (std::string levelName : levelList) {
		Level* level = new Level(levelName);
		bool won = level->play();
		delete level;
		if (!won) {
			Level* level= new Level("GameOver.txt");
			level->play();
		}
	}
}

