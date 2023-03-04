#pragma once
#include "pch.h"
#include <utility>

namespace CollisionHandler {
	//f32 cuboid[8][3] = {{ 0, 0, 0 }, 
	//					{ 1, 0, 0 }, 
	//					{ 0, 1, 0 },
	//					{ 1, 1, 0 }, 
	//					{ 0, 0, 1 },
	//					{ 1, 0, 1 },
	//					{ 0, 1, 1 },
	//					{ 1, 1, 1 }};

	// facing north => remove y = 0, remove 4,5
	// facing south => remove y = 1, remove 6,7
	// facing west => remove x = 0, remove 4,6
	// facing east => remove x = 1, remove 5,7
	using namespace GameObjects;
	bool SAT_Collision(ObjectInst obj1, ObjectInst obj2, f32& depth, AEVec2& normal, AEVec2* (*GetVertices)(ObjectInst, int&));
	void ProjectVertices(AEVec2 vertices[], AEVec2 axis, f32& min, f32& max, int len);
	bool CheckIntersect(AEVec2 verticesA[], AEVec2 verticesB[], int lenA, int lenB, f32& depth, AEVec2& normal);
	double GetDistance(f32 const portrait_x, f32 const portrait_y, f32 const player_x, f32 const player_y);
	f32 checkBoundary(Character const player);
	bool portraitInteract(ObjectInst const portrait, Character const player);

	void GetEdges(ObjectInst &obj);
	AEVec2 GetNormal(AEVec2 point1, AEVec2 point2);
	f32 CheckSide(AEVec2 normal, AEVec2 line, AEVec2 pos);
	bool InCell(ObjectInst &cell, ObjectInst &player);
	bool PointInCell(ObjectInst& cell, ObjectInst& player);
	std::pair<f32, f32> CalcLine(AEVec2 p1, AEVec2 p2);
	int CheckSide1(f32 m, f32 c, AEVec2 point);
}
