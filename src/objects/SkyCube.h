#pragma once
#include "objects/DrawableObject.h"
#include "rendering/VAO.h"

class SkyCube : public DrawableObject
{
public:
	SkyCube() = default;
	void draw(VAO& VAO) override;
};