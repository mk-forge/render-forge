#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include <GLFW/glfw3.h>
#include "rendering/ShaderProgram.h"
#include "patterns/Subject.h"

class ShaderProgram;

class Camera : public Subject
{
private:
	glm::vec3 eye, target, up;
	float alpha, phi, lastX, lastY;
	glm::mat4 V, P;
	double x, y;
	bool firstClick;

public:
	Camera();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix() const;
	void setProjectionMatrix(const glm::mat4& projectionMatrix);
	glm::vec3 getPosition() const;
	glm::vec3 getFront() const;

	void move(GLFWwindow* window, float deltaTime);
	void lookAround(GLFWwindow* window, float deltaTime);
	void look(GLFWwindow* window, float deltaTime);
	void update();
	void changePosition(glm::vec3 position);
};