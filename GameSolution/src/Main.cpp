#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include "header/stb_image.h"

#include "header/Shader.h"
#include "header/Buffer.h"
#include "header/BufferArray.h"
#include "header/Texture.h"
#include "header/Sprite.h"
#include "header/Charakter.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "error" << std::endl;
	}

	float height = 63.0f, width = 63.0f;
	//sicher gehen das es funktioniert hier der Code der später in Klassen aufgeteilt wird

	Shader shader("Resources/Shader.shader", "#defaultVertexShader", "#defaultFragmentShader");
	shader.bind();

	Sprite sprite("Resources/Bilder/KatzeAnimation.png", 0);

	shader.setUniform1i("ourTexture", sprite.getSlot());

	sprite.bind();

	Charakter cat(sprite);

	unsigned int indexArray[2 * 3] = {
		0, 1, 2,
		1, 2, 3
	};

	Buffer vertexBuffer(GL_ARRAY_BUFFER);
	vertexBuffer.bind();
	vertexBuffer.setBufferSizeF(cat.getDataSize());
	vertexBuffer.addDataF(cat.getDataSize(), cat.getData());

	Buffer indexBuffer(GL_ELEMENT_ARRAY_BUFFER);
	indexBuffer.bind();
	indexBuffer.setBufferSizeUI(cat.getIndexDataSize());
	indexBuffer.addDataUI(cat.getIndexDataSize(), const_cast<unsigned int*>(cat.getIndexData()));


	BufferArray bufferArray;
	bufferArray.addLayoutF(0, 2, 4, 0);
	bufferArray.addLayoutF(1, 2, 4, 2);
	bufferArray.aktivateAllLayouts();

	/* Loop until the user closes the window */
	glm::vec2 render(0, width);
	int i = 0;
	float time = 0;
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		if (glfwGetTime() > time) {
			shader.setUniform2f("shift", (((i % 5)) * 63.0f) / 1600.0f, 0.0f);
			i++;
			time += 0.2f;
		}


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;

}