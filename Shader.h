#pragma once
#include <vector>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader {
public:
	GLint ProgramID;
	Shader();
	~Shader();
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void setMat4x3(const std::string &name, const glm::mat4x3 &mat);
};
