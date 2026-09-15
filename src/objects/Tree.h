#pragma once
#include "objects/DrawableObject.h"
#include "rendering/VAO.h"

class Tree : public DrawableObject
{
public:
	Tree() = default;
	void draw(VAO& VAO) override;
};