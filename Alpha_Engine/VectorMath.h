#pragma once
#include "pch.h"

namespace VectorMath {
	using namespace GameObjects;
	AEVec2 vecSubtract(AEVec2 a, AEVec2 b);
	f32 vecDotProduct(AEVec2 a, AEVec2 b);
	f32 GetLength(AEVec2 a);
	AEVec2 vecNormalize(AEVec2 a);
	AEVec2 vecAdd(AEVec2 a, AEVec2 b);
	AEVec2 vecScale(AEVec2 a, f32 scale);
}

