#pragma once
#include "AEEngine.h"
#include "GameObjects.h"
#include <iostream>

namespace PhysicsHandler {
	void MovePlayer(GameObjects::Character& player) {
		AEVec2 pos{ player.pObjInst.transform.m[0][2], player.pObjInst.transform.m[1][2] };

		if (player.pObjInst.flag)
		{
			f32 unitSpeed = player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AEVec2Normalize(&player.dir, &player.dir);
			AEVec2Scale(&player.dir, &player.dir, unitSpeed);
			AEVec2Add(&pos, &pos, &player.dir);

			player.pObjInst.transform.m[0][2] = pos.x;
			player.pObjInst.transform.m[1][2] = pos.y;
		}
	}
}