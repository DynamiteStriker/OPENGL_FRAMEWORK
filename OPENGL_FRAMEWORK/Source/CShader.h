#ifndef _CSHADER_H
#define _CSHADER_H


#include <Eigen/Dense>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <unordered_map>

class CShader
{
private:
	HANDLE Handle;
	std::string m_vFilePath;
	std::string m_fFilePath;

	unsigned int m_RendererID;

	//cache for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	CShader(const std::string& vertexfilepath, const std::string& fragmentfilepath);
	~CShader();

	void Bind(int id = -1000) const;
	void UnBind() const;

	//SET Uniforms function
	void SetUniform4f(const std::string& name, Eigen::Vector4f v);


private:
	GLint GetUniformLocation(const std::string& name);
	bool  LoadShaders();
	std::string ParseShader(const std::string& filePath);
	bool CompileShader(GLuint shaderTypeID, const std::string shaderTypeCode);

};

#endif
