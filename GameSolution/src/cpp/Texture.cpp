#include "../header/Texture.h"
#include "../header/stb_image.h"

Texture::Texture(const float textureHeight, const float textureWidth, const char* name)
	: textureHeight(textureHeight), textureWidth(textureWidth)
{
	this->name = (char*)name;
}

Texture::Texture() {
	//Empty
}

Texture::~Texture() {
	//Empty
}

float Texture::getTextureHeight() const {
	return textureHeight;
}

float Texture::getTextureWidth() const {
	return textureWidth;
}

char* Texture::getName() const {
	return name;
}