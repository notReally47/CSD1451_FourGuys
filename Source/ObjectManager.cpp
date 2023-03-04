/*!***********************************************************************
  \file   ObjectManager.cpp
  \authors
  
  \brief This file contains the implementation of the object manager

  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "PCH.h"
#include <vector>

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace OM
{
	/*DEFINES*/
	s8						fontId;
	const static f32		JUMP_SPRITE = 4.0f / 11.0f;
	using namespace			Enum;

	/*!***********************************************************************
	  \brief Construct a new Object:: Object object
	  
	*************************************************************************/
	Object::Object()
	{
		pTex			= nullptr;
		pMesh			= nullptr;
		type			= 0;
		width			= .0f;
		length			= .0f;
		height			= .0f;
	}

	/*!***********************************************************************
	  \brief Destroy the Object:: Object object
	  
	*************************************************************************/
	Object::~Object()
	{

	}

	/*!***********************************************************************
	  \brief Get the Scale X of the object in width
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetScaleX()
	{ 
		return transform.m[0][0]; // check if this is used anywhere
	} 

	/*!***********************************************************************
	  \brief Get the Pos X of the object in world screen coordinates
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetPosX()
	{ 
		return transform.m[0][2];
	}

	/*!***********************************************************************
	  \brief Get the Pos X of the object in world screen coordinates
	  
	  \return f32 
	*************************************************************************/
	f32 ObjectInst::GetPosX() const
	{ 
		return transform.m[0][2];
	}

	/*!***********************************************************************
	  \brief Get the Scale Y of the object in height
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetScaleY()
	{ 
		return transform.m[1][1];
	}

	/*!***********************************************************************
	  \brief Get the Pos Y of the object in world screen coordinates
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetPosY()
	{
		return transform.m[1][2];
	}

	/*!***********************************************************************
	  \brief Get the Pos Y of the object in world screen coordinates
	  
	  \return f32 
	*************************************************************************/
	f32 ObjectInst::GetPosY() const
	{ 
		return transform.m[1][2];
	}

	/*!***********************************************************************
	  \brief Get the elapsed animation time of the object
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetElapsed()
	{ 
		return transform.m[2][0];
	}

	/*!***********************************************************************
	  \brief Get the player speed
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetPlayerSpeed()
	{ 
		return transform.m[2][1];
	}

	/*!***********************************************************************
	  \brief Get the Pos Z of the object in world screen coordinates
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetPosZ()
	{ 
		return transform.m[2][2];
	}

	/*!***********************************************************************
	  \brief Get the Pos Z of the object in world screen coordinates
	  
	  \return f32 
	*************************************************************************/
	f32 ObjectInst::GetPosZ() const
	{ 
		return transform.m[2][2];
	}

	AEVec2 ObjectInst::GetScaleXY()
	{
		return { GetScaleX(), GetScaleY() };
	}

	/*!***********************************************************************
	  \brief Get the Pos X and Pos Y of the object in world screen coordinates
	  
	  \return AEVec2 
	*************************************************************************/
	AEVec2 ObjectInst::GetPosXY()
	{ 
		return { GetPosX(), GetPosY() }; 
	}

	/*!***********************************************************************
	  \brief Check the direction the player is facing
	  
	  \return int 
	*************************************************************************/
	int Character::CheckDirection()
	{
		int x{ static_cast<int>(dir.x) }, y{ static_cast<int>(dir.y) };
		return	(x > 0) ? (y > 0) ? UP : (y) ? static_cast<int>(RIGHT) : UPRIGHT :
			(x) ? (y > 0) ? LEFT : (y) ? static_cast<int>(DOWN) : DOWNLEFT :
			(y > 0) ? static_cast<int>(UPLEFT) : DOWNRIGHT;
	}

	/*!***********************************************************************
	  \brief Get the texture offset of the object
	  
	  \return AEVec2& 
	*************************************************************************/
	AEVec2& Character::GetOffset()
	{ 
		return pObjInst->tex_offset;
	}

	/*!***********************************************************************
	  \brief Set the texture y offset of the player
	  
	*************************************************************************/
	void Character::SetOffsetY()
	{
		if (pObjInst->flag & ACTIVE)
			GetOffset().y = 0.125f * static_cast<f32>(CheckDirection());
	}

	/*!***********************************************************************
	  \brief Set the texture x offset of the player
	  
	*************************************************************************/
	void Character::SetOffsetX()
	{
		pObjInst->GetElapsed() += GSM::gameTime;
		if (pObjInst->flag & JUMPING)
			GetOffset().x = JUMP_SPRITE;
		else if (pObjInst->flag & ACTIVE)
		{
			if (pObjInst->GetElapsed() >= 0.1f)
				spriteIteration = (pObjInst->GetElapsed() = .0f, ++spriteIteration % 10) ? spriteIteration : 1;
			GetOffset().x = static_cast<f32>(spriteIteration) / 11.0f;
		}
		else
			GetOffset().x = .0f;
	}

	/*!***********************************************************************
	  \brief Get the Vertices X Y object
	  
	  \param obj 
	  \param count 
	  \return AEVec2* 
	*************************************************************************/
	AEVec2* GetVerticesXY(const ObjectInst& obj, int& count)
	{
		count = 4;

		AEVec2* xyCoords = { new AEVec2[count] };
		xyCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosY() + obj.pObj->length / 2 }; //top right
		xyCoords[1] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosY() + obj.pObj->length / 2 }; //top left
		xyCoords[2] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosY() - obj.pObj->length / 2 }; //bot right
		xyCoords[3] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosY() - obj.pObj->length / 2 }; //bot left

		//TODO: Any rotatation 
		return xyCoords;
	}

	/*!***********************************************************************
	  \brief Get the Vertices Y Z object
	  
	  \param obj 
	  \param count 
	  \return AEVec2* 
	*************************************************************************/
	AEVec2* GetVerticesYZ(const ObjectInst& obj, int& count)
	{
		count = 4;
		AEVec2* yzCoords = { new AEVec2[count] };
		yzCoords[0] = AEVec2{ obj.GetPosY() - obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; //top right
		yzCoords[1] = AEVec2{ obj.GetPosY() + obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; //top left
		yzCoords[2] = AEVec2{ obj.GetPosY() - obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; //bot right
		yzCoords[3] = AEVec2{ obj.GetPosY() + obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; //bot left

		//TODO: Any rotatation 
		return yzCoords;
	}

	/*!***********************************************************************
	  \brief Get the Vertices X Z object
	  
	  \param obj 
	  \param count 
	  \return AEVec2* 
	*************************************************************************/
	AEVec2* GetVerticesXZ(const ObjectInst& obj, int& count)
	{
		if (1) { //TODO: Change to check if not a staircase
			count = 4;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; // top right
			xzCoords[1] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; // top left
			xzCoords[2] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; // bot right
			xzCoords[3] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; // bot left
			return xzCoords;
		}
		else {
			count = 3;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 3,
									obj.GetPosZ() - obj.pObj->height / 3 };		// bot left

			xzCoords[1] = AEVec2{ obj.GetPosX() - obj.pObj->width / 3,
									obj.GetPosZ() + (2 * obj.pObj->height) / 3 }; // top left

			xzCoords[2] = AEVec2{ obj.GetPosX() + (2 * obj.pObj->width) / 3,
									obj.GetPosZ() - obj.pObj->height / 3 };		// bot right

			return xzCoords;
		}
	}

	/*!***********************************************************************
	  \brief Convert the object to isometric
	  
	  \param obj 
	  \return AEMtx33 
	*************************************************************************/
	AEMtx33 ConvertIsometric(const ObjectInst& obj)
	{
		AEMtx33 transform = obj.transform;
		transform.m[0][2] = (obj.GetPosX() - obj.GetPosY());
		transform.m[1][2] = (obj.GetPosX() + obj.GetPosY()) / 2.f + obj.GetPosZ();
		return transform;
	}

	/*!***********************************************************************
	  \brief Checks if a point is on the left or right side of a line

	  \param AEVec2 point
	  \param AEVec2 pt1
	  \param AEVec2 pt2
	  \return int: returns 1 if point is on the left side, -1 if point is on the right side, and 0 if point is on the line.
	*************************************************************************/
	int PointLineClassification(AEVec2 point, AEVec2 pt1, AEVec2 pt2)
	{
		int out;
		f32 result = (point.x - pt1.x) * (pt2.y - pt1.y) - (point.y - pt1.y) * (pt2.x - pt1.x);
		out = result > 0 ? 1 : result < 0 ? -1 : 0;
		return out;
	}
}
