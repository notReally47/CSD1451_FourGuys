/*!***********************************************************************
  \file   SimulationManager.cpp
  \authors

  \brief 
  This file contains the implementation of the simulation manager

  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/
#pragma once
#include "PCH.h"

namespace OM
{
	/*!***********************************************************************
	  \brief Move the character based on the direction vector
	  
	*************************************************************************/
	void Character::MoveCharacter()
	{
		AEVec2 pos{ pOI->GetPos() }, dire { dir };
		if (pOI->flag & Enum::FLAG::ACTIVE)
		{
			f32 unitSpeed = pOI->GetPlayerSpeed() * GSM::gameTime;
			AEVec2Normalize(&dire, &dire);
			AEVec2Scale(&dire, &dire, unitSpeed);
			AEVec2Add(&pos, &pos, &dire);
		}
		pOI->SetPos(pos);
	}
	/*!***********************************************************************
	  \brief Check if the character is in the cell
	  
	  \param cell 
	  \return true 
	  \return false 
	*************************************************************************/
	bool Character::InCell(ObjectInst cell)
	{
		f32 x = cell.GetPos().x;
		f32 y = cell.GetPos().y;

		AEVec2 p1 = AEVec2{ x - pOI->GetScale(0.5f).x, y + pOI->GetScale(0.5f).y }; // top left
		AEVec2 p2 = AEVec2{ x + pOI->GetScale(0.5f).x, y + pOI->GetScale(0.5f).y }; // top right
		AEVec2 p4 = AEVec2{ x - pOI->GetScale(0.5f).x, y - pOI->GetScale(0.5f).y }; // bottom left
		AEVec2 p3 = AEVec2{ x + pOI->GetScale(0.5f).x, y - pOI->GetScale(0.5f).y }; // bottom right

		f32 playerX = pOI->GetPos().x;
		f32 playerY = pOI->GetPos().y;

		bool a = x - 0.5f <= playerX && playerX <= x + 0.5f;
		bool b = y - 0.5f <= playerY && playerY <= y + 0.5f;
		return a && b;
	}
	/*!***********************************************************************
	  \brief Get the height of the slope
	  
	  \param cell 
	  \return f32 
	*************************************************************************/
	//f32 Character::SlopeHeight(ObjectInst cell) 
	//{
	//	f32 distance{};
	//	AEVec2 pos{ pOI->GetPos() };

	//	AEVec2 bot[2]	{ cell.botLeft, cell.botRight };
	//	AEVec2 top[2]	{ cell.topRight, cell.topLeft };;
	//	AEVec2 right[2]	{ cell.botRight, cell.topRight };;
	//	AEVec2 left[2]	{ cell.topLeft, cell.botLeft };;

	//	switch (cell.direction) {
	//	case Enum::NORTH:
	//		distance = CDM::PointLineDist(pos, bot);
	//		break;
	//	case Enum::SOUTH:
	//		distance = CDM::PointLineDist(pos, top);
	//		break;
	//	case Enum::EAST:
	//		distance = CDM::PointLineDist(pos, left);
	//		break;
	//	case Enum::WEST:
	//		distance = CDM::PointLineDist(pos, right);
	//		break;
	//	case Enum::NONE:
	//		//nothing
	//		break;
	//	default:
	//		break;
	//	}
	//	return distance;
	//}
	/*!***********************************************************************
	  \brief Set the collider vertices
	  
	*************************************************************************/
	//void ObjectInst::SetCollider()
	//{
	//	topLeft			= { GetPos().x - GetScale(0.5f).x, GetPos().y + GetScale(0.5f).y };
	//	topRight		= { GetPos().x + GetScale(0.5f).x, GetPos().y + GetScale(0.5f).y };
	//	botLeft			= { GetPos().x - GetScale(0.5f).x, GetPos().y - GetScale(0.5f).y };
	//	botRight		= { GetPos().x + GetScale(0.5f).x, GetPos().y - GetScale(0.5f).y };
	//}


}
