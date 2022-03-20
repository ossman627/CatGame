#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debugger.h"


class VertexBuffer {

private:
	unsigned int bufferID;
	unsigned int offset;
	unsigned int bufferSize;

public:
	VertexBuffer();
	~VertexBuffer();

	void addData(unsigned int dataLength, float* data);
	void setBufferSize(unsigned int size);
	void bind();
	void unbind();
};