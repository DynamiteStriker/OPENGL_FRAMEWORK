#ifndef Application_H
#define Application_H


#include "Shader.h"

#include "CSceneBase.h"
#include "Controls.h"
#include "timer.h"
#include "MeshBuilder.h"

class Application
{
private:
	Application();

public:
	static Application* GetInstance();
	~Application();

	bool Start();

	bool Run();

	bool Exit();



protected:

	static Application* instance;

	//timer for the windows application
	StopWatch timer;
	const unsigned char FPS = 60; // FPS of this game
	const unsigned int frameTime = 1000 / FPS; // time for each frame



	//opengl window
	GLFWwindow* window;
	unsigned int window_width;
	unsigned int window_height;

	//shader
	unsigned int shaderProgramID;

	//OBEJCTS
	CSceneBase* testScene;
};


#endif
