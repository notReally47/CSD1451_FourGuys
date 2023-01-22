#pragma once
#include "pch.h"

namespace VectorMath {
	using namespace GameObjects;
	Vector vecSubtract(Vector a, Vector b);
	f32 vecDotProduct(Vector a, Vector b);
	f32 GetLength(Vector a);
	Vector vecNormalize(Vector a);
	Vector vecAdd(Vector a, Vector b);
	Vector vecScale(Vector a, f32 scale);
}

