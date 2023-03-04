#include "Level1.h"
#include "AEEngine.h"
#include "InputHandler.h"
#include "GSM.h"
#include "Enum.h"
#include "PhysicsHandler.h"
#include "AnimationHandler.h"
#include "CollisionHandler.h"
#include <tuple>
#include <limits>
#include <iostream>

namespace Level1 {
	const int y_size = 5;
	const int x_size = 5;

	static bool collide = false;

	static GameObjects::Object		tileObj;
	static GameObjects::Object		playerObj;
	//static GameObjects::Object		wallObj;
	static GameObjects::Object		stairObj;

	static GameObjects::Character	player;
	static GameObjects::ObjectInst	playerObjInst;
	static GameObjects::ObjectInst	stair;
	static GameObjects::ObjectInst	tiles[5][5];
	//static GameObjects::ObjectInst	wall[5][5];

	void Level1_Load() {
		/*TILE OBJECT*/
		tileObj.width = 64.f;
		tileObj.length = 64.f;
		tileObj.height = 64.f / 7.f;
		tileObj.type = Enum::FLOOR;
		tileObj.pTex = AEGfxTextureLoad("../Assets/Textures/floor.png");

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
		/*TILE OBJECT END*/

		/*PLAYER OBJECT*/
		playerObj.width = 16.f;
		playerObj.length = 16.f;
		playerObj.height = 32.f;
		playerObj.type = Enum::PLAYER;
		playerObj.pTex = AEGfxTextureLoad("../Assets/Sprites/player.png");

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
		/*PLAYER OBJECT END*/

		/*WALL OBJECT*/
		//wallObj.width	= 32.f;
		//wallObj.length	= 128.f;
		//wallObj.height	= 128.f;
		//wallObj.type	= Enum::WALL;
		//wallObj.pTex	= AEGfxTextureLoad("../Assets/Textures/wall.png");

		//AEGfxMeshStart();
		//AEGfxTriAdd(
		//	-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		//	0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		//	-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		//AEGfxTriAdd(
		//	0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		//	0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		//	-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		//wallObj.pMesh = AEGfxMeshEnd();
		/*WALL OBJECT END*/

		/*STAIR OBJECT*/
		stairObj.width = 64.f;
		stairObj.length = 64.f;
		stairObj.height = 41.f;
		stairObj.type = Enum::PLATFORM;
		stairObj.pTex = AEGfxTextureLoad("../Assets/Textures/stairs.png");

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
		stairObj.pMesh = AEGfxMeshEnd();
		/*STAIR OBJECT END*/
	}

	void Level1_Init() {
		playerObjInst.flag = 1;
		playerObjInst.pObj = &playerObj;
		playerObjInst.tex_offset = AEVec2{ 0, 0 };
		playerObjInst.transform = AEMtx33{ playerObj.width * 2.f, 0, 0,
											0, playerObj.length + playerObj.height, 0,
											0, 0, 10 };
		/*
			[0][0] scale_x,		[0][1] 0(shearx),	[0][2] world x,
			[1][0] 0(sheary),	[1][1] scale_y,		[1][2] world y,
			[2][0] e,			[2][1] 0,			[2][2] world z
		*/

		player.dir = AEVec2{ 0, 0 };
		player.input = AEVec2{ 0, 0 };
		player.isJumping = false;
		player.isMoving = false;
		player.pObjInst = playerObjInst;
		player.rotation = 0.f;
		player.speed = 1.f;
		player.spriteIteration = 0;
		player.zVel = 0;

		for (int i = 0; i < x_size; i++) {
			for (int j = 0; j < y_size; j++) {
				tiles[i][j].flag = 1;
				tiles[i][j].pObj = &tileObj;
				tiles[i][j].tex_offset = AEVec2{ 0, 0 };
				tiles[i][j].transform = AEMtx33{ tileObj.width * 2.f, 0, (f32)i,
												0, tileObj.length + tileObj.height, (f32)j,
												0, 0, 0 };

				//wall[i][j] .flag		= 1;
				//wall[i][j].pObj			= &tileObj;
				//wall[i][j].tex_offset	= AEVec2{ 0, 0 };
				//wall[i][j].transform	= AEMtx33{	width * 2,	0,					i,
				//									0,			length + height,	j,
				//									0,			0,					0	};
			}
		}

		stair.flag = 1;
		stair.pObj = &stairObj;
		stair.tex_offset = AEVec2{ 0, 0 };
		stair.transform = AEMtx33{ stairObj.width * 2.f, 0, 2,
									0, stairObj.length + stairObj.height, 2,
									0, 0, 10 };
	}

	void Level1_Update() {
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);

		//player.isJumping = InputHandler::PlayerJump(player);
		player.pObjInst.flag = (InputHandler::playerMovement(player)) ? GameObjects::FLAG_ACTIVE : GameObjects::FLAG_INACTIVE;

		/*MOVEMENT*/
		PhysicsHandler::MovePlayer(player);

		/*COLLISION*/
		//CollisionHandler::GetEdges(stair);

		//std::pair<f32, f32> line = CollisionHandler::CalcLine(stair.bot[0], stair.bot[1]);
		//AEVec2 playerPos = { player.pObjInst.transform.m[0][2], player.pObjInst.transform.m[1][2] };
		//CollisionHandler::CheckSide1(line.first, line.second, playerPos);

		if (CollisionHandler::PointInCell(stair, player.pObjInst)) {
			CollisionHandler::GetEdges(stair);
			AEVec2 p = { player.pObjInst.transform.m[0][2], player.pObjInst.transform.m[1][2] };
			player.pObjInst.transform.m[2][2] = (CollisionHandler::distanceFromAEVec2ToLine(p, stair.bot) - 1.5f) * 40.f;
		}
		else player.pObjInst.transform.m[2][2] = 0;
		AEGfxSetCamPosition(0.f, player.pObjInst.transform.m[1][2]);
	}

	void Level1_Draw() {
		GameObjects::RenderSettings();
		for (int i = x_size - 1; i >= 0; i--) {
			for (int j = y_size - 1; j >= 0; j--) {
				GameObjects::RenderObject(tiles[i][j]);
			}
		}
		//for (int i = 0; i < x_size; i++) {
		//	for (int j = 0; j < y_size; j++) {
		//		GameObjects::RenderObject(tiles[i][j]);
		//	}
		//}
		GameObjects::RenderObject(stair);
		AnimationHandler::AnimateCharacter(player);
	}

	void Level1_Free() {
		AEGfxMeshFree(tileObj.pMesh);
		AEGfxMeshFree(stairObj.pMesh);
		AEGfxMeshFree(playerObj.pMesh);
	}

	void Level1_Unload() {
		AEGfxTextureUnload(tileObj.pTex);
		AEGfxTextureUnload(stairObj.pTex);
		AEGfxTextureUnload(playerObj.pTex);
	}
}