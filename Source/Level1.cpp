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
	using enum TYPE;
	using enum LAYER;

	/*DEFINES*/
	const static f32 MIN_CAM_HEIGHT = -65.f;
	//std::vector<OM::ObjectInst> tmp;
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
		bubble.type = BUBBLE;
	}
	/*!***********************************************************************
	  \brief Initialise level 1

	*************************************************************************/
	void Level1_Init()
	{
		/*CREATE PLAYER*/
		GD.LoadPlayerStatsFromFile();

		/*SCALE OBJECTS*/
		GD.OptionChange();
		//GD.ExtractTransformToFile();


		/*DO NOT DELETE*/

		// for (auto& it : vOBJ_INST) {
		// AEVec2 a{ it.GetPosY() + (it.GetPosX() / 2.0f ), it.GetPosY() - (it.GetPosX() / 2.0f) };
		// it.GetPosX() = a.x;
		// it.GetPosY() = a.y;
		//}
/*		tmp.push_back(GD.vOI[0]);
		for (const auto& iter : GD.vOL)
		{
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 6; j++)
				{
					OM::ObjectInst tamp;
					switch (iter.data[i * 6 + j])
					{
					case GRID::TILE:
						tamp.pO = &GD.vO[1];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { .0f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j),
										.0f, 148.0f, -126.0f * (i),
										.0f, .0f, .0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::WBRIDGEL:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 0.f / 9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j)+40.0f,
										.0f, 288.0f, -126.0f * (i)-40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::WDOORL:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 1.f/9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j)+40.0f,
										.0f, 288.0f, -126.0f * (i)-40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f};
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::WCOLUMNL:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 2.f / 9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j)+40.0f,
										.0f, 288.0f, -126.0f * (i)-40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::WPLAINL:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 3.f / 9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j) + 40.0f,
										.0f, 288.0f, -126.0f * (i) - 40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;

					case GRID::WCORNER:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 4.f / 9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j)+40.0f,
										.0f, 288.0f, -126.0f * (i)-40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::WPLAINR:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 5.f / 9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j)+40.0f,
										.0f, 288.0f, -126.0f * (i)-40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::WCOLUMNR:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 6.f / 9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j)+40.0f,
										.0f, 288.0f, -126.0f * (i)-40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::WDOORR:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 7.f / 9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j)+40.0f,
										.0f, 288.0f, -126.0f * (i)-40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::WBRIDGER:
						tamp.pO = &GD.vO[2];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 8.f / 9.f, .0f };
						tamp.transf = { 256.0f, .0f, 126.0f * (j)+40.0f,
										.0f, 288.0f, -126.0f * (i)-40.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::STAIRSL:
						tamp.pO = &GD.vO[6];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 0.f / 21.f, .0f };
						tamp.transf = { 541.0f, .0f, 126.0f * (j)-165.0f,
										.0f, 422.0f, -126.0f * (i)+160.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::STAIRSR:
						tamp.pO = &GD.vO[6];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 20.f / 21.f, .0f };
						tamp.transf = { 541.0f, .0f, 126.0f * (j)-160.0f,
										.0f, 422.0f, -126.0f * (i)+165.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::BRIDGER:
						tamp.pO = &GD.vO[7];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 0.f / 4.f, .0f };
						tamp.transf = { 190.0f, .0f, 126.0f * (j) - 10.0f,
										.0f, 101.0f, -126.0f * (i) + 10.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::BROKENR:
						tamp.pO = &GD.vO[7];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 1.f / 4.f, .0f };
						tamp.transf = { 190.0f, .0f, 126.0f * (j)-10.0f,
										.0f, 101.0f, -126.0f * (i)+10.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::BROKENL:
						tamp.pO = &GD.vO[7];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 2.f / 4.f, .0f };
						tamp.transf = { 190.0f, .0f, 126.0f * (j)-10.0f,
										.0f, 101.0f, -126.0f * (i)+10.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::BRIDGEL:
						tamp.pO = &GD.vO[7];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { 3.f / 4.f, .0f };
						tamp.transf = { 190.0f, .0f, 126.0f * (j)-10.0f,
										.0f, 101.0f, -126.0f * (i)+10.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::VERTICAL:
						tamp.pO = &GD.vO[4];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { .0f / 4.f, .0f/ 5.f };
						tamp.transf = { 77.0f, .0f, 126.0f * (j)-140.0f,
										.0f, 127.0f, -126.0f * (i)+70.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;
					case GRID::HORIZONTAL:
						tamp.pO = &GD.vO[5];
						tamp.layer = iter.layer;
						tamp.flag = 0;
						tamp.texture = { .0f / 4.f, .0f / 5.f };
						tamp.transf = { 93.0f, .0f, 126.0f * (j)-140.0f,
										.0f, 105.0f, -126.0f * (i)+70.0f,
										.0f, .0f, static_cast<f32>(iter.layer - TILE) * 155.0f };
						tamp.pair = nullptr;
						tmp.push_back(tamp);
						break;

					}


				}
		}


		//Extract Using Vector vOBJ_INST & player
		GD.vOI = tmp;
		GD.SaveProgress();
	
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
		unsigned short& flag{GD.player.pOI->flag};
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
			objInst[0].SetCounter(GSM::gameTime);
		if (objInst[0].GetCounter() > 3.f)
		{
			objInst[0].flag = IDLE;
			objInst[0].ResetCounter();
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
/*		for (int i{ 0 }; i < tmp.size(); i++)
		{
			tmp[i].RenderObject();
		}*/
			
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
