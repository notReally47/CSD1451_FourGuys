#include "VectorMath.h"

namespace VectorMath {
	Vector vecSubtract(Vector a, Vector b) {
		Vector vec{ a.x - b.x, a.y - b.y };
		return vec;
	}

	f32 vecDotProduct(Vector a, Vector b) {
		return ((a.x * b.x) + (a.y * b.y));
	}
}