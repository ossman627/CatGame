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
	int spriteHeight;			//Höhe der ganzen Texture
	int spriteWidth;			//Breite der ganzen Texture
	int nrChannels;				//?
	unsigned int spriteID;		//TextureID

	void swap(Sprite& first, Sprite& second);

public:
	Sprite(const char* path, int slot);
	Sprite();
	~Sprite();
	Sprite(Sprite& other);
	Sprite(Sprite&& other);

	Sprite& operator=(Sprite& other);

	void loadSprite(const char* path);
	void bind();
	void unbind();
	void activateSprite();

	int getSlot() const;
	int getSpriteHeight() const;
	int getSpriteWidth() const;
	char* getPath() const;

};