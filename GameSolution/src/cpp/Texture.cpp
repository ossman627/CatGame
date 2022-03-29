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

Texture& Texture::operator=(Texture& other) {

	textureHeight = other.textureHeight;
	textureWidth = other.textureWidth;
	name = other.name;

	return *this;

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