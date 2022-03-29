#include "../header/Game.h"

Game::Game() {
	shader = new Shader("Resources/Shader.shader", "#defaultVertexShader", "#defaultFragmentShader");
	charakterSprite = new Sprite("Resources/Bilder/KatzeAnimation.png", 0);
	charakter = new Charakter(*charakterSprite);

	vertexBuffer = new Buffer(GL_ARRAY_BUFFER);
	indexBuffer = new Buffer(GL_ELEMENT_ARRAY_BUFFER);

	windowWidth = 1024;
	windowHeight = 768;
}

Game::~Game() {
	delete shader;
	delete charakterSprite;
	delete charakter;

	delete vertexBuffer;
	delete indexBuffer;
}