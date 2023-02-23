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

	bool playerMovement(Character& player) {
		AEVec2 dir = AEVec2{};
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
		/*DEPRECIATED -> ISOMETRIC CONVERSION WILL BE IN A DIFFERENT PART OF THE CODE*/
		///*CONVERSION TO ISOMETRIC*/
		//player.dir.x = dir.x + dir.y;
		//player.dir.y = -0.5f * dir.x + 0.5f * dir.y;
		player.input = dir;
		player.dir = dir;
		return dir.x || dir.y;
	}

	bool PlayerJump(GameObjects::Character& player) {
		player.zVel = GRAVITY * (f32)AEFrameRateControllerGetFrameTime() + player.zVel;

		if (AEInputCheckTriggered(AEVK_SPACE) && player.pObjInst.transform.m[2][2] == 0) {
			player.zVel = sqrt(2 * -GRAVITY * (JUMP_HEIGHT));
		}

		player.pObjInst.transform.m[2][2] = player.zVel * (f32)AEFrameRateControllerGetFrameTime() + player.pObjInst.transform.m[2][2];
		if (player.pObjInst.transform.m[2][2] < 0)
			player.pObjInst.transform.m[2][2] = 0;

		return player.pObjInst.transform.m[2][2] > 0;
	}

	bool buttonClick(s32 mouseX, s32 mouseY, float buttonX, float buttonY) {
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