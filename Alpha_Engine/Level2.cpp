#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"
#include "VectorMath.h"
#include "AnimationHandler.h"

namespace Level2 {
	using namespace GameObjects;
	Object leftWall, rightWall, cornerWall;
	Floor platform;
	Character player;
	
	f32 windowWidth, windowHeight;
	Object* objs[3]{ &leftWall, &rightWall, &cornerWall };

	void Level2_Load() {
		AE_ASSERT_MESG(player.obj.pTex = AEGfxTextureLoad("../Assets/Sprites/player.png"), "Failed to load texture");
		AE_ASSERT_MESG(cornerWall.pTex = AEGfxTextureLoad("../Assets/Textures/cornerwall.png"), "Failed to load texture");
		AE_ASSERT_MESG(leftWall.pTex = AEGfxTextureLoad("../Assets/Textures/leftwall0.png"), "Failed to load texture");
		AE_ASSERT_MESG(rightWall.pTex = AEGfxTextureLoad("../Assets/Textures/rightwall0.png"), "Failed to load texture");
		AE_ASSERT_MESG(platform.pTex[0] = AEGfxTextureLoad("../Assets/Textures/floor0.png"), "Failed to load texture");
		AE_ASSERT_MESG(platform.pTex[1] = AEGfxTextureLoad("../Assets/Textures/floor1.png"), "Failed to load texture");
		AE_ASSERT_MESG(platform.pTex[2] = AEGfxTextureLoad("../Assets/Textures/floor2.png"), "Failed to load texture");
		AE_ASSERT_MESG(platform.pTex[3] = AEGfxTextureLoad("../Assets/Textures/floor3.png"), "Failed to load texture");
		
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());
		//AEGfxSetPosition(-1.0f, -1.0f);
	}

	void Level2_Init() {

		/*CREATE CORNER WALL*/
		cornerWall.width = 64, cornerWall.height = 64, cornerWall.rotation = 0, cornerWall.pos.x = 0, cornerWall.pos.y = -16;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 1.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f, 0.5f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.5f
		);
		cornerWall.pMesh = AEGfxMeshEnd();
		
		/*CREATE LEFT WALL*/
		
		leftWall.width = 64, leftWall.height = 64, leftWall.rotation = 0, leftWall.pos.x = -112, leftWall.pos.y = -24;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 1.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f, 0.5f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.5f
		);
		leftWall.pMesh = AEGfxMeshEnd();
		
		/*CREATE RIGHT WALL*/
		
		rightWall.width = 64, rightWall.height = 64, rightWall.rotation = 0, rightWall.pos.x = 112, rightWall.pos.y = -24;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 1.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f, 0.5f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.5f
		);
		rightWall.pMesh = AEGfxMeshEnd();
		
		/*CREATE PLATFORM*/
		platform.width = 48, platform.height = 48, platform.pos.x = 0, platform.pos.y = -32;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 1.0f,	// left bottom
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.5f		// left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f, 0.5f,		// right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.5f		// left top		y = 0.5f
		);
		platform.pMesh = AEGfxMeshEnd();

		/*CREATE PLAYER*/
		player.obj.width = 30, player.obj.height = 30, player.obj.rotation = 0, player.obj.pos.x = 100, player.obj.pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 1.0f / 8.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, 1.0f / 8.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f / 11.0f, 0.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, 1.0f / 8.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		player.obj.pMesh = AEGfxMeshEnd();
		player.direction = AEVec2{ 0.f,0.f }, player.input = AEVec2{ 0,0 }, player.speed = 100.0f;
		player.spriteX = 11, player.spriteY = 8, player.spriteIteration = 0;
		player.pTexOffsetX = 0, player.pTexOffsetY = 0;
		player.isMoving = false;
	}

	void Level2_Update() {
		using namespace CollisionHandler;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);
		player.isMoving = InputHandler::playerMovement(player);

		/*UPDATE LOGIC*/
		/*MOVEMENT*/
		if (player.isMoving) {
			f32 unitSpeed = player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AEVec2Normalize(&player.direction, &player.direction);
			AEVec2Scale(&player.direction, &player.direction, unitSpeed);
			AEVec2Add(&player.obj.pos, &player.obj.pos, &player.direction);
		}
		/*ANIMATION*/


		///*Check for any collision*/
		//for (int i = 0; i < sizeof(objs) / sizeof(Object*); i++) {
		//	f32 depth;
		//	Vector normal;
		//	if (SAT_Collision(player.obj, *objs[i], depth, normal)) {
		//		/*Collision resolution: correct by normal vector with length of the depth.*/
		//		normal.x *= depth;
		//		normal.y *= depth;
		//		player.obj.pos.x -= normal.x;
		//		player.obj.pos.y -= normal.y;
		// 
		//		/*TODO*/
		//		// change the player direction based on the normal.
		//		
		//	}
		//}
	}

	void Level2_Draw() {
		AEGfxSetBackgroundColor(0.f,0.f,0.f);
		RenderWall(cornerWall);
		RenderWall(leftWall);
		RenderWall(rightWall);
		RenderFloor(platform);
		AnimationHandler::AnimateCharacter(player);
	}

	void Level2_Free() {
		AEGfxMeshFree(cornerWall.pMesh);
		AEGfxMeshFree(leftWall.pMesh);
		AEGfxMeshFree(rightWall.pMesh);
		AEGfxMeshFree(platform.pMesh);
		AEGfxMeshFree(player.obj.pMesh);
	}

	void Level2_Unload() {
		AEGfxTextureUnload(cornerWall.pTex);
		AEGfxTextureUnload(leftWall.pTex);
		AEGfxTextureUnload(rightWall.pTex);
		AEGfxTextureUnload(platform.pTex[0]);
		AEGfxTextureUnload(platform.pTex[1]);
		AEGfxTextureUnload(platform.pTex[2]);
		AEGfxTextureUnload(platform.pTex[3]);
		AEGfxTextureUnload(player.obj.pTex);
	}
}