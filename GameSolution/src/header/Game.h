#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"
#include "Buffer.h"
#include "BufferArray.h"
#include "Sprite.h"
#include "Charakter.h"
#include "Debugger.h"

class Game {
private:
	Shader* shader;
	Buffer* vertexBuffer, * indexBuffer;
	Sprite* charakterSprite;
	Charakter* charakter;

	GLFWwindow* window;
	int windowHeight;
	int windowWidth;

	void init();

public:

	Game();
	~Game();
	void process();
};