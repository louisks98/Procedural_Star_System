#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader
{
public:
	unsigned int id;

	Shader(string vertexPath, string fragmentPath);

	void use();

	void setBool(const string& name, bool value) const;
	void setInt(const string& name, int value) const;
	void setFloat(const string& name, int value) const;
	void setVec4(const string& name, glm::vec4 value) const;
};
