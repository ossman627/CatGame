#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>


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

	//sicher gehen das es funktioniert hier der Code der später in Klassen aufgeteilt wird
	float rectAngle[2 * 4] = {
		0.5f, 0.5f,			//oben rechts
		0.5f, -0.5f,		//unten rechts
		-0.5f, -0.5f,		//unten links
		-0.5f, 0.5f			//oben Links
	};

	unsigned int indexArray[2 * 3] = {
		0, 1, 2,
		0, 2, 3
	};
	unsigned int VB, IB, VA;

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(float), rectAngle, GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(float), indexArray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	/* Make the window's context current */


	unsigned int shaderProgram = createShader("#defaultVertexShader", "#defaultFragmentShader");
	glUseProgram(shaderProgram);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}