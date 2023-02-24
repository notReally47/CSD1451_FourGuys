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
		tileObj.width	= 64.f;
		tileObj.length	= 64.f;
		tileObj.height	= 37.f;
		tileObj.type	= Enum::FLOOR;
		tileObj.pTex	= AEGfxTextureLoad("../Assets/Textures/iso.png");

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
		playerObj.width		= 37.f;
		playerObj.length	= 37.f;
		playerObj.height	= 74.f;
		playerObj.type		= Enum::PLAYER;
		playerObj.pTex		= AEGfxTextureLoad("../Assets/Sprites/player.png");

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
		stairObj.width	= 128.f;
		stairObj.length = 128.f;
		stairObj.height = 80.f;
		stairObj.type	= Enum::PLATFORM;
		stairObj.pTex	= AEGfxTextureLoad("../Assets/Textures/stairs.png");

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
		playerObjInst.flag			= 1;
		playerObjInst.pObj			= &playerObj;
		playerObjInst.tex_offset	= AEVec2{ 0, 0 };
		playerObjInst.transform		= AEMtx33	{	30.f, 0, 0,
													0, 30.f, 0,
													0, 0, 0	};
		/*
		 	[0][0] scale_x,		[0][1] 0(shearx),	[0][2] world x,
			[1][0] 0(sheary),	[1][1] scale_y,		[1][2] world y,
			[2][0] e,			[2][1] 0,			[2][2] world z
		*/

		player.dir				= AEVec2{ 0, 0 };
		player.input			= AEVec2{ 0, 0 };
		player.isJumping		= false;
		player.isMoving			= false;
		player.pObjInst			= playerObjInst;
		player.rotation			= 0.f;
		player.speed			= 100.f;
		player.spriteIteration	= 0;
		player.zVel				= 0;

		for (int i = 0; i < x_size; i++) {
			for (int j = 0; j < y_size; j++) {
				tiles[i][j].flag		= 1;
				tiles[i][j].pObj		= &tileObj;
				tiles[i][j].tex_offset	= AEVec2{ 0, 0 };
				tiles[i][j].transform	= AEMtx33{	tileObj.width, 0, (i * tileObj.width),
													0, tileObj.length, (j * tileObj.length),
													0, 0, 0	};

				//wall[i][j] .flag		= 1;
				//wall[i][j].pObj			= &tileObj;
				//wall[i][j].tex_offset	= AEVec2{ 0, 0 };
				//wall[i][j].transform	= AEMtx33{	scalex, 0, i * scalex,
				//									0, scaley, j * scaley,
				//									0, 0, 0	};
			}
		}

		stair.flag			= 1;
		stair.pObj			= &stairObj;
		stair.tex_offset	= AEVec2{ 0, 0 };
		stair.transform		= AEMtx33{	stairObj.width, 0, 120.f,
										0, stairObj.length, 120.f,
										0, 0, 0	};
	}

	void Level1_Update() {
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);

		player.isJumping = InputHandler::PlayerJump(player);
		player.pObjInst.flag = (InputHandler::playerMovement(player)) ? GameObjects::FLAG_ACTIVE : GameObjects::FLAG_INACTIVE;

		/*MOVEMENT*/
		PhysicsHandler::MovePlayer(player);

		/*COLLISION*/
		f32 depthXY, depthYZ, depthXZ;
		AEVec2 normalXY, normalYZ, normalXZ;
		std::pair<f32, AEVec2> XY{ depthXY, normalXY }, YZ{ depthXY, normalYZ }, XZ{ depthXY, normalXZ }, response;

		bool a = CollisionHandler::SAT_Collision(player.pObjInst, stair, XY.first, XY.second, GameObjects::GetVerticesXY);
		bool b = CollisionHandler::SAT_Collision(player.pObjInst, stair, YZ.first, YZ.second, GameObjects::GetVerticesYZ);
		bool c = CollisionHandler::SAT_Collision(player.pObjInst, stair, XZ.first, XZ.second, GameObjects::GetVerticesXZ);

		if (a && b && c) {
			std::cout << player.pObjInst.transform.m[0][2] << '|' << player.pObjInst.transform.m[1][2] << '|' << player.pObjInst.transform.m[2][2] << std::endl;
			std::cout << stair.transform.m[0][2] << '|' << stair.transform.m[1][2] << '|' << stair.transform.m[2][2] << std::endl;

			response.first = static_cast<f32>((std::numeric_limits<float>::max)());
			int plane = 0;

			if (XY.first < response.first)
				response = XY, plane++;
			if (YZ.first < response.first)
				response = YZ, plane++;
			if (XZ.first < response.first)
				response = XZ, plane++;

			if (plane == 1) {
				f32* xPos = &player.pObjInst.transform.m[0][2];
				f32* yPos = &player.pObjInst.transform.m[1][2];

				AEVec2Scale(&response.second, &response.second, response.first);
				*xPos += response.second.x;
				*yPos += response.second.y;
			}

			else if (plane == 2) {
				f32* xPos = &player.pObjInst.transform.m[1][2];
				f32* yPos = &player.pObjInst.transform.m[2][2];

				AEVec2Scale(&response.second, &response.second, response.first);
				*xPos += response.second.x;
				*yPos += response.second.y;
			}

			else if (plane == 3) {
				f32* xPos = &player.pObjInst.transform.m[0][2];
				f32* yPos = &player.pObjInst.transform.m[2][2];

				AEVec2Scale(&response.second, &response.second, response.first);
				*xPos += response.second.x;
				*yPos += response.second.y;
			}
		}
		

		AEGfxSetCamPosition(0.f, player.pObjInst.transform.m[1][2]);
	}

	void Level1_Draw() {
		GameObjects::RenderSettings();

		for (int i = 0; i < x_size; i++) {
			for (int j = 0; j < y_size; j++) {
				GameObjects::RenderObject(tiles[i][j]);
			}
		}

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