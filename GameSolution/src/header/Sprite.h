#pragma once

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debugger.h"
#include <iostream>

class Sprite {
private:
	char* path;					//Pfad zur texture
	int slot;					//Slot zur Bindung der Texture
	int SpriteHeight;			//Höhe der ganzen Texture
	int SpriteWidth;			//Breite der ganzen Texture
	int nrChannels;				//?
	unsigned int SpriteID;		//TextureID

public:
	Sprite(const char* path, int slot);
	Sprite();
	~Sprite();

	void loadSprite(const char* path);
	void bind();
	void unbind();
	void activateSprite();

	int getSlot() const;
	int getSpriteHeight() const;
	int getSpriteWidth() const;
	char* getPath() const;

};