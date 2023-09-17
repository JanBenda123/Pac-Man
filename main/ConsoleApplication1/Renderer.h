#pragma once

class Level;

class Renderer {
public:
	Level* level;
	Renderer(Level* level);
	void render();
};
