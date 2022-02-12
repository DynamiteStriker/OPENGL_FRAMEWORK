#include "CShader.h"

CShader::CShader(const std::string& vertexfilepath, const std::string& fragmentfilepath)
	:
	m_vFilePath(vertexfilepath),
	m_fFilePath(fragmentfilepath),
	m_RendererID(0)
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	LoadShaders();
}

CShader::~CShader()
{
	glDeleteProgram(m_RendererID);
}

bool CShader::LoadShaders()
{

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode = ParseShader(m_vFilePath);

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode = ParseShader(m_fFilePath);


	//Compile Vertex shader
	CompileShader(VertexShaderID, VertexShaderCode);

	//Compile Fragment shader
	CompileShader(FragmentShaderID, FragmentShaderCode);

	// Link the program
	SetConsoleTextAttribute(Handle, 14);
	std::cout << " LINKING";
	std::cout << " shader program" << std::endl;
	SetConsoleTextAttribute(Handle, 7);
	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, VertexShaderID);
	glAttachShader(m_RendererID, FragmentShaderID);
	glLinkProgram(m_RendererID);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Check the program
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &Result);
	if (!Result)
	{
		glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(m_RendererID, InfoLogLength, NULL, &ProgramErrorMessage[0]);

			SetConsoleTextAttribute(Handle, 12);
			std::cout << " FAILED TO LINK SHADER: " << std::endl;
			SetConsoleTextAttribute(Handle, 7);
			printf("%s\n", &ProgramErrorMessage[0]);
			return false;
		}
	}
	else
	{
		SetConsoleTextAttribute(Handle, 10);
		std::cout << " SUCCESS! ";
		SetConsoleTextAttribute(Handle, 7);
		std::cout << " in linking Shader" << std::endl;
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return true;
}

std::string CShader::ParseShader(const std::string& name)
{
	std::string result;
	std::ifstream VertexShaderStream(name, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			result += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		SetConsoleTextAttribute(Handle, 12);
		printf(" Impossible to open %s. Are you in the right directory ?\n", name.c_str());
		SetConsoleTextAttribute(Handle, 7);
		return "NOT PARSED";
	}
	return result;
}

bool CShader::CompileShader(GLuint shaderTypeID, const std::string shaderTypeCode)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	SetConsoleTextAttribute(Handle, 14);
	std::cout << " COMPILING shader : ";
	SetConsoleTextAttribute(Handle, 7);
	printf("%s\n", m_vFilePath.c_str());
	char const* SourcePointer = shaderTypeCode.c_str();
	glShaderSource(shaderTypeID, 1, &SourcePointer, NULL);
	glCompileShader(shaderTypeID);

	// Check Vertex Shader
	glGetShaderiv(shaderTypeID, GL_COMPILE_STATUS, &Result);
	if (!Result)
	{
		glGetShaderiv(shaderTypeID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(shaderTypeID, InfoLogLength, NULL, &ShaderErrorMessage[0]);

			SetConsoleTextAttribute(Handle, 12);
			std::cout << " FAILED TO COMPILE VERTEX SHADER: " << std::endl;
			SetConsoleTextAttribute(Handle, 7);
			printf("%s\n", &ShaderErrorMessage[0]);
		}
	}
	else
	{
		SetConsoleTextAttribute(Handle, 10);
		std::cout << " SUCCESS! ";
		SetConsoleTextAttribute(Handle, 7);
		printf("in compiling shader : %s\n", m_vFilePath.c_str());
	}

	return Result;
}

void CShader::Bind(int id) const
{
	if (id == -1000)
		glUseProgram(m_RendererID);
	else
		glUseProgram(id);
}

void CShader::UnBind() const
{
	glUseProgram(0);

}

void CShader::SetUniform4f(const std::string& name, Eigen::Vector4f v)
{
	glUniform4f(GetUniformLocation(name), v[0], v[1], v[2], v[3]);
}

GLint CShader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) == m_UniformLocationCache.end())
		m_UniformLocationCache[name] = glGetUniformLocation(m_RendererID, name.c_str());
	return m_UniformLocationCache[name];
}


