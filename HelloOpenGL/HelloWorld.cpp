#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "ShaderLoader.h"

using namespace std;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f
	};
	
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vertexShader = ShaderLoader::LoadShader("basic.vert", GL_VERTEX_SHADER);
	GLuint fragmentShader = ShaderLoader::LoadShader("basic.frag", GL_FRAGMENT_SHADER);

	GLuint program = ShaderLoader::LinkProgram(vertexShader, fragmentShader, NULL);

	//glBindFragDataLocation(program, 0, "outColor");
	glUseProgram(program);

	GLint posAttrib = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	
	GLint colorAttrib = glGetAttribLocation(program, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

	GLint uniColor = glGetUniformLocation(program, "triangleColor");

	unsigned long int time = 0;
	while (!glfwWindowShouldClose(window))
	{
		int ratio = time % 1000;
		glUniform3f(uniColor, sin((float)ratio/1000.0f * 22 / 7), 0.0f, 0.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		time++;
	}

	glfwTerminate();
}