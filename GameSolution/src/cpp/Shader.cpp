#include "../header/Shader.h"

Shader::Shader(const char* path, const char* vertexShaderType, const char* fragmentShaderType) {
	this->path = (char*)path;

	shaderID = createShader(vertexShaderType, fragmentShaderType);
}

Shader::~Shader() {

}

unsigned int Shader::createShader(const char* vertexShaderType, const char* fragmentShaderType) {

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

void Shader::setUniform2f(const char* uniform, float v1, float v2) {
	glUniform2f(glGetUniformLocation(shaderID, uniform), v1, v2);
}

void Shader::setUniform1i(const char* uniform, int v1) {
	glUniform1i(glGetUniformLocation(shaderID, uniform), v1);
}

void Shader::activateTexture(int v1) {
	glActiveTexture(v1);
}

void Shader::bind() {
	glUseProgram(shaderID);
}

void Shader::unbind() {
	glUseProgram(0);
}


//--------------------------private funktionen----------------------------------
unsigned int Shader::compileShader(unsigned int type, const char* typeOfSource) {
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

std::string Shader::findAndGetShaderSource(const char* shaderType) {
	std::string source = "";
	std::string line;
	bool finish = false;
	std::fstream shaderFile(path, std::ifstream::in);

	while (!shaderFile.eof() && finish == false) {
		std::getline(shaderFile, line);
		if (std::strcmp(line.c_str(), shaderType) == 0) {
			source = getShaderSource(shaderFile);
			finish = true;
		}
	}

	return source;
}

std::string Shader::getShaderSource(std::fstream& file) {
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