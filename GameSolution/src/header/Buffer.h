#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debugger.h"


class Buffer {

private:
	unsigned int bufferID;
	unsigned int offset;
	unsigned int bufferSize;						//Größe des Buffers
	unsigned int bufferType;						//Type in sinne von GL_ARRAY_BUFFER oder GL_ELEMENT_ARRAY_BUFFER

public:
	Buffer();
	Buffer(unsigned int bufferType);
	~Buffer();

	//Setzt die Größe des Buffers anhand von float werten
	void setBufferSizeF(unsigned int size);

	//Übergibt dem Buffer(VertexBuffer) ein Float Array um daten zu speichern
	void addDataF(unsigned int dataLength, float* data);

	//Setz die größe des Buffers anhand eines unsigned int wertes
	void setBufferSizeUI(unsigned int size);

	//Übergibt dem Buffer(IndexBuffer) ein unsigned int Array um daten zu speichern
	void addDataUI(unsigned int dataLength, unsigned int* data);

	//Buffer wird gebunden
	void bind();

	//Buffer wird entbunden
	void unbind();
};