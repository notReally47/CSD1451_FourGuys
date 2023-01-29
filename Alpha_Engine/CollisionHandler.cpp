#include "CollisionHandler.h"
#include "pch.h"
#include <limits>
#include <iostream>
#include <cmath>

namespace CollisionHandler {

	/*SAT COLLISION*/
	bool SAT_Collision(ObjectInst obj1, ObjectInst obj2, f32& depth, AEVec2& normal) {
		/*Get vertices of the 2 objects*/
		AEVec2* verticesA = GetVertices(obj1);
		AEVec2* verticesB = GetVertices(obj2);

		/*Initialize/reset normal and depth*/
		normal = AEVec2{ 0,0 };
		depth = static_cast<f32>((std::numeric_limits<float>::max)());

		/*Number of vertices*/
		int lenA = 4;/**(&verticesA + 1) - verticesA;*/
		int lenB = 4;/**(&verticesB + 1) - verticesB;*/

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

	f32 checkBoundary(Character const player) {
		f32 leftBoarder = -7.f * (f32)AEGetWindowWidth() / 20.f, rightBoarder = 7.f * (f32)AEGetWindowWidth() / 20.f;
		return leftBoarder > player.pObjInst.transform.m[0][2] ? leftBoarder - player.pObjInst.transform.m[0][2] : player.pObjInst.transform.m[0][2] > rightBoarder ? rightBoarder - player.pObjInst.transform.m[0][2] : 0.f;
	}

	bool portraitInteract(ObjectInst const portrait, Character const player) {
		f32 dist = sqrt(pow(portrait.transform.m[0][0] - player.pObjInst.transform.m[0][0], 2) + pow(portrait.transform.m[1][2] - player.pObjInst.transform.m[1][2], 2));

		if (dist < 55.f)
			return true;
		else
			return false;
	}
}