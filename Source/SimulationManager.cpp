#pragma once
#include "PCH.h"

namespace OM
{
	void Character::MoveCharacter()
	{
		AEVec2 pos{ this->pObjInst->GetPosXY() }, dir{ this->dir };
		if (this->pObjInst->flag & Enum::FLAG::ACTIVE)
		{
			f32 unitSpeed = this->pObjInst->GetPlayerSpeed() * gameTime;
			AEVec2Normalize(&dir, &dir);
			AEVec2Scale(&dir, &dir, unitSpeed);
			AEVec2Add(&pos, &pos, &dir);
		}
		this->pObjInst->GetPosX() = pos.x;
		this->pObjInst->GetPosY() = pos.y;
	}
}
