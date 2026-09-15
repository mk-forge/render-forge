#pragma once
#include "objects/DrawableObject.h"
#include "rendering/VAO.h"

class Sphere : public DrawableObject
{
public:
	Sphere() = default;
	void draw(VAO& VAO) override;
};