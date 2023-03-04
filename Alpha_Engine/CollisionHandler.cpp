#include "CollisionHandler.h"
#include "pch.h"
#include <limits>
#include <iostream>
#include <cmath>

namespace CollisionHandler {

	/*SAT COLLISION*/
	bool SAT_Collision(ObjectInst obj1, ObjectInst obj2, f32& depth, AEVec2& normal, AEVec2* (*GetVertices)(ObjectInst, int&)) {
		int lenA{};
		int lenB{};

		/*Get vertices of the 2 objects*/
		AEVec2* verticesA = GetVertices(obj1, lenA);
		AEVec2* verticesB = GetVertices(obj2, lenB);

		/*Initialize/reset normal and depth*/
		normal = AEVec2{ 0,0 };
		depth = static_cast<f32>((std::numeric_limits<float>::max)());

		/*Check for all intersections*/
		bool out = (CheckIntersect(verticesA, verticesB, lenA, lenB, depth, normal) && CheckIntersect(verticesB, verticesA, lenB, lenA, depth, normal));

		depth /= AEVec2Length(&normal);
		AEVec2Normalize(&normal, &normal);

		/*Check if normal is pointing in the correct
		direction by comparing with center of object A to center of object B.
		obj2 position x - obj1 position x, obj2 position y - obj1 position y */
		AEVec2 dir = AEVec2{ obj2.transform.m[0][2] - obj1.transform.m[0][2], obj2.transform.m[1][2] - obj1.transform.m[1][2] }; // Get vector from object A to object B

		/*If the normal is in the opposite direction, negate the vector.*/
		if (AEVec2DotProduct(&dir, &normal) < 0.f) {
			normal.x = -normal.x;
			normal.y = -normal.y;
		}

		delete[] verticesA;
		delete[] verticesB;

		return out;
	}

	/*Projects the vertex onto a axis and returns the maximum and mimum points.*/
	void ProjectVertices(AEVec2 vertices[], AEVec2 axis, f32& min, f32& max, int len) {
		min = static_cast<f32>((std::numeric_limits<float>::max)());
		max = static_cast<f32>((std::numeric_limits<float>::min)());

		/*Get projection for each vertex and sets min and max respectively.*/
		for (int i = 0; i < len; i++) {
			f32 projection = AEVec2DotProduct(&vertices[i], &axis);
			min = projection < min ? projection : min;
			max = projection > max ? projection : max;
		}
	}

	/*Check if the maximum and minimum projections of each object intersects*/
	bool CheckIntersect(AEVec2 verticesA[], AEVec2 verticesB[], int lenA, int lenB, f32& depth, AEVec2& normal) {
		for (int i = 0; i < lenA; i++) {
			f32 minA, maxA, minB, maxB;
			AEVec2 va = verticesA[i];
			AEVec2 vb = verticesA[(i + 1) % lenA]; // Loops back to the start if i reaches the end of the loop.

			AEVec2 edge;
			AEVec2Sub(&edge, &vb, &va); // Get edge created by the 2 vertex
			AEVec2 axis{ -edge.y, edge.x }; // Normal to the edge. Use this as the axis to compare to.

			/*Get minumum and maximum points*/
			ProjectVertices(verticesA, axis, minA, maxA, lenA);
			ProjectVertices(verticesB, axis, minB, maxB, lenB);

			/*If they do not intersect, return false.*/
			if (minA >= maxB || minB >= maxA)
				return false;

			f32 axisDepth = maxB - minA < maxA - minB ? maxB - minA : maxA - minB; // Length/depth of intersection

			/*Outs the smallest depth and axis for resolution*/
			if (axisDepth < depth) {
				depth = axisDepth;
				normal = axis;
			}
		}
		return true;
	}


	double GetDistance(f32 const portrait_x, f32 const portrait_y, f32 const player_x, f32 const player_y) {
		return sqrt(pow(portrait_x - player_x, 2) + pow(portrait_y - player_y, 2));
	}

	bool portraitInteract(ObjectInst const portrait, Character const player) {
		f32 dist = static_cast<f32>(sqrt(pow(portrait.transform.m[0][0] - player.pObjInst.transform.m[0][0], 2) + pow(portrait.transform.m[1][2] - player.pObjInst.transform.m[1][2], 2)));

		if (dist < 55.f)
			return true;
		else
			return false;
	}

	void GetEdges(ObjectInst &obj) {
		f32 posX = obj.transform.m[0][1];
		f32 posY = obj.transform.m[0][2];

		AEVec2 topleft = AEVec2{ posX - 0.5f, posY + 0.5f }; // top left
		AEVec2 topright = AEVec2{ posX + 0.5f, posY + 0.5f }; // top right
		AEVec2 botleft = AEVec2{ posX - 0.5f, posY - 0.5f }; // bottom left
		AEVec2 botright = AEVec2{ posX + 0.5f, posY - 0.5f }; // bottom right

		obj.top[0] = topleft;
		obj.top[1] = topright;

		obj.bot[0] = botright;
		obj.bot[1] = botleft;

		obj.right[0] = topright;
		obj.right[1] = botright;

		obj.left[0] = botleft;
		obj.left[1] = topleft;
	}

	AEVec2 GetNormal(AEVec2 point1, AEVec2 point2) {
		AEVec2 lineVec;
		AEVec2Sub(&lineVec, &point2, &point1);
		AEVec2Normalize(&lineVec, &lineVec);
		return AEVec2{ lineVec.y, -lineVec.x };
	}

	f32 CheckSide(AEVec2 normal, AEVec2 line, AEVec2 pos) {
		f32 p0 = AEVec2DotProduct(&normal, &line);
		f32 q = AEVec2DotProduct(&normal, &pos);
		f32 out = q - p0;
		return out;
	}

	bool InCell(ObjectInst &cell, ObjectInst &player) {
		GetEdges(cell);
		AEVec2 topNormal = GetNormal(cell.top[0], cell.top[1]);
		AEVec2 botNormal = GetNormal(cell.bot[0], cell.bot[1]);
		AEVec2 leftNormal = GetNormal(cell.left[0], cell.left[1]);
		AEVec2 rightNormal = GetNormal(cell.right[0], cell.right[1]);

		AEVec2 playerPos = { player.transform.m[0][2], player.transform.m[1][2] };

		f32 topDist = CheckSide(topNormal, cell.top[0], playerPos);
		f32 botDist = CheckSide(botNormal, cell.bot[0], playerPos);
		f32 leftDist = CheckSide(leftNormal, cell.left[0], playerPos);
		f32 rightDist = CheckSide(rightNormal, cell.right[0], playerPos);

		return (topDist > 0 && botDist > 0 && leftDist > 0 && rightDist > 0);
	}

	bool PointInCell(ObjectInst& cell, ObjectInst& player) {
		f32 x = cell.transform.m[0][2];
		f32 y = cell.transform.m[1][2];

		AEVec2 p1 = AEVec2{ x - 0.5f, y + 0.5f }; // top left
		AEVec2 p2 = AEVec2{ x + 0.5f, y + 0.5f }; // top right
		AEVec2 p4 = AEVec2{ x - 0.5f, y - 0.5f }; // bottom left
		AEVec2 p3 = AEVec2{ x + 0.5f, y - 0.5f }; // bottom right

		f32 playerX = player.transform.m[0][2];
		f32 playerY = player.transform.m[1][2];

		bool a = x - 0.5f <= playerX && playerX <= x + 0.5f;
		bool b = y - 0.5f <= playerY && playerY <= y + 0.5f;
		return a && b;
	}

 	std::pair<f32, f32> CalcLine(AEVec2 p1, AEVec2 p2) {
		std::pair<f32, f32> line;
		line.first = (p2.y - p1.y) / (p2.x, p1.x);
		line.second = p1.y - line.first * p1.x;
		return line;
	}

	int CheckSide1(f32 m, f32 c, AEVec2 point) {
		f32 yOnLine = m * point.x + c;
		std::cout << yOnLine << std::endl;
		if (point.y > yOnLine)
			return 1;
		else if (point.y < yOnLine)
			return -1;
		else return 0;
	}
}