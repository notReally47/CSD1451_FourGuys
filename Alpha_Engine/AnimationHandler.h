#pragma once
#include "pch.h"

namespace AnimationHandler {
	using namespace GameObjects;
	void setTextureOffsetY(Character&);
	void setTextureOffsetX(Character&);
	bool checkDirection(Character, int, int);
	void AnimateCharacter(Character&);
}