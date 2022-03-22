#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debugger.h"
#include <iostream>

class Texture {
private:
	char* path;					//Pfad zur texture
	int slot;					//Slot zur Bindung der Texture
	int textureHeight;			//Höhe der ganzen Texture
	int textureWidth;			//Breite der ganzen Texture
	int nrChannels;				//?
	unsigned int textureID;		//TextureID

public:
	Texture(const char* path, int slot);
	~Texture();

	void loadTexture(const char* path);
	void bind();
	void unbind();
	void activateTexture();

	int getSlot() const;
	int getTextureHeight() const;
	int getTextureWidth() const;

};