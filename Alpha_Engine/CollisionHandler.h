#pragma once
#include "pch.h"

namespace CollisionHandler {
	using namespace GameObjects;
	bool SAT_Collision(ObjectInst obj1, ObjectInst obj2, f32& depth, AEVec2& normal);
	void ProjectVertices(AEVec2 vertices[], AEVec2 axis, f32& min, f32& max, int len);
	bool CheckIntersect(AEVec2 verticesA[], AEVec2 verticesB[], int lenA, int lenB, f32& depth, AEVec2& normal);
	double DistanceBetweenPlayerAndPortrait(AEVec2 const portrait_pos, AEVec2 const player_pos);
}
