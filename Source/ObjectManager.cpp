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

	/*
						  mm           mm
			  mm@**@@m   m@@           @@                    @@
			m@@*    *@@m  @@                                 @@
			@@*      *@@  @@m@@@@m   *@@@   mm@*@@  m@@*@@ @@@@@@
			@@        @@  @@    *@@    @@  m@*   @@@@*  @@   @@
			@@        @@  !@     @@    @@  !@******@!        @@
			*@@      @@*  !!!   m@!    @@  !@m    m@!m    m  @!
			!@@      !@!  !!     !!    !!  !!******!!        !!
			*@!!!    !!!  :!!   !!!    !!  :!!     !:!    !  !!
			  : : : :     : : : ::     :    : : ::  : : :    ::: :
									:: ::
									::::
	*/

	/*!***********************************************************************
	  \brief Construct a new Object:: Object object
	  
	*************************************************************************/
	Object::Object()
	{
		pTex			= nullptr;
		pMesh			= nullptr;
		type			= TYPE::PLAYER;
	}
	/*!***********************************************************************
	  \brief Destroy the Object:: Object object
	  
	*************************************************************************/
	Object::~Object()
	{
		
	}
	/*
				  mm           mm
	  mm@**@@m   m@@           @@                    @@   *@@@@*                      @@
	m@@*    *@@m  @@                                 @@     @@                        @@
	@@*      *@@  @@m@@@@m   *@@@   mm@*@@  m@@*@@ @@@@@@   @@  *@@@@@@@@m   m@@*@@@@@@@@@
	@@        @@  @@    *@@    @@  m@*   @@@@*  @@   @@     @@    @@    @@   @@   **  @@
	@@        @@  !@     @@    @@  !@******@!        @@     @!    @!    @@   *@@@@@m  @@
	*@@      @@*  !!!   m@!    @@  !@m    m@!m    m  @!     @!    @!    !@        @@  @!
	!@@      !@!  !!     !!    !!  !!******!!        !!     !!    !!    !!   *!   @!  !!
	*@!!!    !!!  :!!   !!!    !!  :!!     !:!    !  !!     :!    !!    !!   !!   !!  !!
	  : : : :     : : : ::     :    : : ::  : : :    ::: ::!: : : :::  :!: : : :!:    ::: :
							:: ::
							::::
*/
	/*!***********************************************************************
	  \brief Construct a new Object Inst:: Object Inst object
	  
	*************************************************************************/
	ObjectInst::ObjectInst()
	{
		pO			= nullptr;
		flag			= 0;
		texture		= { .0f };
		transf = { .0f };
		pair = nullptr;
	}
	/*!***********************************************************************
	  \brief Construct a new Object Inst:: Object Inst object from another object
	  
	  \param obj 
	*************************************************************************/
	ObjectInst::ObjectInst(const ObjectInst& obj) : ObjectInst()
	{
		*this = obj;
	}
	/*!***********************************************************************
	  \brief Destroy the Object Inst:: Object Inst object
	  
	*************************************************************************/
	ObjectInst::~ObjectInst()
	{

	}
	/*!***********************************************************************
	  \brief Get the elapsed animation time of the object
	  
	  \return f32& 
	*************************************************************************/
	f32 ObjectInst::GetCounter() const
	{ 
		return transf.m[2][0];
	}
	void ObjectInst::SetCounter(f32 dt)
	{
		transf.m[2][0] += dt;
	}
	void ObjectInst::ResetCounter()
	{
		transf.m[2][0] = .0f;
	}
	/*!***********************************************************************
	  \brief Get the player speed
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetPlayerSpeed()
	{ 
		return transf.m[2][1];
	}
	/*!***********************************************************************
	  \brief Get the Pos Z of the object in world screen coordinates
	  
	  \return f32& 
	*************************************************************************/
	f32& ObjectInst::GetPosZ()
	{ 
		return transf.m[2][2];
	}
	/*!***********************************************************************
	  \brief Get the Pos Z of the object in world screen coordinates
	  
	  \return f32 
	*************************************************************************/
	f32 ObjectInst::GetPosZ() const
	{ 
		return transf.m[2][2];
	}
	/*!***********************************************************************
	  \brief Get the Pos X and Pos Y of the object in world screen coordinates
	  
	  \return AEVec2 
	*************************************************************************/
	AEVec2 ObjectInst::GetPos() const
	{ 
		return { transf.m[0][2], transf.m[1][2] };
	}
	/*!***********************************************************************
	  \brief Set the Pos X and Pos Y of the object in world screen coordinates
	  
	  \param pos 
	*************************************************************************/
	void ObjectInst::SetPos(AEVec2 pos)
	{
		transf.m[0][2] = pos.x;
		transf.m[1][2] = pos.y;
	}
	/*!***********************************************************************
	  \brief Scale the object by a value
	  
	  \param val 
	  \return AEVec2 
	*************************************************************************/
	AEVec2 ObjectInst::GetScale(f32 val)
	{
		return { transf.m[0][0] * val, transf.m[1][1] * val };
	}
	void ObjectInst::SetScale(f32 val)
	{
		transf.m[0][0] *= val;
		transf.m[1][1] *= val;
	}
	/*!***********************************************************************
	  \brief Check the direction the player is facing
	  
	  \return int 
	*************************************************************************/
	int Character::CheckDirection()
	{
		int x{ static_cast<int>(dir.x) }, y{ static_cast<int>(dir.y) };
		return	(x > 0) ? (y > 0) ? RIGHT : (y) ? static_cast<int>(DOWN) : DOWNRIGHT :
			(x) ? (y > 0) ? UP : (y) ? static_cast<int>(LEFT) :  UPLEFT :
			(y > 0) ? static_cast<int>(UPRIGHT) : DOWNLEFT;
	}
	/*!***********************************************************************
	  \brief Get the texture offset of the objects
	  
	  \return AEVec2& 
	*************************************************************************/
	AEVec2& Character::GetOffset()
	{ 
		return pOI->texture;
	}
	/*!***********************************************************************
	  \brief Set the texture y offset of the player
	  
	*************************************************************************/
	void Character::SetOffsetY()
	{
		if (pOI->flag & ACTIVE)
			GetOffset().y = 0.125f * static_cast<f32>(CheckDirection());
	}
	/*!***********************************************************************
	  \brief Set the texture x offset of the player
	  
	*************************************************************************/
	void Character::SetOffsetX()
	{
		pOI->SetCounter(GSM::gameTime);
		if (pOI->flag & JUMPING)
			GetOffset().x = JUMP_SPRITE;
		else if (pOI->flag & ACTIVE)
		{
			if (pOI->GetCounter() >= 0.1f)
				iter = (pOI->ResetCounter(), ++iter % 10) ? iter : 1;
			GetOffset().x = static_cast<f32>(iter) / 11.0f;
		}
		else
			GetOffset().x = .0f;
	}
	/*!***********************************************************************
	  \brief Convert the object to isometric
	  
	  \param obj 
	  \return AEMtx33 
	*************************************************************************/
	AEMtx33 ConvertIsometric(const ObjectInst& obj)
	{
		AEMtx33 transform = obj.transf;
		transform.m[0][2] = (obj.GetPos().x + obj.GetPos().y);
		transform.m[1][2] = -(obj.GetPos().x - obj.GetPos().y) / 2.f + obj.GetPosZ();
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
