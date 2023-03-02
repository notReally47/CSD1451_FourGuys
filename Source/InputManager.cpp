#include "PCH.h"
#include "InputManager.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace IM
{
	const static f32 GRAVITY		= -1000.f;
	const static f32 JUMP_HEIGHT	= 50.f;

	using namespace OM;


	void ExitGame(GAME_STATES next) {
		if (AEInputCheckTriggered(AEVK_ESCAPE))
			next = GAME_STATES::QUIT;
	}

	bool PlayerMovement(Character& player) {
		AEVec2 dir{ .0f,.0f };
		if (AEInputCheckCurr(AEVK_A)) {
			dir.x--;
		}
		if (AEInputCheckCurr(AEVK_D)) {
			dir.x++;
		}
		if (AEInputCheckCurr(AEVK_W)) {
			dir.y++;
		}
		if (AEInputCheckCurr(AEVK_S)) {
			dir.y--;
		}

		player.input = dir;
		player.dir = dir;
		return dir.x || dir.y;
	}

	bool PlayerJump(Character& player) {
		player.zVel = GRAVITY * (f32)AEFrameRateControllerGetFrameTime() + player.zVel;

		if (AEInputCheckTriggered(AEVK_SPACE) && player.pObjInst->GetPosZ() == 0) {
			player.zVel = sqrt(2 * -GRAVITY * (JUMP_HEIGHT));
		}

		player.pObjInst->GetPosZ() = player.zVel * (f32)AEFrameRateControllerGetFrameTime() + player.pObjInst->GetPosZ();
		if (player.pObjInst->GetPosZ() < 0)
			player.pObjInst->GetPosZ() = 0;

		return player.pObjInst->GetPosZ() > 0;
	}

	bool ButtonClick(s32 mouseX, s32 mouseY, float buttonX, float buttonY) {
		AEInputGetCursorPosition(&mouseX, &mouseY);
		if (AEInputCheckReleased(AEVK_LBUTTON) && mouseX <= static_cast<s32>(buttonX + 100.f) && mouseX >= static_cast<s32>(buttonX)
			&& mouseY <= static_cast<s32>(buttonY + 50.f) && mouseY >= static_cast<s32>(buttonY))
		{
			std::cout << "true\n";
			return true;
		}
		return false;
	}
}