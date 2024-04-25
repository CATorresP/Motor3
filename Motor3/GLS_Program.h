#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class GLS_Program
{
private:
	GLuint programID;
	GLuint fragmentShaderID;
	GLuint vertexShaderID;
	int numAttribute;
public:
	GLS_Program();
	~GLS_Program();
	void compileShaders(const string&, const string&);
	GLuint compileShader(const string&, GLenum);
	void linkShader();
	void addAttribute(const string);
	void use();
	void unuse();
	GLuint getUniformLocation(const string& name);
};