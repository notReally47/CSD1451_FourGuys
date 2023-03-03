/*!***********************************************************************
  \file	CollisionDetectionManager.cpp
  \authors 
  
  
  \brief 
  This file contains the implementation of the collision detection manager

  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "PCH.h"
#include "CollisionDetectionManager.h"
#include <limits>
#include <cmath>

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace CDM
{
	/*!***********************************************************************
	  \brief SAT collision detection
	  
	  \param obj1 
	  \param obj2 
	  \param depth 
	  \param normal 
	  \param GetVertices 
	  \return true 
	  \return false
	*************************************************************************/
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
		AEVec2 dir = AEVec2{ obj2.GetPosX() - obj1.GetPosX(), obj2.GetPosY() - obj1.GetPosY() }; // Get vector from object A to object B

		/*If the normal is in the opposite direction, negate the vector.*/
		if (AEVec2DotProduct(&dir, &normal) < 0.f) {
			normal.x = -normal.x;
			normal.y = -normal.y;
		}

		delete[] verticesA;
		delete[] verticesB;

		return out;
	}
	/*!***********************************************************************
	  \brief Projects the vertex onto a axis and returns the maximum and 
	  minimum points
	  
	  \param vertices 
	  \param axis 
	  \param min 
	  \param max 
	  \param len 
	*************************************************************************/
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

	/*!***********************************************************************
	  \brief Check if the maximum and minimum projections of each object
	  intersects
	  
	  \param verticesA 
	  \param verticesB 
	  \param lenA 
	  \param lenB 
	  \param depth 
	  \param normal 
	  \return true 
	  \return false 
	*************************************************************************/
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

	/*!***********************************************************************
	  \brief Get the distance between player and object
	  
	  \param portrait_x 
	  \param portrait_y 
	  \param player_x 
	  \param player_y 
	  \return double 
	*************************************************************************/
	double GetDistance(f32 const portrait_x, f32 const portrait_y, f32 const player_x, f32 const player_y) {
		return sqrt(pow(portrait_x - player_x, 2) + pow(portrait_y - player_y, 2));
	}

	/*!***********************************************************************
	  \brief Check if player is within range of object to interact
	  
	  \param portrait 
	  \param player 
	  \return true 
	  \return false 
	*************************************************************************/
	bool portraitInteract(ObjectInst const portrait, Character const player) {
		f32 dist = static_cast<f32>(sqrt(pow(portrait.transform.m[0][0] - player.pObjInst->transform.m[0][0], 2) + pow(portrait.GetPosY() - player.pObjInst->GetPosY(), 2)));

		if (dist < 55.f)
			return true;
		else
			return false;
	}
}