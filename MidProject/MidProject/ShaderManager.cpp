#include "ShaderManager.h"


// Loads a text file and returns code for shaders
std::string ShaderManager::LoadShaderFile(std::string File) {

	// Open the file passed
	std::ifstream fin(File.c_str());

	// Make sure file is open
	if (!fin)
		return "";

	std::string Line = "";
	std::string Text = "";

	// Store each line in the text file within a string object
	while (getline(fin, Line)) {
		Text += "\n" + Line;
	}

	// Close the file
	fin.close();

	// Return the text data
	return Text;
}


// Loads the vertex and fragment shader and creates them
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

	// Get an Id to our vertex and fragment shaders
	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Load the shaders from the respective files and store it in a string
	strVShader = LoadShaderFile(VertFile.c_str());
	strFShader = LoadShaderFile(FragFile.c_str());

	// Do a quick switch so we can do a double pointer below
	const char *szVShader = strVShader.c_str();
	const char *szFShader = strFShader.c_str();

	// Assigns the shader text file to each shader pointer
	glShaderSource(VertexShaderID, 1, &szVShader, nullptr);
	glShaderSource(FragmentShaderID, 1, &szFShader, nullptr);

	// Compile the shader code
	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	// Create a program object to represent our shaders
	ShaderProgramID = glCreateProgram();

	// Attach each shader we just loaded to our program object
	glAttachShader(ShaderProgramID, VertexShaderID);
	glAttachShader(ShaderProgramID, FragmentShaderID);

	// Link our program object with OpenGL
	glLinkProgram(ShaderProgramID);

	// Check to see if any errors happened in this function
	ErrorCheckValue = glGetError();

	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr, "ERROR: Could not create the shader program with error Id: %d\n", ErrorCheckValue);
		exit(-1);
	}
}


// Returns a variable ID for a shader variable
// Used when we need to pass in variabl;es into a shader
GLint ShaderManager::GetVariable(std::string strV) {

	// If we dont have an active program object - return -1
	if (!ShaderProgramID)
		return -1;

	// Returns variable ID for a variable in a shader file
	return glGetUniformLocation(ShaderProgramID, strV.c_str());
}


// Frees all of our shader data
void ShaderManager::Destroy() {
	
	// If our vertex shader pointer is valid, free it
	if (VertexShaderID) {
		glDetachShader(ShaderProgramID, VertexShaderID);
		glDeleteShader(VertexShaderID);
		VertexShaderID = 0;
	}

	// If our fragment shader pointer is valid, free it
	if (FragmentShaderID) {
		glDetachShader(ShaderProgramID, FragmentShaderID);
		glDeleteShader(FragmentShaderID);
		FragmentShaderID = 0;
	}

	// If our program object pointer is valid, free it
	if (ShaderProgramID) {
		glDeleteProgram(ShaderProgramID);
		ShaderProgramID = 0;
	}
}