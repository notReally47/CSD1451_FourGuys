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
	const static f32 MIN_CAM_HEIGHT = -65.f;
	OM::Object bubble;
	OM::ObjectInst objInst[1];
	FM::GameData GD;
	

	/*!***********************************************************************
	  \brief Load level 1 data

	*************************************************************************/
	void Level1_Load()
	{
		GD.LoadShapeFromFile();
		GD.LoadTransformFromFile();
		GD.LoadLayersFromFile();
		bubble.type = Enum::TYPE::BUBBLE;
	}
	/*!***********************************************************************
	  \brief Initialise level 1

	*************************************************************************/
	void Level1_Init()
	{
		/*CREATE PLAYER*/
		GD.LoadPlayerStatsFromFile();

		/*SCALE OBJECTS*/
		//GD.Option_Change();

		/*tmp.head = &GD.vOI[83].flag;
		tmp.next = &GD.vOI[90].flag;*/

		/*DO NOT DELETE*/

		// for (auto& it : vOBJ_INST) {
		// AEVec2 a{ it.GetPosY() + (it.GetPosX() / 2.0f ), it.GetPosY() - (it.GetPosX() / 2.0f) };
		// it.GetPosX() = a.x;
		// it.GetPosY() = a.y;
		//}

		/*Extract Using Vector vOBJ_INST & player*/
		GD.ExtractTransformToFile();
	
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
		objInst[0].pO = &bubble;
		objInst[0].flag = Enum::FLAG::IDLE;
		objInst[0].texture = {.0f, .0f};
		objInst[0].transf = {150.f, .0f, .0f + .0f,
								.0f, 150.0f, 0.f,
								.0f, .0f, .0f};
		objInst[0].pO->pTex = AEGfxTextureLoad("../Resource/Textures/bubble.jpg");
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
		unsigned long &flag{GD.player.pOI->flag};
		flag = (IM::PlayerJump(GD.player)) ? flag | JUMPING : flag & ~JUMPING;
		flag = (IM::PlayerMovement(GD.player)) ? flag | ACTIVE : flag & ~ACTIVE;

		/*MOVEMENT*/
		// PhysicsHandler::Move::MoveCharacter();
		GD.player.MoveCharacter();

		// check if player if near portrait
		for (size_t i{0}; i < GD.vOI.size(); i++)
		{
			if (GD.vOI[i].pO->type == PORTRAIT || GD.vOI[i].pO->type == LANDSCAPE)
			{
				GD.vOI[i].flag = (CDM::GetDistance(GD.vOI[i].GetPos().x, GD.vOI[i].GetPos().y, GD.vOI[i].transf.m[0][0], GD.vOI[i].transf.m[1][1], GD.player.pOI->GetPos().x, GD.player.pOI->GetPos().y) < 10.0) ? static_cast<unsigned long>(GLOW) : IDLE;
			}
			if (GD.vOI[i].flag == GLOW)
			{
				objInst[0].transf.m[0][2] = GD.vOI[i].GetPos().x;
				objInst[0].transf.m[1][2] = GD.vOI[i].GetPos().y;
				objInst[0].GetPosZ() = GD.vOI[i].GetPosZ() + 100.0f;
				objInst[0].flag = ACTIVE;
				// * tmp.next |= ACTIVE;
			}
			if (GD.vOI[i].pO->type == WALL && GD.vOI[i].flag & DOOR)
			{
				if (CDM::GetDistance(GD.vOI[i].GetPos().x + GD.vOI[i].GetPosZ(), GD.vOI[i].GetPos().y + GD.vOI[i].GetPosZ(), GD.vOI[i].transf.m[0][0], GD.vOI[i].transf.m[1][1], GD.player.pOI->GetPos().x, GD.player.pOI->GetPos().y) == 0.0)
				{
					GD.vOI[i].flag |= static_cast<unsigned long>(ACTIVE);
					//std::cout << "Door is unlocked" << ImportData.vOI[i].flag << std::endl;
					IM::PlayerInteractionF(GD.player, GD.vOI, i);
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
		AEGfxSetCamPosition(0.f, max(GD.player.pOI->GetPos().y, MIN_CAM_HEIGHT));
	}
	/*!***********************************************************************
	  \brief Render game objects

	*************************************************************************/
	void Level1_Draw()
	{
		OM::RenderSettings();
		// Initialise i to 1 to skip player
		for (int i{1}; i < GD.vOI.size(); i++)
		{
			if (GD.vOI[i].flag & Enum::FLAG::GLOW)
				GD.vOI[i].RenderGlow();
			GD.vOI[i].RenderObject();
		}
		GD.player.AnimateCharacter();
		if (objInst[0].flag == Enum::FLAG::ACTIVE)
			objInst[0].RenderObject();
	}
	/*!***********************************************************************
	  \brief Free level 1 data

	*************************************************************************/
	void Level1_Free()
	{
		for (size_t i{0}; i < GD.vO.size(); i++)
			AEGfxMeshFree(GD.vO[i].pMesh);
		AEGfxMeshFree(bubble.pMesh);
		GD.vOI.clear();
	}
	/*!***********************************************************************
	  \brief Unload level 1 data

	*************************************************************************/
	void Level1_Unload()
	{
		for (size_t i{0}; i < GD.vO.size(); i++)
			AEGfxTextureUnload(GD.vO[i].pTex);
		AEGfxTextureUnload(bubble.pTex);
		GD.vO.clear();
	}
}
