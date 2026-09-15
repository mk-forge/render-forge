#pragma once
#include "objects/DrawableObject.h"
#include "rendering/VAO.h"

class Plain : public DrawableObject
{
public:
	Plain() = default;
	void draw(VAO& VAO) override;
};