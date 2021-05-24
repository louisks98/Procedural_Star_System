#include "shader.h"
Shader::Shader(string vertexPath, string fragmentPath)
{
	string vertex_code;
	string fragment_code;
	ifstream vertex_file;
	ifstream fragment_file;
	
	// read shader files
	vertex_file.exceptions(ifstream::failbit | ifstream::badbit);
	fragment_file.exceptions(ifstream::failbit | ifstream::badbit);
	
	try
	{
		vertex_file.open(vertexPath);
		fragment_file.open(fragmentPath);

		stringstream vertex_stream;
		stringstream fragment_stream;

		vertex_stream << vertex_file.rdbuf();
		fragment_stream << fragment_file.rdbuf();

		vertex_file.close();
		fragment_file.close();

		vertex_code = vertex_stream.str();
		fragment_code = fragment_stream.str();
	}
	catch (ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vcode = vertex_code.c_str();
	const char* fcode = fragment_code.c_str();

	// compile shaders
	unsigned int vertex;
	unsigned int fragment;
	int success;
	char info_log[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vcode, nullptr);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fcode, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	};

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setBool(const string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const string& name, int value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec4(const string& name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), value.w, value.x, value.y, value.z);
}
