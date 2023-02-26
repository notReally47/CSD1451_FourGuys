#include "CollisionHandler.h"
#include "pch.h"
#include <limits>
#include <iostream>
#include <cmath>
#include <cstdlib>

namespace CollisionHandler
{

	/*SAT COLLISION*/
	bool SAT_Collision(ObjectInst obj1, ObjectInst obj2, f32 &depth, AEVec2 &normal, AEVec2 *(*GetVertices)(ObjectInst, int &))
	{
		int lenA{};
		int lenB{};

		/*Get vertices of the 2 objects*/
		AEVec2 *verticesA = GetVertices(obj1, lenA);
		AEVec2 *verticesB = GetVertices(obj2, lenB);

		/*Initialize/reset normal and depth*/
		normal = AEVec2{0, 0};
		depth = static_cast<f32>((std::numeric_limits<float>::max)());

		/*Check for all intersections*/
		bool out = (CheckIntersect(verticesA, verticesB, lenA, lenB, depth, normal) && CheckIntersect(verticesB, verticesA, lenB, lenA, depth, normal));

		depth /= AEVec2Length(&normal);
		AEVec2Normalize(&normal, &normal);

		/*Check if normal is pointing in the correct
		direction by comparing with center of object A to center of object B.
		obj2 position x - obj1 position x, obj2 position y - obj1 position y */
		AEVec2 dir = AEVec2{obj2.GetPosX() - obj1.GetPosX(), obj2.GetPosY() - obj1.GetPosY()}; // Get vector from object A to object B

		/*If the normal is in the opposite direction, negate the vector.*/
		if (AEVec2DotProduct(&dir, &normal) < 0.f)
		{
			normal.x = -normal.x;
			normal.y = -normal.y;
		}

		delete[] verticesA;
		delete[] verticesB;

		return out;
	}

	/*Projects the vertex onto a axis and returns the maximum and mimum points.*/
	void ProjectVertices(AEVec2 vertices[], AEVec2 axis, f32 &min, f32 &max, int len)
	{
		min = static_cast<f32>((std::numeric_limits<float>::max)());
		max = static_cast<f32>((std::numeric_limits<float>::min)());

		/*Get projection for each vertex and sets min and max respectively.*/
		for (int i = 0; i < len; i++)
		{
			f32 projection = AEVec2DotProduct(&vertices[i], &axis);
			min = projection < min ? projection : min;
			max = projection > max ? projection : max;
		}
	}

	/*Check if the maximum and minimum projections of each object intersects*/
	bool CheckIntersect(AEVec2 verticesA[], AEVec2 verticesB[], int lenA, int lenB, f32 &depth, AEVec2 &normal)
	{
		for (int i = 0; i < lenA; i++)
		{
			f32 minA, maxA, minB, maxB;
			AEVec2 va = verticesA[i];
			AEVec2 vb = verticesA[(i + 1) % lenA]; // Loops back to the start if i reaches the end of the loop.

			AEVec2 edge;
			AEVec2Sub(&edge, &vb, &va);	  // Get edge created by the 2 vertex
			AEVec2 axis{-edge.y, edge.x}; // Normal to the edge. Use this as the axis to compare to.

			/*Get minumum and maximum points*/
			ProjectVertices(verticesA, axis, minA, maxA, lenA);
			ProjectVertices(verticesB, axis, minB, maxB, lenB);

			/*If they do not intersect, return false.*/
			if (minA >= maxB || minB >= maxA)
				return false;

			f32 axisDepth = maxB - minA < maxA - minB ? maxB - minA : maxA - minB; // Length/depth of intersection

			/*Outs the smallest depth and axis for resolution*/
			if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = axis;
			}
		}
		return true;
	}

	double GetDistance(f32 const object_x, f32 const object_y, f32 const width, f32 const height, f32 const player_x, f32 const player_y)
	{
		std::cout << "wall x y " << object_x <<" "<< object_y<< "\n";
		std::cout << "wall w h " << width <<" "<< height<< "\n";
		std::cout << "player x y " << player_x <<" "<< player_y<< "\n";

		f32 minX = object_x - width / 2;
		f32 minY = object_y - height / 2;
		f32 maxX = object_x + width / 2;
		f32 maxY = object_y + height / 2;
		if (player_x >= minX && player_x <= maxX && player_y >= minY && player_y <= maxY)
			// point is inside the rectangle
			return 0.0;
		else
		{
			// distance between point and rec
			double dx = max(minX - player_x, 0.0) + max(player_x - (minX + width), 0.0);
			double dy = max(minY - player_y, 0.0) + max(player_y - (minY + height), 0.0);
			return sqrt(dx * dx + dy * dy);
		}
	}
}