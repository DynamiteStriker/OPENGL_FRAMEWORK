#include "Application.h"

Application* Application::instance = nullptr;


Application::Application() :
	window_width(800),
	window_height(600),
	window(nullptr),
	shaderProgramID(0)
{
	//print out in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle, 11);
	std::cout << " Application ";
	SetConsoleTextAttribute(Handle, 10);
	std::cout << "Created" << std::endl;
	SetConsoleTextAttribute(Handle, 7);
}

Application* Application::GetInstance()
{
	//check if there is an Application opened
	if (instance == nullptr)
		instance = new Application();

	return instance;

}

Application::~Application()
{
	window = nullptr;

	//print out in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle, 11);
	std::cout << " Application ";
	SetConsoleTextAttribute(Handle, 12);
	std::cout << "Deleted" << std::endl;
	SetConsoleTextAttribute(Handle, 7);
}

bool Application::Start()
{
	//print out in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle, 11);
	std::cout << " Application ";
	SetConsoleTextAttribute(Handle, 14);
	std::cout << "Starting!" << std::endl;
	SetConsoleTextAttribute(Handle, 7);


	//Initialize GLFW
	if (!glfwInit())
	{
		SetConsoleTextAttribute(Handle, 12);
		std::cout << " FAILED TO INIT GLFW" << std::endl;
		SetConsoleTextAttribute(Handle, 7);
		exit(EXIT_FAILURE);
	}





	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 



	//Create a window and create its OpenGL context
	window_width = 800;
	window_height = 600;
	window = glfwCreateWindow(window_width, window_height, "Physics", NULL, NULL);
	
	//If the window couldn't be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(window);

	//initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		SetConsoleTextAttribute(Handle, 12);
		std::cout << " FAILED TO INIT GLEW" << std::endl;
		SetConsoleTextAttribute(Handle, 7);
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//print out GL version
	std::cout << glGetString(GL_VERSION) << std::endl;
	//set the control Events to be on the created window
	Controls::SetWindow(window);

	//init Shaders
	shaderProgramID = LoadShaders("Shader//test.vertexshader", "Shader//test.fragmentshader"); // load shader
	glUseProgram(shaderProgramID);


	//INIT OBJECTS HERE
	testScene = new CSceneBase("test Scen");
	testScene->Init();
	return true;
}

bool Application::Run()
{
	//print out in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle, 11);
	std::cout << " Application ";
	SetConsoleTextAttribute(Handle, 14);
	std::cout << "Running!" << std::endl;
	SetConsoleTextAttribute(Handle, 7);


	//Init Here
	timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	float deltaTime = 0;

	//Main Loop
	while (!glfwWindowShouldClose(window) && !Controls::IsKeyPressed(VK_ESCAPE))
	{
		deltaTime = timer.getElapsedTime();
		//Update here
		 testScene->Update(deltaTime);


		 //Render here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		testScene->Render();

		
		//Swap buffers
		glfwSwapBuffers(window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	return true;
}

bool Application::Exit()
{

	//print out in the console
	auto Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Handle, 11);
	std::cout << " Application ";
	SetConsoleTextAttribute(Handle, 14);
	std::cout << "Exiting!" << std::endl;
	SetConsoleTextAttribute(Handle, 7);
	
	delete testScene->objectMesh;
	delete testScene;

	//delete Shader Programme
	glDeleteProgram(shaderProgramID);
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(window);
	//Finalize and clean up GLFW
	glfwTerminate();
	return true;
}

