#include "VectorMath.h"
#include "pch.h"
#include <math.h>

namespace VectorMath {
	AEVec2 vecSubtract(AEVec2 a, AEVec2 b) {
		AEVec2 vec{ a.x - b.x, a.y - b.y };
		return vec;
	}

	f32 vecDotProduct(AEVec2 a, AEVec2 b) {
		return ((a.x * b.x) + (a.y * b.y));
	}

	f32 GetLength(AEVec2 a) {
		return sqrt(pow(a.x, 2) + pow(a.y, 2));
	}

	AEVec2 vecNormalize(AEVec2 a) {
		f32 len = GetLength(a);
		return AEVec2{ a.x / len, a.y / len };
	}

	AEVec2 vecAdd(AEVec2 a, AEVec2 b) {
		return AEVec2{ a.x + b.x, a.y + b.y };
	}

	AEVec2 vecScale(AEVec2 a, f32 scale) {
		return AEVec2{ a.x *= scale, a.y * scale };
	}
}