#include "Shader.h"

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		SetConsoleTextAttribute(Handle, 12);	
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		SetConsoleTextAttribute(Handle, 7);
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		SetConsoleTextAttribute(Handle, 12);
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		SetConsoleTextAttribute(Handle, 7);
	}


	GLint Result = GL_FALSE;
	int InfoLogLength;



	// Compile Vertex Shader
	SetConsoleTextAttribute(Handle, 14);
	std::cout << " COMPILING shader : ";
	SetConsoleTextAttribute(Handle, 7);
	printf("%s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	if (!Result)
	{
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);

			SetConsoleTextAttribute(Handle, 12);
			std::cout << " FAILED TO COMPILE VERTEX SHADER: " << std::endl;
			SetConsoleTextAttribute(Handle, 7);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}
	}
	else
	{
		SetConsoleTextAttribute(Handle, 10);
		std::cout << " SUCCESS! ";
		SetConsoleTextAttribute(Handle, 7);
		printf("in compiling shader : %s\n", vertex_file_path);
	}

	// Compile Fragment Shader
	SetConsoleTextAttribute(Handle, 14);
	std::cout << " COMPILING shader : ";
	SetConsoleTextAttribute(Handle, 7);
	printf("%s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	if (!Result)
	{
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);

			SetConsoleTextAttribute(Handle, 12);
			std::cout << " FAILED TO COMPILE FRAGMENT SHADER: " << std::endl;
			SetConsoleTextAttribute(Handle, 7);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}
	}
	else
	{
		SetConsoleTextAttribute(Handle, 10);
		std::cout << " SUCCESS! ";
		SetConsoleTextAttribute(Handle, 7);
		printf("in compiling shader : %s\n", fragment_file_path);
	}

	// Link the program
	SetConsoleTextAttribute(Handle, 14);
	std::cout << " LINKING";
	std::cout << " shader program" << std::endl;
	SetConsoleTextAttribute(Handle, 7);
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	if (!Result)
	{
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);

			SetConsoleTextAttribute(Handle, 12);
			std::cout << " FAILED TO LINK SHADER: " << std::endl;
			SetConsoleTextAttribute(Handle, 7);

			printf("%s\n", &ProgramErrorMessage[0]);
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

	return ProgramID;
}