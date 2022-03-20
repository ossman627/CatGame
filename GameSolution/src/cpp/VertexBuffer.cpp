#include "../header/VertexBuffer.h"

VertexBuffer::VertexBuffer() :offset(0), bufferSize(0) {
	GLCall(glGenBuffers(1, &bufferID));

}

VertexBuffer::~VertexBuffer() {
	//Empty
}

void VertexBuffer::setBufferSize(unsigned int size) {
	bufferSize = size * sizeof(float);
	GLCall(glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, GL_STATIC_DRAW));

}

void VertexBuffer::addData(unsigned int dataLength, float* data) {
	if ((offset + dataLength * sizeof(float)) <= bufferSize) {
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, dataLength * sizeof(float), data));
		offset = offset + dataLength * sizeof(float);
	}
	else {
		LOG("Buffer zu klein");
	}
}

void VertexBuffer::bind() {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
}

void VertexBuffer::unbind() {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}