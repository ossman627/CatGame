#include "../header/Texture.h"
#include "../header/stb_image.h"

Texture::Texture(const char* path, int slot) : slot(slot) {
	this->path = (char*)path;
	loadTexture(path);
}

Texture::~Texture() {
	//Empty
}

void Texture::loadTexture(const char* path) {

	GLCall(stbi_set_flip_vertically_on_load(1));
	GLCall(glGenTextures(1, &textureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
	// set the texture wrapping/filtering options (on the currently bound texture object)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	// load and generate the texture

	unsigned char* data = stbi_load(path, &textureWidth, &textureHeight, &nrChannels, 4);
	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
void Texture::bind() {
	activateTexture();
	GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
}
void Texture::unbind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::activateTexture() {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
}
int Texture::getSlot() const {
	return slot;
}

int Texture::getTextureHeight() const {
	return textureHeight;
}

int Texture::getTextureWidth() const {
	return textureWidth;
}