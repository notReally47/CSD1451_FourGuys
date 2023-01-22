#include "VectorMath.h"
#include <math.h>

namespace VectorMath {
	Vector vecSubtract(Vector a, Vector b) {
		Vector vec{ a.x - b.x, a.y - b.y };
		return vec;
	}

	f32 vecDotProduct(Vector a, Vector b) {
		return ((a.x * b.x) + (a.y * b.y));
	}

	f32 GetLength(Vector a) {
		return sqrt(pow(a.x, 2) + pow(a.y, 2));
	}

	Vector vecNormalize(Vector a) {
		f32 len = GetLength(a);
		return Vector{ a.x / len, a.y / len };
	}

	Vector vecAdd(Vector a, Vector b) {
		return Vector{ a.x + b.x, a.y + b.y };
	}

	Vector vecScale(Vector a, f32 scale) {
		return Vector{ a.x *= scale, a.y * scale };
	}
}