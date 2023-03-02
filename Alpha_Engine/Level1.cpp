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
		stairObj.height = 8.f * 64.f / 7.f;
		stairObj.type = Enum::PLATFORM;
		stairObj.pTex = AEGfxTextureLoad("../Assets/Textures/ianr1.png");

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
		player.speed = 100.f;
		player.spriteIteration = 0;
		player.zVel = 0;

		for (int i = 0; i < x_size; i++) {
			for (int j = 0; j < y_size; j++) {
				tiles[i][j].flag = 1;
				tiles[i][j].pObj = &tileObj;
				tiles[i][j].tex_offset = AEVec2{ 0, 0 };
				tiles[i][j].transform = AEMtx33{ tileObj.width * 2.f, 0, (i * tileObj.width),
													0, tileObj.length + tileObj.height, (j * tileObj.length),
													0, 0, 0 };

				//wall[i][j] .flag		= 1;
				//wall[i][j].pObj			= &tileObj;
				//wall[i][j].tex_offset	= AEVec2{ 0, 0 };
				//wall[i][j].transform	= AEMtx33{	scalex, 0, i * scalex,
				//									0, scaley, j * scaley,
				//									0, 0, 0	};
			}
		}

		stair.flag = 1;
		stair.pObj = &stairObj;
		stair.tex_offset = AEVec2{ 0, 0 };
		stair.transform = AEMtx33{ stairObj.width * 2.f, 0, 128.f,
									0, stairObj.length * 2.f + stairObj.height, 128.f,
									0, 0, 10 };
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

		bool a, b, c;
		f32* xPos = &player.pObjInst.transform.m[0][2];
		f32* yPos = &player.pObjInst.transform.m[1][2];
		f32* zPos = &player.pObjInst.transform.m[2][2];

		for (int i = x_size - 1; i >= 0; i--) {
			for (int j = y_size - 1; j >= 0; j--) {
				a = CollisionHandler::SAT_Collision(player.pObjInst, tiles[i][j], depthXY, normalXY, GameObjects::GetVerticesXY);
				b = CollisionHandler::SAT_Collision(player.pObjInst, tiles[i][j], depthXY, normalXY, GameObjects::GetVerticesXZ);
				c = CollisionHandler::SAT_Collision(player.pObjInst, tiles[i][j], depthYZ, normalYZ, GameObjects::GetVerticesYZ);
				if (a && b && c) {
					AEVec2Scale(&normalYZ, &normalYZ, depthYZ);
					//*yPos -= normalXY.x;
					*zPos -= normalXY.y;
				}
			}
		}


		a = CollisionHandler::SAT_Collision(player.pObjInst, stair, depthXY, normalXY, GameObjects::GetVerticesXY);
		b = CollisionHandler::SAT_Collision(player.pObjInst, stair, depthXY, normalXY, GameObjects::GetVerticesXZ);
		c = CollisionHandler::SAT_Collision(player.pObjInst, stair, depthYZ, normalYZ, GameObjects::GetVerticesYZ);

		if (a) {
			//AEVec2Scale(&normalXY, &normalXY, depthXY);
			//*xPos -= normalXY.x;
			//*yPos -= normalXY.y;
			//else { 
			//	AEVec2Scale(&normalYZ, &normalYZ, depthYZ);
			//	*yPos -= normalXY.x;
			//	*zPos -= normalXY.y;
			//}
			//AEVec2Scale(&normalXY, &normalXY, depthXY);
			//*xPos -= normalXY.x;
			//*yPos -= normalXY.y;
			//AEVec2Scale(&normalYZ, &normalYZ, depthYZ);
			//*yPos -= normalYZ.x;
			//*zPos -= normalYZ.y;
			//AEVec2* line = new AEVec2[2];
			//line[0] = AEVec2{ stair.transform.m[0][2] - stair.pObj->width / 2, stair.transform.m[1][2] - stair.pObj->length / 2 }; //bot right
			//line[1] = AEVec2{ stair.transform.m[0][2] + stair.pObj->width / 2, stair.transform.m[1][2] - stair.pObj->length / 2 }; //bot left
			//AEVec2 pos = { *xPos, *yPos + player.pObjInst.pObj->height / 2.f };

			//f32 dist = GameObjects::distanceFromAEVec2ToLine(pos, line);
			//*zPos = dist / 2.f;
			//delete[] line;
			//std::cout << dist << std::endl;
		}
		//else *zPos = 0;


		AEGfxSetCamPosition(0.f, player.pObjInst.transform.m[1][2]);
	}

	void Level1_Draw() {
		GameObjects::RenderSettings();
		for (int i = x_size - 1; i >= 0; i--) {
			for (int j = y_size - 1; j >= 0; j--) {
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