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
		AEVec2 pos{ pObjInst->transform.m[0][2], pObjInst->transform.m[1][2] };

		if (pObjInst->flag)
		{
			f32 unitSpeed = pObjInst->GetPlayerSpeed() * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			if (dir.x != 0 || dir.y != 0) {
				AEVec2Normalize(&dir, &dir);
				AEVec2Scale(&dir, &dir, unitSpeed);
				AEVec2Add(&pos, &pos, &dir);
			}
			pObjInst->transform.m[0][2] = 0.f > pos.x || pos.x > 5.f ? pObjInst->transform.m[0][2] : pos.x;
			pObjInst->transform.m[1][2] = 0.f > pos.y || pos.y > 5.f ? pObjInst->transform.m[1][2] : pos.y;
		}
	}

	bool Character::InCell(ObjectInst cell)
	{
		f32 x = cell.transform.m[0][2];
		f32 y = cell.transform.m[1][2];

		AEVec2 p1 = AEVec2{ x,			y + 1.f }; // top left
		AEVec2 p2 = AEVec2{ x + 1.f,	y + 1.f }; // top right
		AEVec2 p4 = AEVec2{ x,			y		}; // bottom left
		AEVec2 p3 = AEVec2{ x + 1.f,	y		}; // bottom right

		f32 playerX = pObjInst->GetPosX();
		f32 playerY = pObjInst->GetPosY();

		bool a = x <= playerX && playerX <= x + 1.f;
		bool b = y <= playerY && playerY <= y + 1.f;
		return a && b;
	}

	f32 Character::HandleSlope(ObjectInst cell)
	{
		f32 displacement = pObjInst->GetPlayerSpeed() * (f32)AEFrameRateControllerGetFrameTime() * (cell.pObj->height);

		switch (cell.direction) {
		case Enum::NORTH:
			displacement = input.y > 0 ? displacement : input.y < 0 ? -displacement : 0;
			break;
		case Enum::SOUTH:
			displacement = input.y < 0 ? displacement : input.y > 0 ? -displacement : 0;
			break;
		case Enum::WEST:
			displacement = input.x < 0 ? displacement : input.x > 0 ? -displacement : 0;
			break;
		case Enum::EAST:
			displacement = input.x > 0 ? displacement : input.x < 0 ? -displacement : 0;
			break;
		default:
			displacement = 0.f;
			break;
		}

		return displacement;
	}

	void ObjectInst::SetCollider()
	{
		AEVec2 pos	= GetPosXY();
		topLeft		= { pos.x - 0.5f, pos.y + 0.5f };
		topRight	= { pos.x + 0.5f, pos.y + 0.5f };
		botLeft		= { pos.x - 0.5f, pos.y - 0.5f };
		botRight	= { pos.x + 0.5f, pos.y - 0.5f };
	}


}
