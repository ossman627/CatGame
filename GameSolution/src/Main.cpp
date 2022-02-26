#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>

/*
template<typename T>
static void LOG(T value) {
	std::cout << value << std::endl;
}

*/
/*
static std::string getShaderSource(const char* shader) {
	std::string source;
	std::fstream shaderFile("Resources/Shader.shader", std::ifstream::in);
	LOG(shaderFile.is_open());

	return source;
}
*/

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

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//std::string source = getShaderSource("blub");
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}