/*!***********************************************************************
  \file   MainMenu.cpp
  \authors

  \brief
  This file contains the implementation of the main menu

  \copyright
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/
#include "PCH.h"
#include "InputManager.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace Menu
{
	AEGfxVertexList *pMesh1{0}, *pMesh2{0}, *pMesh3{0};
	OM::Object button, background;
	OM::ObjectInst objInst[4];
	char strBuffer[10];
	char strBuffer2[10];
	char strBuffer3[10];

	/*!***********************************************************************
	  \brief Loads the assets for the main menu

	*************************************************************************/
	void Menu_Load()
	{
		button.type = Enum::TYPE::BUTTON;
		background.type = Enum::TYPE::BACKGROUND;
	}

	/*!***********************************************************************
	  \brief Initialises the main menu

	*************************************************************************/
	void Menu_Init()
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
		button.pMesh = background.pMesh = AEGfxMeshEnd();
		for (int i = 0; i < 3; i++)
		{
			objInst[i].pO = &button;
			objInst[i].flag = Enum::FLAG::IDLE;
			objInst[i].texture = {.0f, .0f};
			objInst[i].transf = {100.0f, .0f, .0f + .0f,
									.0f, 50.0f, i * 100.f - 100.f,
									.0f, .0f, .0f};
			objInst[i].pO->pTex = AEGfxTextureLoad("../Resource/Textures/button.png");
		}

		objInst[3].pO = &background;
		objInst[3].flag = Enum::FLAG::IDLE;
		objInst[3].texture = {.0f, .0f};
		objInst[3].transf = {static_cast<f32>(AEGetWindowWidth()), .0f, .0f,
								.0f, static_cast<f32>(AEGetWindowHeight()), 0.f,
								.0f, .0f, .0f};
		objInst[3].pO->pTex = AEGfxTextureLoad("../Resource/Textures/spellbook.png");

		memset(strBuffer, 0, 10 * sizeof(char));
		sprintf_s(strBuffer, "Start");
		memset(strBuffer2, 0, 10 * sizeof(char));
		sprintf_s(strBuffer2, "Option");
		memset(strBuffer3, 0, 10 * sizeof(char));
		sprintf_s(strBuffer3, "Exit");

		AESysSetWindowTitle("Main Menu");
	}

	/*!***********************************************************************
	  \brief Checks for input and changes the state of the main menu

	*************************************************************************/
	void Menu_Update()
	{
		/*UPDATE LOGIC*/
		IM::ExitGame(GSM::next);
		if (IM::ButtonClick(objInst[0].GetPos().x, objInst[0].GetPos().y))
		{
			GSM::next = GAME_STATES::LEVEL1;
			// option = !option;
		}
		if (IM::ButtonClick(objInst[2].GetPos().x, objInst[2].GetPos().y))
		{
			GSM::next = GAME_STATES::QUIT;
		}
	}

	/*!***********************************************************************
	  \brief Renders the main menu buttons

	*************************************************************************/
	void Menu_Draw()
	{
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		OM::RenderSettings();
		objInst[3].RenderObject();
		// for (int i{}; i < (sizeof(objInst) / sizeof(objInst[0])); i++)
		for (int i = 0; i < 3; i++)
			objInst[i].RenderObject();
		// }

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(GSM::fontId, strBuffer3, OM::GetScreenXPercentage(objInst[0].GetPos().x - objInst[0].transf.m[0][0] / 4.f), OM::GetScreenYPercentage(objInst[0].GetPos().y), 1.0f, 1.0f, 1.f, 1.f);
		AEGfxPrint(GSM::fontId, strBuffer2, OM::GetScreenXPercentage(objInst[1].GetPos().x - objInst[1].transf.m[0][0] / 4.f), OM::GetScreenYPercentage(objInst[1].GetPos().y), 1.0f, 1.0f, 1.f, 1.f);
		AEGfxPrint(GSM::fontId, strBuffer, OM::GetScreenXPercentage(objInst[2].GetPos().x - objInst[2].transf.m[0][0] / 4.f), OM::GetScreenYPercentage(objInst[2].GetPos().y), 1.0f, 1.0f, 1.f, 1.f);
	}

	/*!***********************************************************************
	  \brief Frees the main menu meshes

	*************************************************************************/
	void Menu_Free()
	{
		AEGfxMeshFree(button.pMesh);
	}

	/*!***********************************************************************
	  \brief Unloads the main menu textures

	*************************************************************************/
	void Menu_Unload()
	{
		AEGfxTextureUnload(button.pTex);
		AEGfxTextureUnload(background.pTex);
	}
}
