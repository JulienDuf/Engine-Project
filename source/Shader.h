#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Ressource.h"

class Shader : public Ressource{

private:

	GLuint vertexID;
	GLuint fragmentID;
	GLuint programID;

	std::string vertexSource;
	std::string fragmentSource;

	bool compilerShader(GLuint &shader, GLenum type, std::string &fichierSource) {

		shader = glCreateShader(type);

		if (shader == 0) {

			std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
			return false;
		}

		std::ifstream fichier(fichierSource.c_str());

		if (!fichier) {

			std::cout << "Error, the type of shader " << fichierSource << " doesn't exist" << std::endl;
			glDeleteShader(shader);

			return false;
		}

		std::string line;
		std::string sourceCode;

		while (getline(fichier, line))
			sourceCode += line + '\n';

		fichier.close();
		const GLchar* chainCodeSource = sourceCode.c_str();

		glShaderSource(shader, 1, &chainCodeSource, 0);
		glCompileShader(shader);

		GLint compilationError(0);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationError);

		if (compilationError != GL_TRUE) {

			GLint errorSize(0);
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);

			char *error = new char[errorSize + 1];

			glGetShaderInfoLog(shader, errorSize, &errorSize, error);
			error[errorSize] = '\0';

			std::cout << error << std::endl;

			delete[] error;
			glDeleteShader(shader);

			return false;
		}

		return true;
	}

	GLint getUniform(const GLchar* uniformName) {

		GLint uniform = glGetUniformLocation(programID, uniformName);
		return uniform;
	}

public:

	Shader() {

		vertexID = 0;
		fragmentID = 0;
		vertexID = 0;
	}

	Shader(const char* fragPath, const char* vertexPath) {

		fragmentSource = fragPath;
		vertexSource = vertexPath;
		programID = 0;
		fragmentID = 0;
		vertexID = 0;
		load();
	}

	bool load() {

		if (programID != 0) {
			if (glIsProgram(programID) == GL_TRUE)
				glDeleteProgram(programID);
		}

		if (fragmentID != 0) {
			if (glIsShader(fragmentID) == GL_TRUE)
				glDeleteShader(fragmentID);
		}

		if (vertexID != 0) {
			if (glIsShader(vertexID) == GL_TRUE)
				glDeleteShader(vertexID);
		}

		if (!compilerShader(fragmentID, GL_FRAGMENT_SHADER, fragmentSource))
			return false;

		if (!compilerShader(vertexID, GL_VERTEX_SHADER, vertexSource))
			return false;

		programID = glCreateProgram();

		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);

		/*glBindAttribLocation(programID, 0, "in_Vertex");
		glBindAttribLocation(programID, 1, "in_Color");
		glBindAttribLocation(programID, 2, "in_TexCoord0");*/

		glLinkProgram(programID);

		GLint linkErreur(0);
		glGetProgramiv(programID, GL_LINK_STATUS, &linkErreur);

		if (linkErreur != GL_TRUE)	{

			GLint errorSize(0);
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorSize);

			char *error = new char[errorSize + 1];
			glGetShaderInfoLog(programID, errorSize, &errorSize, error);
			error[errorSize] = '\0';

			std::cout << error << std::endl;

			delete[] error;
			glDeleteProgram(programID);

			return false;
		}

		return true;
	}

	GLuint getProgramID() {

		return programID;
	}

	GLint getAttrib(const GLchar* attribName) {

		GLint attrib = glGetAttribLocation(programID, attribName);
		if (attrib == -1)
			throw std::runtime_error(std::string("Program attribute not found: ") + attribName);

		return attrib;
	}

	void setUniformMatrix4x4(const GLchar* uniformName, GLsizei count, GLboolean transpose, GLfloat* matrix) {

		glUniformMatrix4fv(getUniform(uniformName), count, transpose, matrix);
	}

	void use() {

		GLint i = glGetAttribLocation(programID, "vertNormal");

		glUseProgram(programID);
	}

	void stopUse() {

		glUseProgram(0);
	}
};
