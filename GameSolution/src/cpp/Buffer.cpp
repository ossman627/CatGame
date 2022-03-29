#include "../header/Buffer.h"

Buffer::Buffer() {

}

Buffer::Buffer(unsigned int bufferType) :offset(0), bufferSize(0) {
	GLCall(glGenBuffers(1, &bufferID));
	this->bufferType = bufferType;

}

Buffer::~Buffer() {
	//Empty
}

void Buffer::setBufferSizeF(unsigned int size) {
	bufferSize = size * sizeof(float);
	GLCall(glBufferData(bufferType, bufferSize, NULL, GL_STATIC_DRAW));

}

void Buffer::setBufferSizeUI(unsigned int size) {
	bufferSize = size * sizeof(unsigned int);
	GLCall(glBufferData(bufferType, bufferSize, NULL, GL_STATIC_DRAW));

}

void Buffer::addDataF(unsigned int dataLength, float* data) {
	if ((offset + dataLength * sizeof(float)) <= bufferSize) {
		GLCall(glBufferSubData(bufferType, offset, dataLength * sizeof(float), data));
		offset = offset + dataLength * sizeof(float);
	}
	else {
		LOG("Buffer zu klein");
	}
}

void Buffer::addDataUI(unsigned int dataLength, unsigned int* data) {
	if ((offset + dataLength * sizeof(unsigned int)) <= bufferSize) {
		GLCall(glBufferSubData(bufferType, offset, dataLength * sizeof(unsigned int), data));
		offset = offset + dataLength * sizeof(unsigned int);
	}
	else {
		LOG("Buffer zu klein");
	}
}

void Buffer::bind() {
	GLCall(glBindBuffer(bufferType, bufferID));
}

void Buffer::unbind() {
	GLCall(glBindBuffer(bufferType, 0));
}