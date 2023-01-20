#include "CollisionHandler.h"
#include "pch.h"
#include "VectorMath.h"
#include <limits>
#include <iostream>

namespace CollisionHandler {
	using namespace GameObjects;
	using namespace VectorMath;

	/*AABB Collision*/
	bool Collided(Object obj1, Object obj2) {
		return obj1.pos.x - (obj1.width) < obj2.pos.x + (obj2.width) &&
			obj1.pos.x + (obj1.width) > obj2.pos.x - (obj2.width) &&
			obj1.pos.y - (obj1.height) < obj2.pos.y + (obj2.height) &&
			obj1.pos.y + (obj1.height) > obj2.pos.y - (obj2.height);
	}

	void ResetPosition(Character& movingObj, int direction) {
		switch (direction) {
		case Enum::RIGHT:
			//movingObj.obj.pos.x -= movingObj.velocity_x * AEFrameRateControllerGetFrameTime();
			movingObj.velocity_x = -movingObj.velocity_x;
			break;
		case Enum::LEFT:
			//movingObj.obj.pos.x -= movingObj.velocity_x * AEFrameRateControllerGetFrameTime();
			movingObj.velocity_x = -movingObj.velocity_x;
			break;
		default:
			break;
		}
	}

	/*SAT COLLISION*/
	bool SAT_Collision(Object obj1, Object obj2, f32& depth, Vector& normal) {
		Vector* verticesA = GetVertices(obj1);
		Vector* verticesB = GetVertices(obj2);

		normal = Vector{ 0,0 };
		depth = static_cast<f32>((std::numeric_limits<float>::max)());

		int lenA = 4;/**(&verticesA + 1) - verticesA;*/
		int lenB = 4;/**(&verticesB + 1) - verticesB;*/

		bool out = (CheckIntersect(verticesA, verticesB, lenA, lenB, depth, normal) && CheckIntersect(verticesB, verticesA, lenB, lenA, depth, normal));
		depth /= GetLength(normal);
		normal = Normalize(normal);

		Vector dir = Vector{ obj2.pos.x - obj1.pos.x, obj2.pos.y - obj1.pos.y };

		if (vecDotProduct(dir, normal) < 0.f) {
			normal.x = -normal.x;
			normal.y = -normal.y;
		}

		delete[] verticesA;
		delete[] verticesB;
		return out;
	}

	void ProjectVertices(Vector vertices[], Vector axis, f32& min, f32& max, int len) {
		min = static_cast<f32>((std::numeric_limits<float>::max)());
		max = static_cast<f32>((std::numeric_limits<float>::min)());

		for (int i = 0; i < len; i++)
		{
			Vector v = vertices[i];
			f32 projection = vecDotProduct(v, axis);

			min = projection < min ? projection : min;
			max = projection > max ? projection : max;
		}
	}

	bool CheckIntersect(Vector verticesA[], Vector verticesB[], int lenA, int lenB, f32& depth, Vector& normal) {
		for (int i = 0; i < lenA; i++) {
			f32 minA, maxA, minB, maxB;
			Vector va = verticesA[i];
			Vector vb = verticesA[(i + 1) % lenA];

			Vector edge = vecSubtract(vb, va);
			Vector axis = { -edge.y, edge.x };

			ProjectVertices(verticesA, axis, minA, maxA, lenA);
			ProjectVertices(verticesB, axis, minB, maxB, lenB);

			if (minA >= maxB || minB >= maxA) {
				return false;
			}

			f32 axisDepth = maxB - minA < maxA - minB ? maxB - minA : maxA - minB;
			if (axisDepth < depth) {
				depth = axisDepth;
				normal = axis;
			}
		}
		return true;
	}
}