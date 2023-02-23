#pragma once
#include "PhysicsHandler.h"
#include "GSM.h"

namespace PhysicsHandler {

	void Move::MoveCharacter() 
	{
		AEVec2 pos{ this->pObjInst->GetPosXY() }, dir{ this->dir };
		if (this->pObjInst->flag & Enum::FLAG::ACTIVE)
		{
			f32 unitSpeed = this->pObjInst->GetPlayerSpeed() * GSM::gameTime;
			AEVec2Normalize(&dir, &dir);
			AEVec2Scale(&dir, &dir, unitSpeed);
			AEVec2Add(&pos, &pos, &dir);
		}
		this->pObjInst->GetPosX() = pos.x;
		this->pObjInst->GetPosY() = pos.y;
	}

}