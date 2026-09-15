#include "Callback.h"

void Callback::error_callback(int /*error*/, const char* description) {
	fputs(description, stderr);
}

void Callback::key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}