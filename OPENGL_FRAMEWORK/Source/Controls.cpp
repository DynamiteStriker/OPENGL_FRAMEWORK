#include "Controls.h"

GLFWwindow* Controls::window = nullptr;

bool Controls::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool Controls::IsMousePressed(unsigned short key)
{
    return glfwGetMouseButton(window, key) != 0;
}

void Controls::GetCursorPos(double* xpos, double* ypos)
{
    glfwGetCursorPos(window, xpos, ypos);
}

void Controls::SetWindow(GLFWwindow* win)
{
    window = win;
}
