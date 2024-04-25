#include "GLS_Program.h"
#include "Error.h"

GLS_Program::GLS_Program() 
	: programID(0), vertexShaderID(0), fragmentShaderID(0), numAttribute(0)
{
}

GLS_Program::~GLS_Program()
{
}


void GLS_Program::compileShaders(
	const string& vertexShaderFilePath,
	const string& fragmentShaderFilePath
) {
	programID = glCreateProgram();
	// vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	// fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	vertexShaderID = compileShader(vertexShaderFilePath, GL_VERTEX_SHADER);
	fragmentShaderID = compileShader(fragmentShaderFilePath, GL_FRAGMENT_SHADER);
}


GLuint GLS_Program::compileShader(const string& shaderPath, GLenum shaderType)
{
	GLuint shaderId = glCreateShader(shaderType);
	string fileContent = "";
	string line = "";
	GLint isCompiled = 0;
	ifstream shaderFile(shaderPath);

	if (shaderId == 0) {
		return shaderId;
	}

	if (shaderFile.fail()) {
		fatalError("El archivo " + shaderPath + " no se encuentra disponible");
	}
	while (getline(shaderFile, line)) {
		fileContent += line + "\n";
	}
	shaderFile.close();

	const char* contents = fileContent.c_str();
	glShaderSource(shaderId, 1, &contents, nullptr);
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);
		fatalError("Shader no compilaron " + printf("%s", &(errorLog[0])));
		glDeleteShader(shaderId);
		return 0;
	}
	return shaderId;
}

void GLS_Program::linkShader()
{
	GLint isLinked = 0;
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(programID);
		fatalError("Shader no linkearon " + printf("%s", &(infoLog[0])));
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void GLS_Program::addAttribute(const string attributeName)
{
	glBindAttribLocation(
		programID,
		numAttribute++,
		attributeName.c_str()
	);
}

void GLS_Program::use()
{
	glUseProgram(programID);
	for (int i = 0; i < numAttribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLS_Program::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < numAttribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLuint GLS_Program::getUniformLocation(const string& name)
{
	GLuint location = glGetUniformLocation(programID, name.c_str());
	if (location == GL_INVALID_INDEX)
		fatalError("Variable uniform " + name + " no encontrada.");
	return location;
}
