#include "../header/Sprite.h"
#include "../header/stb_image.h"

Sprite::Sprite(const char* path, int slot) : slot(slot) {
	this->path = (char*)path;
	loadSprite(path);
}

Sprite::Sprite() {
	//empty
}

Sprite::~Sprite() {
	//Empty
}

void Sprite::loadSprite(const char* path) {

	GLCall(stbi_set_flip_vertically_on_load(1));
	GLCall(glGenTextures(1, &SpriteID));
	GLCall(glBindTexture(GL_TEXTURE_2D, SpriteID));
	// set the texture wrapping/filtering options (on the currently bound texture object)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// load and generate the texture

	unsigned char* data = stbi_load(path, &SpriteWidth, &SpriteHeight, &nrChannels, 4);
	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SpriteWidth, SpriteHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
void Sprite::bind() {
	activateSprite();
	GLCall(glBindTexture(GL_TEXTURE_2D, SpriteID));
}
void Sprite::unbind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Sprite::activateSprite() {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
}
int Sprite::getSlot() const {
	return slot;
}

int Sprite::getSpriteHeight() const {
	return SpriteHeight;
}

int Sprite::getSpriteWidth() const {
	return SpriteWidth;
}

char* Sprite::getPath() const {
	return path;
}