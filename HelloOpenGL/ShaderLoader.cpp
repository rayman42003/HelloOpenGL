#include "ShaderLoader.h"

using namespace std;

#include <fstream>

string ShaderLoader::ReadFile(const char* filePath)
{
	string content;
	ifstream fileStream(filePath);

	if (!fileStream.is_open())
		return "";

	string line;
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint ShaderLoader::LoadShader(const char* path, GLenum type) 
{ 
	GLuint shader = glCreateShader(type);

	string shaderString = ReadFile(path);
	const char* shaderSource = shaderString.c_str();

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	return shader;
}

bool ShaderLoader::ShaderCompiled(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	return status == GL_TRUE;
}

string ShaderLoader::GetShaderCompilerMessage(GLuint shader)
{
	char buffer[512];
	glGetShaderInfoLog(shader, 512, NULL, buffer);
	return buffer;
}

GLuint ShaderLoader::LinkProgram(GLuint vertShader, GLuint fragShader, GLuint geomShader)
{
	GLuint program = glCreateProgram();
	//Required
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	//Optional
	if (geomShader)
		glAttachShader(program, geomShader);

	glLinkProgram(program);
	return program;
}

bool ShaderLoader::ProgramCompiled(GLuint program)
{
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	return status == GL_TRUE;
}

string ShaderLoader::GetProgramLinkerMessage(GLuint program)
{
	char buffer[512];
	glGetProgramInfoLog(program, 512, NULL, buffer);
	return buffer;
}
