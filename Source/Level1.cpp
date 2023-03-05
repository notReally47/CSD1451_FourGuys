/*!***********************************************************************
  \file   Level1.cpp
  \authors

  \brief
  This file contains the implementation of the level 1
  \copyright
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "PCH.h"
#include "InputManager.h"
#include "CollisionDetectionManager.h"
#include "FileManager.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace Level1
{
	/*DEFINES*/
	const static std::string level_number = "01";
	const static f32 MIN_CAM_HEIGHT = -65.f;

	OM::Character player;
	FM::Import ImportData;
	FM::Export ExportData;
	OM::Character *sCHARACTER;
	OM::Object bubble;
	OM::ObjectInst objInst[1];

	/*!***********************************************************************
	  \brief Load level 1 data

	*************************************************************************/
	void Level1_Load()
	{
		ImportData.vO = *ImportData.Load_Shape_From_YAML(level_number);
		ImportData.vOI = *ImportData.Load_Transform_From_YAML(level_number);
		sCHARACTER = ImportData.Load_Player_Stats_From_YAML(level_number);
		bubble.type = Enum::TYPE::BUBBLE;
	}
	/*!***********************************************************************
	  \brief Initialise level 1

	*************************************************************************/
	void Level1_Init()
	{
		/*CREATE PLAYER*/
		FM::Init_Player(&ImportData.vOI[0], sCHARACTER, player);

		/*SCALE OBJECTS*/
		FM::Option_Change(ImportData.vOI);

		/*DO NOT DELETE*/

		// for (auto& it : vOBJ_INST) {
		// AEVec2 a{ it.GetPosY() + (it.GetPosX() / 2.0f ), it.GetPosY() - (it.GetPosX() / 2.0f) };
		// it.GetPosX() = a.x;
		// it.GetPosY() = a.y;
		//}

		/*Extract Using Vector vOBJ_INST & player*/
		ExportData.Extract_Transform_Data_Out(ImportData.vOI, player, level_number);
		// add bubble mesh and texture
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
		bubble.pMesh = AEGfxMeshEnd();
		objInst[0].pObj = &bubble;
		objInst[0].flag = Enum::FLAG::IDLE;
		objInst[0].tex_offset = {.0f, .0f};
		objInst[0].transform = {150.f, .0f, .0f + .0f,
								.0f, 150.0f, 0.f,
								.0f, .0f, .0f};
		objInst[0].pObj->pTex = AEGfxTextureLoad("../Resource/Textures/bubble.jpg");
	}
	/*!***********************************************************************
	  \brief Update player and objects based on input and collisions

	*************************************************************************/
	void Level1_Update()
	{
		using namespace Enum;
		/*HANDLE INPUT*/
		IM::ExitGame(GSM::next);

		/*SET PLAYER BIT FLAG FOR MOVEMENT OR JUMPING*/
		unsigned long &flag{player.pObjInst->flag};
		flag = (IM::PlayerJump(player)) ? flag | JUMPING : flag & ~JUMPING;
		flag = (IM::PlayerMovement(player)) ? flag | ACTIVE : flag & ~ACTIVE;

		/*MOVEMENT*/
		// PhysicsHandler::Move::MoveCharacter();
		player.MoveCharacter();

		// check if player if near portrait
		for (size_t i{0}; i < ImportData.vOI.size(); i++)
		{
			if (ImportData.vOI[i].pObj->type == PORTRAIT || ImportData.vOI[i].pObj->type == LANDSCAPE)
			{
				ImportData.vOI[i].flag = (CDM::GetDistance(ImportData.vOI[i].GetPos().x, ImportData.vOI[i].GetPos().y, ImportData.vOI[i].transform.m[0][0], ImportData.vOI[i].transform.m[1][1], player.pObjInst->GetPos().x, player.pObjInst->GetPos().y) < 10.0) ? static_cast<unsigned long>(GLOW) : IDLE;
			}
			if (ImportData.vOI[i].flag == GLOW)
			{
				objInst[0].transform.m[0][2] = ImportData.vOI[i].GetPos().x;
				objInst[0].transform.m[1][2] = ImportData.vOI[i].GetPos().y;
				objInst[0].GetPosZ() = ImportData.vOI[i].GetPosZ() + 100.0f;
				objInst[0].flag = ACTIVE;
			}
			if (ImportData.vOI[i].pObj->type == WALL && ImportData.vOI[i].flag & DOOR)
			{
				if (CDM::GetDistance(ImportData.vOI[i].GetPos().x + ImportData.vOI[i].GetPosZ(), ImportData.vOI[i].GetPos().y + ImportData.vOI[i].GetPosZ(), ImportData.vOI[i].transform.m[0][0], ImportData.vOI[i].transform.m[1][1], player.pObjInst->GetPos().x, player.pObjInst->GetPos().y) == 0.0)
				{
					ImportData.vOI[i].flag |= static_cast<unsigned long>(ACTIVE);
					std::cout << "Door is unlocked" << ImportData.vOI[i].flag << std::endl;
					IM::PlayerInteractionF(player, ImportData.vOI, i);
				}
			}
		}

		if (objInst[0].flag == ACTIVE)
			objInst[0].GetElapsed() += GSM::gameTime;
		if (objInst[0].GetElapsed() > 3.f)
		{
			objInst[0].flag = IDLE;
			objInst[0].GetElapsed() = {};
		}

		/*COLLISIONS*/
		// TODO: Collision

		/*ANIMATION*/
		AEGfxSetCamPosition(0.f, max(player.pObjInst->GetPos().y, MIN_CAM_HEIGHT));
	}
	/*!***********************************************************************
	  \brief Render game objects

	*************************************************************************/
	void Level1_Draw()
	{
		OM::RenderSettings();
		// Initialise i to 1 to skip player
		for (int i{1}; i < ImportData.vOI.size(); i++)
		{
			if (ImportData.vOI[i].flag & Enum::FLAG::GLOW)
				ImportData.vOI[i].RenderGlow();
			ImportData.vOI[i].RenderObject();
		}
		player.AnimateCharacter();
		if (objInst[0].flag == Enum::FLAG::ACTIVE)
			objInst[0].RenderObject();
	}
	/*!***********************************************************************
	  \brief Free level 1 data

	*************************************************************************/
	void Level1_Free()
	{
		for (size_t i{0}; i < ImportData.vO.size(); i++)
			AEGfxMeshFree(ImportData.vO[i].pMesh);
		AEGfxMeshFree(bubble.pMesh);
		ImportData.vOI.clear();
	}
	/*!***********************************************************************
	  \brief Unload level 1 data

	*************************************************************************/
	void Level1_Unload()
	{
		for (size_t i{0}; i < ImportData.vO.size(); i++)
			AEGfxTextureUnload(ImportData.vO[i].pTex);
		AEGfxTextureUnload(bubble.pTex);
		ImportData.vO.clear();
	}
}
