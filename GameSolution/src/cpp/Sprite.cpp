#include "../header/Sprite.h"
#include "../header/stb_image.h"

Sprite::Sprite(const char* path, int slot) : slot(slot) {
	this->path = (char*)path;
	loadSprite(path);
}

Sprite::Sprite() {
	path = NULL;
}

Sprite::~Sprite() {
	//Empty
}

Sprite::Sprite(Sprite& other) {
	LOG("Sprite Kopied");
	swap(*this, other);
}

Sprite::Sprite(Sprite&& other) {
	LOG("Sprite moved");
	path = other.path;
	slot = other.slot;
	spriteHeight = other.spriteHeight;
	spriteWidth = other.spriteWidth;
	nrChannels = other.nrChannels;

	other.path = nullptr;
}



void Sprite::loadSprite(const char* path) {

	GLCall(stbi_set_flip_vertically_on_load(1));
	GLCall(glGenTextures(1, &spriteID));
	GLCall(glBindTexture(GL_TEXTURE_2D, spriteID));
	// set the texture wrapping/filtering options (on the currently bound texture object)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// load and generate the texture

	unsigned char* data = stbi_load(path, &spriteWidth, &spriteHeight, &nrChannels, 4);
	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spriteWidth, spriteHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Sprite& Sprite::operator=(Sprite& other) {

	strcpy_s(path, strlen(other.path) + 1, other.path);
	slot = other.slot;
	spriteHeight = other.spriteHeight;
	spriteWidth = other.spriteWidth;
	nrChannels = other.nrChannels;

	//Kopier auch die ID, auch wenn ID's einzigartig sind
	spriteID = other.spriteID;
	return *this;

}
void Sprite::bind() {
	activateSprite();
	GLCall(glBindTexture(GL_TEXTURE_2D, spriteID));
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
	return spriteHeight;
}

int Sprite::getSpriteWidth() const {
	return spriteWidth;
}

char* Sprite::getPath() const {
	return path;
}

//Private Methoden
void Sprite::swap(Sprite& first, Sprite& second) {
	std::swap(first.path, second.path);
	std::swap(first.slot, second.slot);
	std::swap(first.spriteHeight, second.spriteHeight);
	std::swap(first.spriteWidth, second.spriteWidth);
	std::swap(first.nrChannels, second.nrChannels);
	std::swap(first.spriteID, second.spriteID);
}