#pragma once
#include "PCH.h"

namespace CDM
{
	using namespace OM;
	bool SAT_Collision(ObjectInst obj1, ObjectInst obj2, f32& depth, AEVec2& normal, AEVec2* (*GetVertices)(ObjectInst, int&));
	void ProjectVertices(AEVec2 vertices[], AEVec2 axis, f32& min, f32& max, int len);
	bool CheckIntersect(AEVec2 verticesA[], AEVec2 verticesB[], int lenA, int lenB, f32& depth, AEVec2& normal);
	double GetDistance(f32 const portrait_x, f32 const portrait_y, f32 const player_x,f32 const player_y);
	bool portraitInteract(ObjectInst const portrait, Character const player);
}