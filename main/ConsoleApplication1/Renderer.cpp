#include "Renderer.h"
#include "Level.h"
#include <iostream>
#include <windows.h>

Renderer::Renderer(Level* level) {
	this->level = level;
};
void Renderer::render() {
	system("cls");
	std::list<GameObject*>::iterator it = level->objectList.begin();
	GameObject* objToDraw;
	int isLast = 0;
	for (int y = 0; y < level->height; y++) {
		for (int x = 0; x < level->width+1; x++) {
			objToDraw = *it;						// Loads last object to have a comparison for z-index
			int spaceNotEmpty = 0;					
			while ((*it)->x == x && (*it)->y == y) {
				spaceNotEmpty = 1;					// At this point we know that space is not empty, so the previously loaded object can be drawn here
				if ((*it)->zIndex > objToDraw->zIndex) { //compare z-indices
					objToDraw = *it;
				}
				if (it != level->objectList.end()) {// If it's not the last element in list, continue
					it++;
				}
				else {
					isLast = 1;						// If it's the last one, exit the loop
					break;								
				}
			}
			if (isLast) { break; }					// break the first for loop
			if (spaceNotEmpty) { std::cout << objToDraw->sprite; }	// If object belong here, print its spaite
			else { std::cout << ' '; }				// If the loaded object does not belong to that space, whitespace character will be printed instead		
		}
		if (isLast) { break; }						// break the second for loop
		std::cout << '\n';
		
	}

}

