#pragma once
#include "Texture.h"
#include "Sprite.h"
#include "Debugger.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Charakter {
private:
	Texture cat;								//Default Charakter als Texture
	Sprite spriteOfCat;							//Sprite muss übergeben werden, um auf deren Variablen zuzugreifen
	float velocity;								//Geschwindigkeit der Katze

	static const int dataLength = 16;			//Datengröße
	static const int indexDataLength = 6;		//Index datengröße

	float data[dataLength];						//Daten zum rendern

	//wird jetzt schon gefüllt, da es sich nicht
	//ändert oder angepasst werden muss
	const unsigned int indexData[indexDataLength] = { 0, 1,2,
													1, 2, 3 };

	void initData();							//Daten erzeugen und in der liste speichern

public:
	Charakter(Sprite sprite);
	~Charakter();

	float* getData();											//Daten zurück geben
	const unsigned int* getIndexData() const;					//Daten von den Indices

	int getDataSize() const;
	int getIndexDataSize() const;
	void render();




};