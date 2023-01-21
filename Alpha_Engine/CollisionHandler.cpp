#include "CollisionHandler.h"
#include "pch.h"
#include "VectorMath.h"
#include <limits>
#include <iostream>

namespace CollisionHandler {
	using namespace VectorMath;

	/*SAT COLLISION*/
	bool SAT_Collision(Object obj1, Object obj2, f32& depth, Vector& normal) {
		/*Get vertices of the 2 objects*/
		Vector* verticesA = GetVertices(obj1);
		Vector* verticesB = GetVertices(obj2);

		/*Initialize/reset normal and depth*/
		normal = Vector{ 0,0 };
		depth = static_cast<f32>((std::numeric_limits<float>::max)());

		/*Number of vertices*/
		int lenA = 4;/**(&verticesA + 1) - verticesA;*/
		int lenB = 4;/**(&verticesB + 1) - verticesB;*/

		/*Check for intersection*/
		bool out = (CheckIntersect(verticesA, verticesB, lenA, lenB, depth, normal) && CheckIntersect(verticesB, verticesA, lenB, lenA, depth, normal));

		depth /= GetLength(normal);
		normal = Normalize(normal);

		/*Check if normal is pointing in the correct
		direction by comparing with center of object A to center of object B.*/

		Vector dir = Vector{ obj2.pos.x - obj1.pos.x, obj2.pos.y - obj1.pos.y }; // Get vector from object A to object B

		/*If the normal is in the opposite direction, negate the vector.*/
		if (vecDotProduct(dir, normal) < 0.f) {
			normal.x = -normal.x;
			normal.y = -normal.y;
		}

		delete[] verticesA;
		delete[] verticesB;

		return out;
	}

	/*Projects the vertex onto a axis and returns the maximum and mimum points.*/
	void ProjectVertices(Vector vertices[], Vector axis, f32& min, f32& max, int len) {
		min = static_cast<f32>((std::numeric_limits<float>::max)());
		max = static_cast<f32>((std::numeric_limits<float>::min)());

		/*Get projection for each vertex and sets min and max respectively.*/
		for (int i = 0; i < len; i++) {
			f32 projection = vecDotProduct(vertices[i], axis);
			min = projection < min ? projection : min;
			max = projection > max ? projection : max;
		}
	}

	/*Check if the maximum and minimum projections of each object intersects*/
	bool CheckIntersect(Vector verticesA[], Vector verticesB[], int lenA, int lenB, f32& depth, Vector& normal) {
		for (int i = 0; i < lenA; i++) {
			f32 minA, maxA, minB, maxB;
			Vector va = verticesA[i];
			Vector vb = verticesA[(i + 1) % lenA]; // Loops back to the start if i reaches the end of the loop.

			Vector edge = vecSubtract(vb, va); // Get edge created by the 2 vertex
			Vector axis = { -edge.y, edge.x }; // Normal to the edge. Use this as the axis to compare to.

			/*Get minumum and maximum points*/
			ProjectVertices(verticesA, axis, minA, maxA, lenA);
			ProjectVertices(verticesB, axis, minB, maxB, lenB);

			/*If they do not intersect, return false.*/
			if (minA >= maxB || minB >= maxA)
				return false;

			f32 axisDepth = maxB - minA < maxA - minB ? maxB - minA : maxA - minB; // Returns the length of intersection

			/*Outs the smallest depth and axis for resolution*/
			if (axisDepth < depth) {
				depth = axisDepth;
				normal = axis;
			}
		}
		return true;
	}
}