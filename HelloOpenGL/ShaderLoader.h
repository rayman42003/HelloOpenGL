#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include "GL/glew.h"
#include <string>

class ShaderLoader {
public:
	static std::string ReadFile(const char* filePath);

	static GLuint LoadShader(const char* path, GLenum type);
	static bool ShaderCompiled(GLuint shader);
	static std::string GetShaderCompilerMessage(GLuint shader);

	static GLuint LinkProgram(GLuint vertShader, GLuint fragShader, GLuint geomShader);
	static bool ProgramCompiled(GLuint program);
	static std::string GetProgramLinkerMessage(GLuint program);
};

#endif