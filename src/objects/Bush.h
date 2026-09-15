#pragma once
#include "objects/DrawableObject.h"

class Bush : public DrawableObject
{
public:
	Bush() = default;
	void draw(VAO& VAO) override;
};