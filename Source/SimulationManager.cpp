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
}
