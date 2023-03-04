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
	void Character::MoveCharacter()
	{
		AEVec2 pos{ pObjInst->GetPosXY() }, dire { dir };
		if (pObjInst->flag & Enum::FLAG::ACTIVE)
		{
			f32 unitSpeed = pObjInst->GetPlayerSpeed() * GSM::gameTime;
			AEVec2Normalize(&dire, &dire);
			AEVec2Scale(&dire, &dire, unitSpeed);
			AEVec2Add(&pos, &pos, &dire);
		}
		pObjInst->GetPosX() = pos.x;
		pObjInst->GetPosY() = pos.y;
	}

	bool Character::InCell(ObjectInst cell)
	{
		f32 x = cell.GetPosX();
		f32 y = cell.GetPosY();

		AEVec2 p1 = AEVec2{ x - pObjInst->GetScaleX() / 2.f, y + pObjInst->GetScaleY() / 2.f }; // top left
		AEVec2 p2 = AEVec2{ x + pObjInst->GetScaleX() / 2.f, y + pObjInst->GetScaleY() / 2.f }; // top right
		AEVec2 p4 = AEVec2{ x - pObjInst->GetScaleX() / 2.f, y - pObjInst->GetScaleY() / 2.f }; // bottom left
		AEVec2 p3 = AEVec2{ x + pObjInst->GetScaleX() / 2.f, y - pObjInst->GetScaleY() / 2.f }; // bottom right

		f32 playerX = pObjInst->GetPosX();
		f32 playerY = pObjInst->GetPosY();

		bool a = x - 0.5f <= playerX && playerX <= x + 0.5f;
		bool b = y - 0.5f <= playerY && playerY <= y + 0.5f;
		return a && b;
	}

	f32 Character::SlopeHeight(ObjectInst cell) 
	{
		f32 distance{};
		AEVec2 pos{ pObjInst->GetPosX(), pObjInst->GetPosY() };

		AEVec2 bot[2]	{ cell.botLeft, cell.botRight };
		AEVec2 top[2]	{ cell.topRight, cell.topLeft };;
		AEVec2 right[2]	{ cell.botRight, cell.topRight };;
		AEVec2 left[2]	{ cell.topLeft, cell.botLeft };;

		switch (cell.direction) {
		case Enum::NORTH:
			distance = CDM::PointLineDist(pos, bot);
			break;
		case Enum::SOUTH:
			distance = CDM::PointLineDist(pos, top);
			break;
		case Enum::EAST:
			distance = CDM::PointLineDist(pos, left);
			break;
		case Enum::WEST:
			distance = CDM::PointLineDist(pos, right);
			break;
		case Enum::NONE:
			//nothing
			break;
		default:
			break;
		}
		return distance;
	}

	void ObjectInst::SetCollider()
	{
		AEVec2 scale	= GetScaleXY();
		AEVec2 pos		= GetPosXY();
		topLeft			= { pos.x - scale.x / 2.f, pos.y + scale.y / 2.f };
		topRight		= { pos.x + scale.x / 2.f, pos.y + scale.y / 2.f };
		botLeft			= { pos.x - scale.x / 2.f, pos.y - scale.y / 2.f };
		botRight		= { pos.x + scale.x / 2.f, pos.y - scale.y / 2.f };
	}


}
