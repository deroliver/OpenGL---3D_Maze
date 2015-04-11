#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include <string>
#include <fstream>
#include "GL\glew.h"


class ShaderManager {

public:

	ShaderManager() {}
	~ShaderManager() { Destroy(); }

	// Loads text file for shader and returns string
	std::string LoadShaderFile(std::string File);

	// Loads vertex/fragment shader from text file
	void Initialize(std::string VertexFile, std::string FragmentFile);

	// Returns ID for a variable in the shader
	GLint GetVariable(std::string Variable);

	// Functions to set an integer
	void SetInt(GLint id, int newvalue)											{ glUniform1i(id, newvalue);		}
	void SetFloat(GLint id, GLfloat newvalue)									{ glUniform1f(id, newvalue);		}
	void SetFloat2(GLint id, GLfloat v0, GLfloat v1)							{ glUniform2f(id, v0, v1);			}
	void SetFloat3(GLint id, GLfloat v0, GLfloat v1, GLfloat v2)				{ glUniform3f(id, v0, v1, v2);		}
	void SetFloat4(GLint id, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)	{ glUniform4f(id, v0, v1, v2, v3);	}

	// Allows us to pass a 4x4 matrix (array of 16 floats) to a shader using the ID receieved from GetVariable()
	void SetMatrix4(GLint id, GLsizei count, GLboolean transpose, const GLfloat *value) {

		glUniformMatrix4fv(id, count, transpose, value);
	}


	void TurnOn()	{ glUseProgram(ShaderProgramID); }
	void TurnOff()	{ glUseProgram(0); }

	void Destroy();

private:

	// Stores vertex shader information
	GLuint VertexShaderID;

	// Stores fragment shader information
	GLuint FragmentShaderID;

	// Stores program information for all shaders
	GLuint ShaderProgramID;	
};

#endif