#include "ShaderManager.h"


std::string ShaderManager::LoadShaderFile(std::string File) {

	std::ifstream fin(File.c_str());

	if (!fin)
		return "";

	std::string Line = "";
	std::string Text = "";

	while (getline(fin, Line)) {
		Text += "\n" + Line;
	}

	fin.close();

	return Text;
}


void ShaderManager::Initialize(std::string VertFile, std::string FragFile) {

	// These will hold the shader's text file data
	std::string strVShader, strFShader;

	// Make sure the user passed in a vertex and fragment shader file
	if (!VertFile.length() || !FragFile.length())
		return;

	// If any of our shader pointers are set, let's free them first
	if (VertexShaderID || FragmentShaderID || ShaderProgramID)
		Destroy();

	// Reset the last OpenGL error so we can check if down below
	GLenum ErrorCheckValue = glGetError();

	// Here we get an Id to our vertex and fragment shaders
	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Now we load the shaders from the respective files and store it in a string
	strVShader = LoadShaderFile(VertFile.c_str());
	strFShader = LoadShaderFile(FragFile.c_str());

	// Do a quick switch so we can do a double pointer below
	const char *szVShader = strVShader.c_str();
	const char *szFShader = strFShader.c_str();

	// Now this assigns the shader text file to each shader pointer
	glShaderSource(VertexShaderID, 1, &szVShader, nullptr);
	glShaderSource(FragmentShaderID, 1, &szFShader, nullptr);

	// Now we actually compile the shader code
	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	// Next we create a program object to represent our shaders
	ShaderProgramID = glCreateProgram();

	// We attach each shader we just loaded to our program object
	glAttachShader(ShaderProgramID, VertexShaderID);
	glAttachShader(ShaderProgramID, FragmentShaderID);

	// Our last init function is to link our program object with OpenGL
	glLinkProgram(ShaderProgramID);

	// Now check to see if any errors happened in this function
	ErrorCheckValue = glGetError();

	// If there was an error found, print it to the screen and close the OpenGL window.
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		// Use gluErrorString(ErrorCheckValue) if you want to get the string value of the
		// error, but I removed this since Mac OSX 10.9 (Mavericks) deprecated this function.
		fprintf(stderr, "ERROR: Could not create the shader program with error Id: %d\n", ErrorCheckValue);
		exit(-1);
	}
}


GLint ShaderManager::GetVariable(std::string strV) {

	if (!ShaderProgramID)
		return -1;

	return glGetUniformLocation(ShaderProgramID, strV.c_str());
}


void ShaderManager::Destroy() {
	
	if (VertexShaderID) {
		glDetachShader(ShaderProgramID, VertexShaderID);
		glDeleteShader(VertexShaderID);
		VertexShaderID = 0;
	}

	if (FragmentShaderID) {
		glDetachShader(ShaderProgramID, FragmentShaderID);
		glDeleteShader(FragmentShaderID);
		FragmentShaderID = 0;
	}

	if (ShaderProgramID) {
		glDeleteProgram(ShaderProgramID);
		ShaderProgramID = 0;
	}
}