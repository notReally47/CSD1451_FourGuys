#pragma once
#include "pch.h"

namespace CollisionHandler {
	using namespace GameObjects;
	bool Collided(Object obj1, Object obj2);
	void ResetPosition(Character& movingObj, int direction);
	bool SAT_Collision(Object obj1, Object obj2);
	void ProjectVertices(Vector vertices[], Vector axis, f32& min, f32& max, int len);
	bool CheckIntersect(Vector verticesA[], Vector verticesB[], int lenA, int lenB);
}
