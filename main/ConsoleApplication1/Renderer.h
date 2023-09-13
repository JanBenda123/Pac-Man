#pragma once
#include "Level.h"

class Renderer {
public:
	Level* level;
	Renderer(Level* level);
	void render();
};
