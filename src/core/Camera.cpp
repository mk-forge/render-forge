#include "rendering/ShaderProgram.h"
#include "core/Camera.h"

Camera::Camera() {
	eye = glm::vec3(0.0f, 1.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	firstClick = true;
	alpha = 90.0f;
	phi = -90.0f;

	glm::vec3 lookDirection{};
	lookDirection.x = sin(glm::radians(alpha)) * cos(glm::radians(phi));
	lookDirection.y = cos(glm::radians(alpha));
	lookDirection.z = sin(glm::radians(alpha)) * sin(glm::radians(phi));
	target = glm::normalize(lookDirection);
}

glm::mat4 Camera::getViewMatrix() {
	V = glm::lookAt(eye, eye + target, up);
	return V;
}

glm::mat4 Camera::getProjectionMatrix() const {
	return P;
}

void Camera::setProjectionMatrix(const glm::mat4& projectionMatrix) {
	this->P = projectionMatrix;
}

glm::vec3 Camera::getPosition() const {
	return eye;
}

glm::vec3 Camera::getFront() const {
	return glm::normalize(target);
}

void Camera::move(GLFWwindow* window, float deltaTime) {
	float speed = 20.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		eye += glm::normalize(target) * speed;
		notifyAll();
	} else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		eye -= glm::normalize(target) * speed;
		notifyAll();
	} else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		eye -= glm::normalize(glm::cross(target, up)) * speed;
		notifyAll();
	} else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		eye += glm::normalize(glm::cross(target, up)) * speed;
		notifyAll();
	} else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		eye += glm::normalize(up) * speed;
		notifyAll();
	} else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		eye -= glm::normalize(up) * speed;
		notifyAll();
	}
}

void Camera::lookAround(GLFWwindow* window, float deltaTime) {
	glfwGetCursorPos(window, &x, &y);

	if (firstClick) {
		lastX = (float)x;
		lastY = (float)y;
		firstClick = false;
		return;
	}

	float sensitivity = 0.2f * deltaTime * 60.0f;
	float xoffset = ((float)x - lastX) * sensitivity;
	float yoffset = (lastY - (float)y) * sensitivity;
	lastX = (float)x;
	lastY = (float)y;

	phi += xoffset;
	alpha += yoffset;

	if (alpha > 89.0f) alpha = 89.0f;
	if (alpha < -89.0f) alpha = -89.0f;

	update();
}

void Camera::look(GLFWwindow* window, float deltaTime) {
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_RELEASE)
		lookAround(window, deltaTime);
	else
		firstClick = true;
}

void Camera::update() {
	glm::vec3 lookDirection{};
	lookDirection.x = sin(glm::radians(alpha)) * cos(glm::radians(phi));
	lookDirection.z = sin(glm::radians(alpha)) * sin(glm::radians(phi));
	lookDirection.y = cos(glm::radians(alpha));
	target = glm::normalize(lookDirection);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	notifyAll();
}

void Camera::changePosition(glm::vec3 position) {
	this->eye = position;
	notifyAll();
}