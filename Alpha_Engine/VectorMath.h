#pragma once
#include "pch.h"

namespace VectorMath {
	using namespace GameObjects;
	/*SAT COLLISION CHECK*/
	f32 GetLength(Vector vec);
	Vector GetNormalized(Vector vec);
	f32 DotProduct(Vector vec);
	Vector ProjectOnAxis(Object obj, Vector vec);
	bool Overlapping(Vector vecA, Vector vecB);
	f32 OverlapLen(Vector vecA, Vector vecB);
	Vertices GetVertices(const Vertices vertices);
	Vector GetPerpendicularAxis(Vertices vertices, size_t index);
}

