#pragma once
#include "pch.h"

namespace CollisionHandler {
	using namespace GameObjects;
	bool SAT_Collision(Object obj1, Object obj2, f32& depth, Vector& normal);
	void ProjectVertices(Vector vertices[], Vector axis, f32& min, f32& max, int len);
	bool CheckIntersect(Vector verticesA[], Vector verticesB[], int lenA, int lenB, f32& depth, Vector& normal);
}
