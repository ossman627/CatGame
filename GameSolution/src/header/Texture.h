#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debugger.h"
#include <glm/glm.hpp>
#include <iostream>


struct Coordinates {
	glm::vec2 position;
	glm::vec2 textCoords;
};


class Texture {
private:

	float textureHeight;			//Höhe der ganzen Texture
	float textureWidth;				//Breite der ganzen Texture
	char* name;


public:
	Texture(const float textureHeight, const float textureWidth, const char* name);
	Texture();
	~Texture();
	Texture& operator=(Texture& other);
	float getTextureHeight() const;
	float getTextureWidth() const;

	char* getName() const;

};