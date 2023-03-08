/*!***********************************************************************
  \file   Level2.cpp
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

namespace Level2
{
	/*DEFINES*/
	//const static std::string level_number = "01";
	const static f32 MIN_CAM_HEIGHT = -65.f;
	const static f32 LEVEL_HEIGHT = 80.f;

	//OM::Character player;
	//FM::Import ImportData;
	//FM::Export ExportData;
	//OM::Character* sCHARACTER;

	static OM::Object	tileObj;
	static OM::Object	playerObj;
	static OM::Object	stairObj;
	static OM::Object	wallLeftObj;
	static OM::Object	wallRightObj;

	static OM::Character	player;
	static OM::ObjectInst	pObjInst;

	static OM::ObjectInst walls[5][10];
	static OM::ObjectInst floors[5][5][5];
	static OM::ObjectInst stair;
	//static OM::ObjectInst layers[5][5][5];

	static bool isFalling{ false };
	static bool allowInput{ true };

	/*!***********************************************************************
	  \brief Load level 1 data

	*************************************************************************/
	void Level2_Load()
	{
		/*TILE OBJECT*/
		tileObj.width = 64.f;
		tileObj.length = 64.f;
		tileObj.height = 64.f / 7.f;
		tileObj.type = Enum::FLOOR;
		tileObj.pTex = AEGfxTextureLoad("../Resource/Textures/floor.png");

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
			0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,
			0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
		);
		tileObj.pMesh = AEGfxMeshEnd();


		/*PLAYER OBJECT*/
		playerObj.width = 16.f;
		playerObj.length = 16.f;
		playerObj.height = 32.f;
		playerObj.type = Enum::PLAYER;
		playerObj.pTex = AEGfxTextureLoad("../Resource/Textures/player.png");

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f / 8.0f,
			0.5f, -0.5f, 0xFFFF0000, 1.0f / 11.0f, 1.0f / 8.0f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			0.5f, 0.5f, 0xFFFF0000, 1.0f / 11.0f, 0.0f,
			0.5f, -0.5f, 0xFFFF0000, 1.0f / 11.0f, 1.0f / 8.0f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
		);
		playerObj.pMesh = AEGfxMeshEnd();

		/*STAIR OBJECT*/
		stairObj.width = 64.f;
		stairObj.length = 64.f;
		stairObj.height = LEVEL_HEIGHT;
		stairObj.type = Enum::PLATFORM;
		stairObj.pTex = AEGfxTextureLoad("../Resource/Textures/stairSingle.png");

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
			0.5f, -0.5f, 0xFFFF0000, 1.f, 1.0f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			0.5f, 0.5f, 0xFFFF0000, 1.f, 0.0f,
			0.5f, -0.5f, 0xFFFF0000, 1.f, 1.0f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
		);
		stairObj.pMesh = AEGfxMeshEnd();

		/*STAIR OBJECT*/
		wallLeftObj.width = 64.f;
		wallLeftObj.length = 64.f / 7.f;
		wallLeftObj.height = LEVEL_HEIGHT;
		wallLeftObj.type = Enum::WALL;
		wallLeftObj.pTex = AEGfxTextureLoad("../Resource/Textures/wall.png");

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, 2.f / 7.f, 1.0f,
			0.5f, -0.5f, 0xFFFF0000, 3.f / 7.f, 1.0f,
			-0.5f, 0.5f, 0xFFFF0000, 2.f / 7.f, 0.0f
		);
		AEGfxTriAdd(
			0.5f, 0.5f, 0xFFFF0000, 3.f / 7.f, 0.0f,
			0.5f, -0.5f, 0xFFFF0000, 3.f / 7.f, 1.0f,
			-0.5f, 0.5f, 0xFFFF0000, 2.f / 7.f, 0.0f
		);
		wallLeftObj.pMesh = AEGfxMeshEnd();

		/*STAIR OBJECT*/
		wallRightObj.width = 64.f;
		wallRightObj.length = 64.f / 7.f;
		wallRightObj.height = LEVEL_HEIGHT;
		wallRightObj.type = Enum::WALL;
		wallRightObj.pTex = AEGfxTextureLoad("../Resource/Textures/wall.png");

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, 4.f / 7.f, 1.0f,
			0.5f, -0.5f, 0xFFFF0000, 5.f / 7.f, 1.0f,
			-0.5f, 0.5f, 0xFFFF0000, 4.f / 7.f, 0.0f
		);
		AEGfxTriAdd(
			0.5f, 0.5f, 0xFFFF0000, 5.f / 7.f, 0.0f,
			0.5f, -0.5f, 0xFFFF0000, 5.f / 7.f, 1.0f,
			-0.5f, 0.5f, 0xFFFF0000, 4.f / 7.f, 0.0f
		);
		wallRightObj.pMesh = AEGfxMeshEnd();
	}

	/*!***********************************************************************
	  \brief Initialise level 1

	*************************************************************************/
	void Level2_Init()
	{
		pObjInst.flag = Enum::FLAG::ACTIVE;
		pObjInst.pObj = &playerObj;
		pObjInst.tex_offset = AEVec2{ 0, 0 };
		pObjInst.transform = AEMtx33{ playerObj.width * 2.f, 0, 1,
											0, playerObj.length + playerObj.height, 1,
											0, 2.f, 0.f };
		player.dir = AEVec2{ 0, 0 };
		player.input = AEVec2{ 0, 0 };
		player.pObjInst = &pObjInst;
		player.spriteIteration = 0;
		player.zVel = 0;
		player.layer = 0;

		/*WALLS*/
		for (size_t j = 0; j < 5; j++)
		{
			for (size_t i = 0; i < 5; i++)
			{
				walls[j][i].pObj = &wallLeftObj;
				walls[j][i].transform = AEMtx33{ walls[j][i].pObj->width * 2.f, 0, (f32)i,
								0, walls[j][i].pObj->width + walls[j][i].pObj->height, (f32)4 + 3.f / 14.f,
								0, 0, LEVEL_HEIGHT * (f32)j };
			}

			for (size_t i = 5; i < 10; i++)
			{
				walls[j][i].pObj = &wallRightObj;
				walls[j][i].transform = AEMtx33{ walls[j][i].pObj->width * 2.f, 0, (f32)4 + 3.f / 14.f,
								0, walls[j][i].pObj->width + walls[j][i].pObj->height, (f32)i - 5,
								0, 0, LEVEL_HEIGHT * (f32)j };
			}
		}

		/*FLOORS*/
		for (size_t i = 0; i < 5; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				for (size_t k = 0; k < 5; k++)
				{
					if (j >= i) {
						floors[i][j][k].pObj = &tileObj;
						floors[i][j][k].transform = AEMtx33{ floors[i][j][k].pObj->width * 2.f, 0, (f32)j,
														0, floors[i][j][k].pObj->width + floors[i][j][k].pObj->height, (f32)k,
														0, 0, LEVEL_HEIGHT * (f32)i };
					}
					else floors[i][j][k].pObj = nullptr;
				}
			}
		}

		/*ADD SOME STAIRS*/
		floors[0][0][3].pObj = &stairObj;
		floors[0][0][3].direction = Enum::NORTH;
		floors[0][0][3].transform = AEMtx33{ floors[0][0][3].pObj->width * 2.f, 0, 0,
											0, floors[0][0][3].pObj->width + floors[0][0][3].pObj->height, 3,
											0, 0, 64.f / 7.f };

		floors[1][0][4].pObj = &tileObj;
		floors[1][0][4].direction = Enum::NONE;
		floors[1][0][4].transform = AEMtx33{ floors[1][0][4].pObj->width * 2.f, 0, 0.f,
											0, floors[1][0][4].pObj->width + floors[1][0][4].pObj->height, 4.f,
											0, 0, LEVEL_HEIGHT * 1.f };
	}

	/*!***********************************************************************
	  \brief Update player and objects based on input and collisions

	*************************************************************************/
	void Level2_Update()
	{
		unsigned int ground{};


		using namespace Enum;
		/*HANDLE INPUT*/
		IM::ExitGame(GSM::next);

		/*SET PLAYER BIT FLAG FOR MOVEMENT OR JUMPING*/
		unsigned long& flag{ player.pObjInst->flag };

		flag = (IM::PlayerJump(player)) ? flag | JUMPING : flag & ~JUMPING;
		flag = (IM::PlayerMovement(player)) ? flag | ACTIVE : flag & ~ACTIVE;
		player.MoveCharacter();

		/*Compare player position with grid data*/
		OM::ObjectInst* currTile = &floors[player.layer][(int)player.pObjInst->GetPosX()][(int)player.pObjInst->GetPosY()];

		/*if player is on a valid tile*/
		if (currTile->pObj == &stairObj) { // stairs
			if (CDM::PartialCollision(*player.pObjInst, *currTile, player.pObjInst->GetPosZ() >= LEVEL_HEIGHT * player.layer)) {
				player.zVel = player.HandleSlope(*currTile);
			}
			else {
				AEVec2 normal = CDM::CollisionResponse(*player.pObjInst, *currTile);
				player.pObjInst->GetPosX() += normal.x;
				player.pObjInst->GetPosY() += normal.y;
			}
		}
		/*if not fall*/
		else {
			for (int i = 0; i < 5; i++)
			{
				if (player.pObjInst->GetPosZ() >= i * LEVEL_HEIGHT)
					player.layer = i;
			}
			player.zVel += -25.f * (f32)AEFrameRateControllerGetFrameTime();
		}		

		/*check nearst ground to the player*/
		for (int i = 0; i <= player.layer; i++)
		{
			if (floors[i][(int)player.pObjInst->GetPosX()][(int)player.pObjInst->GetPosY()].pObj != nullptr)
				ground = i;
		}

		/*change zpos*/
		player.pObjInst->GetPosZ() += player.zVel;
		if (player.pObjInst->GetPosZ() < ground * LEVEL_HEIGHT && ground == player.layer) {
			player.pObjInst->GetPosZ() = ground * LEVEL_HEIGHT;
			player.zVel = 0;
		}
		//player.pObjInst->GetPosZ() = player.zVel + player.pObjInst->GetPosZ() < player.layer * LEVEL_HEIGHT ?
		//								player.layer * LEVEL_HEIGHT : player.zVel + player.pObjInst->GetPosZ();

		/*ANIMATION*/

		/*camera*/
		AEGfxSetCamPosition(0.f, max(player.pObjInst->GetPosZ(), MIN_CAM_HEIGHT));
	}

	/*!***********************************************************************
	  \brief Render game objects

	*************************************************************************/
	void Level2_Draw()
	{
		OM::RenderSettings();

		/*render walls first as background*/
		for (size_t j = 0; j < 5; j++)
		{
			for (int i = 9; i >= 0; i--)
			{
				if (walls[j][i].pObj)
					walls[j][i].RenderObject();
			}
		}

		for (int i = 0; i < 5; i++) // render levels from bottom up
		{
			/* render smaller x and y values last to overlap objects further away */
			for (int j = 4; j >= 0; j--)
			{
				for (int k = 4; k >= 0; k--)
				{
					if (floors[i][j][k].pObj)
						floors[i][j][k].RenderObject();
				}
			}
			/*if player is current level, render with the correct priority*/
			if (player.layer == i)
				player.AnimateCharacter();
		}


#ifdef DEBUG
		char buffer[256];
		sprintf_s(buffer, "layer: %d x: %.2f y: %.2f z: %f\n", player.layer, player.pObjInst->GetPosX(), player.pObjInst->GetPosY(), player.pObjInst->GetPosZ());
		//std::cout << "Player position: " << k << ' ' << j << ' ' << i << std::endl;
		AEGfxPrint(GSM::fontId, buffer, -.5f, -0.7f, 1.f, 1.f, 1.f, 1.f);
#endif
	}

	/*!***********************************************************************
	  \brief Free level 1 data

	*************************************************************************/
	void Level2_Free()
	{
		AEGfxMeshFree(tileObj.pMesh);
		AEGfxMeshFree(stairObj.pMesh);
		AEGfxMeshFree(playerObj.pMesh);
	}

	/*!***********************************************************************
	  \brief Unload level 1 data

	*************************************************************************/
	void Level2_Unload()
	{
		AEGfxTextureUnload(tileObj.pTex);
		AEGfxTextureUnload(stairObj.pTex);
		AEGfxTextureUnload(playerObj.pTex);
	}
}
