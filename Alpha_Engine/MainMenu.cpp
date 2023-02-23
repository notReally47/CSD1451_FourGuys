#include "MainMenu.h"
#include "AEEngine.h"
#include "InputHandler.h"
#include "GSM.h"
#include "Enum.h"
#include <iostream>

namespace MainMenu
{
	char strBuffer[10];
	char strBuffer2[10];
	char strBuffer3[10];
	using namespace GameObjects;
	Object button, slider, box;
	ObjectInst objInst[4];
	bool option{false};
	/*LOAD ASSETS*/
	void MainMenu_Load()
	{
		using namespace GameObjects;
		button.type = Enum::TYPE::BUTTON;
		slider.type = Enum::TYPE::BUTTON;
	}
	/*LOAD INITIAL DATA*/
	void MainMenu_Init()
	{
		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		// Saving the mesh (list of triangles) in pMesh
		button.pMesh = slider.pMesh = box.pMesh = AEGfxMeshEnd();

		for (int i = 0; i < 3; i++)
		{
			objInst[i].pObj = &button;
			objInst[i].flag = FLAG_INACTIVE;
			objInst[i].tex_offset = {.0f, .0f};
			objInst[i].transform = {100.0f, .0f, .0f + .0f,
									.0f, 50.0f, i * 100.f - 100.f,
									.0f, .0f, .0f};
			objInst[i].pObj->pTex = AEGfxTextureLoad("../Assets/Textures/images.png");
		}

		objInst[3].pObj = &slider;
		objInst[3].flag = FLAG_INACTIVE;
		objInst[3].tex_offset = {.0f, .0f};
		objInst[3].transform = {200.0f, .0f, .0f + .0f,
								.0f, 40.0f, 0.f,
								.0f, .0f, .0f};
		objInst[3].pObj->pTex = AEGfxTextureLoad("../Assets/Textures/slider.png");

		// memset(strBuffer, 0, 10 * sizeof(char));
		// sprintf_s(strBuffer, "Start");
		// memset(strBuffer2, 0, 10 * sizeof(char));
		// sprintf_s(strBuffer2, "Option");
		// memset(strBuffer3, 0, 10 * sizeof(char));
		// sprintf_s(strBuffer3, "Exit");

		AESysSetWindowTitle("Main Menu");
	}

	void MainMenu_Update()
	{
		using namespace Enum;
		/*UPDATE LOGIC*/

		if (option)
		{
			if (AEInputCheckTriggered(AEVK_ESCAPE))
				option = !option;
		}
		else
		{
			InputHandler::ExitGame(GSM::next);
			// for (int i{}; i < (sizeof(objInst) / sizeof(objInst[0])); i++)
			for (int i = 0; i < 3; i++)
			{
				if (InputHandler::buttonClick(objInst[i].transform.m[0][2], objInst[i].transform.m[1][2]))
				{
					// GSM::next = GAME_STATES::GS_LEVEL2;
					option = !option;
				}
				if (InputHandler::buttonClick(0.f, 375.f))
				{
					GSM::next = Enum::GS_QUIT;
				}
			}
		}
	}

	/*RENDERING*/
	void MainMenu_Draw()
	{
		if (option)
		{
			AEGfxSetBackgroundColor(1.0f, 1.0f, 1.0f);
			RenderSettings();
			RenderObject(objInst[3]);
		}
		else
		{
			AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
			RenderSettings();
			// for (int i{}; i < (sizeof(objInst) / sizeof(objInst[0])); i++)
			for (int i = 0; i < 3; i++)
				RenderObject(objInst[i]);
		}

		// AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		// AEGfxPrint(fontId, strBuffer, -0.055f, 0.3f, 2.0f, 0.0f, 0.f, 0.f);
		// AEGfxPrint(fontId, strBuffer2, -0.08f, -0.02f, 2.0f, 0.0f, 0.f, 0.f);
		// AEGfxPrint(fontId, strBuffer3, -0.05f, -0.35f, 2.0f, 0.0f, 0.0f, 0.0f);
	}

	/*CLEAN UP DATA (SAVE/RESET ETC)*/
	void MainMenu_Free()
	{
		AEGfxMeshFree(button.pMesh);
	}

	/*UNLOADS ASSETS*/
	void MainMenu_Unload()
	{
	}
}