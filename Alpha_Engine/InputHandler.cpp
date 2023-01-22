#include "InputHandler.h"
#include "AEEngine.h"
#include "GSM.h"
#include "Enum.h"
#include "GameObjects.h"

namespace InputHandler {
	using namespace GameObjects;
	void MoveObject(float &obj1Y, float &obj1X) {
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

	void ChangeTexture(float &objtexX, float &objtexY) {
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

	void MoveCamera(float &camX, float &camY) {
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

	void ExitGame(int &next) {
		if (AEInputCheckTriggered(AEVK_ESCAPE))
			next = Enum::GS_QUIT;
	}

	bool playerMovement(Character &player) {
		Vector dir = Vector{ 0,0 };
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
		player.direction = dir;
		return !(dir.x == 0 && dir.y == 0);
	}
}