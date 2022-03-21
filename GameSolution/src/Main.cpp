#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include "header/stb_image.h"

#include "header/Shader.h"
#include "header/Buffer.h"
#include "header/BufferArray.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
     x;\
     ASSERT(GLLogCall(#x, __FILE__, __LINE__))



static unsigned int texturBuffer;
static int spriteHeight, spriteWidth, nrChannels;



static void loadSprite() {
	stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &texturBuffer);
	glBindTexture(GL_TEXTURE_2D, texturBuffer);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture

	unsigned char* data = stbi_load("Resources/Bilder/KatzeAnimation.png", &spriteWidth, &spriteHeight, &nrChannels, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spriteWidth, spriteHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

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
	loadSprite();
	float height = 63.0f, width = 63.0f;
	//sicher gehen das es funktioniert hier der Code der später in Klassen aufgeteilt wird
	float rectAngle[4 * 4] = {
		0.2f, 0.2f,	  width / spriteWidth, 1.0f,//oben rechts
		0.2f, -0.2f,  width / spriteWidth, (spriteHeight - height) / spriteHeight,//unten rechts
		-0.2f, -0.2f, 0.0f, (spriteHeight - height) / spriteHeight,//unten links
		-0.2f, 0.2f,  0.0f, 1.0f//oben Links
	};

	unsigned int indexArray[2 * 3] = {
		0, 1, 2,
		0, 2, 3
	};

	Buffer vertexBuffer(GL_ARRAY_BUFFER);
	vertexBuffer.bind();
	vertexBuffer.setBufferSizeF(16);
	vertexBuffer.addDataF(16, rectAngle);

	Buffer indexBuffer(GL_ELEMENT_ARRAY_BUFFER);
	indexBuffer.bind();
	indexBuffer.setBufferSizeUI(6);
	indexBuffer.addDataUI(6, indexArray);


	BufferArray bufferArray;
	bufferArray.addLayoutF(0, 2, 4, 0);
	bufferArray.addLayoutF(1, 2, 4, 2);
	bufferArray.aktivateAllLayouts();





	Shader shader("Resources/Shader.shader", "#defaultVertexShader", "#defaultFragmentShader");
	shader.bind();
	shader.setUniform1i("ourTexture", 0);
	shader.activateTexture(GL_TEXTURE0);
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
		//glUniform2f(glGetUniformLocation(shaderProgram, "additional"), render.x, (i % 8) * render.y);
		if (glfwGetTime() > time) {
			shader.setUniform2f("shift", (((i % 5)) * 63.0f + 1.0f) / spriteWidth, 0.0f);
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