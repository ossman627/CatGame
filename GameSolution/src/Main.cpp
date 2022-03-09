#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include "header/stb_image.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static unsigned int texturBuffer;
static int spriteHeight, spriteWidth, nrChannels;

template<typename T>
static void LOG(T value) {
	std::cout << value << std::endl;
}

static std::string getShaderSource(std::fstream& file) {
	std::string source = "";
	std::string line;

	while (true) {					//Endlos schleife, wird von break beendet
		std::getline(file, line);
		if (line == "#Ende") {
			break;
		}
		source += line + "\n";
	}
	return source;

}

static std::string findAndGetShaderSource(const char* shaderType) {
	std::string source = "";
	std::string line;
	bool finish = false;
	std::fstream shaderFile("Resources/Shader.shader", std::ifstream::in);

	while (!shaderFile.eof() && finish == false) {
		std::getline(shaderFile, line);
		if (std::strcmp(line.c_str(), shaderType) == 0) {
			source = getShaderSource(shaderFile);
			finish = true;
		}
	}

	return source;
}

static unsigned int compileShader(unsigned int type, const char* typeOfSource)
{
	unsigned int shaderId = glCreateShader(type);

	//In 2 Schritten: 1)Source in String speichern, 2) Dan in Char umwandeln.
	//findAndGetShaderSource(typeOfSource).c_str(); verursacht fehler
	std::string tempSource = (findAndGetShaderSource(typeOfSource));
	const char* source = tempSource.c_str();
	glShaderSource(shaderId, 1, &source, nullptr);
	glCompileShader(shaderId);

	//Fehler handling
	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shaderId, length, &length, message);

		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shaderId);
		return 0;
	}
	return shaderId;
}

static unsigned int createShader(const char* vertexShaderType, const char* fragmentShaderType)
{
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderType);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderType);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

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

	unsigned char* data = stbi_load("Resources/Bilder/Katze.png", &spriteWidth, &spriteHeight, &nrChannels, 4);
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
	float height = 72.0f, width = 128.0f;
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
	unsigned int VB, IB, VA;

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), rectAngle, GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(float), indexArray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	/* Make the window's context current */


	unsigned int shaderProgram = createShader("#defaultVertexShader", "#defaultFragmentShader");
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
	glActiveTexture(GL_TEXTURE0);
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
			glUniform2f(glGetUniformLocation(shaderProgram, "additional"), (i % 8) * 128.0f / spriteWidth, 0);
			i++;
			time += 0.1f;
		}


		LOG(glfwGetTime());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}