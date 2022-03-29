#include "../header/Charakter.h"



Charakter::Charakter() {

}

Charakter::Charakter(Sprite& sprite) {
	texture = new Texture(63.0f, 63.0f, "Katze");
	spriteOfCat = &sprite;
	initData();						//Daten füllen
}
Charakter::~Charakter() {
	delete texture;
	spriteOfCat = nullptr;
}

float* Charakter::getData() {
	return data;
}

const unsigned int* Charakter::getIndexData() const {
	return indexData;
}

int Charakter::getDataSize() const {
	return dataLength;
}

int Charakter::getIndexDataSize() const {
	return indexDataLength;
}


void Charakter::render() {

}

//private funktionen
void Charakter::initData() {

	//Varialen um das Füllen der Daten Dynamisch zu machen
	float x = -0.2f;
	float y = 0.2f;
	float size = 0.4f;

	const int coordSamples = 4;
	Coordinates coordinates[coordSamples];					//Liste das die Coordinaten strukturiert speichert

	//obenlinks
	coordinates[0].position = { x, y };
	coordinates[0].textCoords = { 0.0, 1.0f };

	//unten links
	coordinates[1].position = { x, y - size };
	coordinates[1].textCoords = { 0.0f, (spriteOfCat->getSpriteHeight() - texture->getTextureHeight()) / spriteOfCat->getSpriteHeight() };

	//obenrechts
	coordinates[2].position = { x + size, y };
	coordinates[2].textCoords = { texture->getTextureWidth() / spriteOfCat->getSpriteWidth(), 1.0f };

	//untenrechts
	coordinates[3].position = { x + size, y - size };
	coordinates[3].textCoords = { texture->getTextureWidth() / spriteOfCat->getSpriteWidth(),
								(spriteOfCat->getSpriteHeight() - texture->getTextureHeight()) / spriteOfCat->getSpriteHeight() };

	//Daten Füllen
	for (int i = 0; i < dataLength / coordSamples; i++) {
		data[i * coordSamples + 0] = coordinates[i].position.x;
		data[i * coordSamples + 1] = coordinates[i].position.y;
		data[i * coordSamples + 2] = coordinates[i].textCoords.x;
		data[i * coordSamples + 3] = coordinates[i].textCoords.y;
	}
}

