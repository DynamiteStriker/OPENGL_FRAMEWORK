#ifndef CONTROLS_H
#define CONTROLS_H

#include <windows.h>
#include <GLFW/glfw3.h>
static class Controls
{
public:
	static bool IsKeyPressed(unsigned short key);

	static bool IsMousePressed(unsigned short key);

	static void GetCursorPos(double* xpos, double* ypos);

	static void SetWindow(GLFWwindow* win);
private:
	static GLFWwindow* window;
};

#endif

