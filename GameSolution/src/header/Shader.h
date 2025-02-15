#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <string>

class Shader {
private:
	unsigned int shaderID;
	char* path;				//Pfad zum Shadercode

	//Gibt den den Code des Shaders zur�ck
	std::string getShaderSource(std::fstream& file);

	//Findet den Code des Shaders in der Datei und gibt den Code zur�ck
	std::string findAndGetShaderSource(const char* shaderType);

	//Compiliert den Shadercode
	unsigned int compileShader(unsigned int type, const char* typeOfSource);

	//Erstellt einen Shader
	unsigned int createShader(const char* vertexShaderType, const char* fragmentShaderType);


public:
	Shader(const char* path, const char* vertexShaderType, const char* fragmentShaderType);
	~Shader();

	void setUniform2f(const char* uniform, float v1, float v2);
	void setUniform1i(const char* uniform, int v1);
	void activateTexture(int v1);

	void bind();
	void unbind();
};
