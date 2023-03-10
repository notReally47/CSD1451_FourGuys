#include "InputHandler.h"
#include "AEEngine.h"
#include "GSM.h"
#include "Enum.h"
#include <iostream>
#include "GameObjects.h"

namespace InputHandler {
	const static f32 GRAVITY		= -1000.f;
	const static f32 JUMP_HEIGHT	= 50.f;

	using namespace GameObjects;

	void MoveObject(float& obj1Y, float& obj1X) {
		if (AEInputCheckCurr(AEVK_1))
			AEGfxSetBlendMode(AE_GFX_BM_NONE);
		else if (AEInputCheckCurr(AEVK_2))
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		else if (AEInputCheckCurr(AEVK_3))
			AEGfxSetBlendMode(AE_GFX_BM_ADD);

		// Object 1 Control
		if (AEInputCheckCurr(AEVK_UP))
			obj1Y += 3.0f;
		else if (AEInputCheckCurr(AEVK_DOWN))
			obj1Y -= 3.0f;

		if (AEInputCheckCurr(AEVK_LEFT))
			obj1X -= 3.0f;
		else if (AEInputCheckCurr(AEVK_RIGHT))
			obj1X += 3.0f;
	}

	void ChangeTexture(float& objtexX, float& objtexY) {
		// Texture offset
		if (AEInputCheckCurr(AEVK_L))
			objtexX -= 0.01f;
		else if (AEInputCheckCurr(AEVK_J))
			objtexX += 0.01f;

		if (AEInputCheckCurr(AEVK_I))
			objtexY += 0.01f;
		else if (AEInputCheckCurr(AEVK_K))
			objtexY -= 0.01f;
	}

	void MoveCamera(float& camX, float& camY) {
		// Move the camera
		AEGfxGetCamPosition(&camX, &camY);
		if (AEInputCheckCurr(AEVK_W))
			AEGfxSetCamPosition(camX, camY + 2);
		else if (AEInputCheckCurr(AEVK_S))
			AEGfxSetCamPosition(camX, camY - 2);

		AEGfxGetCamPosition(&camX, &camY);
		if (AEInputCheckCurr(AEVK_A))
			AEGfxSetCamPosition(camX - 2, camY);
		else if (AEInputCheckCurr(AEVK_D))
			AEGfxSetCamPosition(camX + 2, camY);
	}

	void ExitGame(int& next) {
		if (AEInputCheckTriggered(AEVK_ESCAPE))
			next = Enum::GS_QUIT;
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

	bool ButtonClick(float buttonX, float buttonY)
	{
		s32 mouseX, mouseY;
		AEInputGetCursorPosition(&mouseX, &mouseY);
		if (AEInputCheckReleased(AEVK_LBUTTON) && mouseX <= static_cast<s32>(AEGetWindowWidth() / 2 + (buttonX + 50.f)) && mouseX >= static_cast<s32>(AEGetWindowWidth() / 2 + (buttonX - 50.f)) && mouseY <= static_cast<s32>(AEGetWindowHeight() / 2 + (buttonY + 25.f)) && mouseY >= static_cast<s32>(AEGetWindowHeight() / 2 + (buttonY - 25.f)))
			return true;
		return false;
	}
	void PlayerInteractionF(Character &player)
	{
		if (AEInputCheckCurr(AEVK_F))
		{
			player.pObjInst->GetPosX() = 0.f;
			player.pObjInst->GetPosY() = 0.f;
		}
	}

}