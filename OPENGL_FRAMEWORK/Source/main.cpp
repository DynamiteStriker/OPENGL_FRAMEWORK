// OPENGL_FRAMEWORK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Application.h"
int main()
{
    Application* app = Application::GetInstance();
    app->Start();
    app->Run();
    app->Exit();

    delete app;
    app = nullptr;
}
