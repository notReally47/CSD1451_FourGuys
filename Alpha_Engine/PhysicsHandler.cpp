#pragma once
#include "AEEngine.h"
#include "GameObjects.h"
#include <iostream>

namespace PhysicsHandler {
	void MovePlayer(GameObjects::Character& player) {
		AEVec2 pos{ player.pObjInst->GetPosXY() };
		if (player.pObjInst->flag & Enum::FLAG::ACTIVE)
		{
			f32 unitSpeed = player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AEVec2Normalize(&player.dir, &player.dir);
			AEVec2Scale(&player.dir, &player.dir, unitSpeed);
			AEVec2Add(&pos, &pos, &player.dir);

			player.pObjInst->GetPosX() = pos.x;
			player.pObjInst->GetPosY() = pos.y;
		}
	}
}