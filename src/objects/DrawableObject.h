#pragma once
#include <GL/glew.h>
#include "rendering/VAO.h"

class DrawableObject
{
public:
	DrawableObject() = default;
	virtual void draw(VAO& VAO) = 0;
	virtual ~DrawableObject() = default;
};