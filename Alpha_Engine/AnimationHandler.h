#pragma once
#include "pch.h"

namespace AnimationHandler {
	using namespace GameObjects;
	void setTextureOffsetY(ObjectInst&, AEVec2&);
	void setTextureOffsetX(ObjectInst&, int&);
	bool checkDirection(AEVec2&, int, int);
	void AnimateCharacter(Character&);
}