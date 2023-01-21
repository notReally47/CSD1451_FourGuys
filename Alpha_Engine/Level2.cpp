#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"

namespace Level2 {
	using namespace GameObjects;
	Object leftWall, rightWall, cornerWall;
	Floor platform;
	//Character player;
	s8 fontId;
	f32 windowWidth, windowHeight;
	//Object* objs[4]{ &platform, &leftWall, &rightWall, &cornerWall };

	void Level2_Load() {
		//player.obj.pTex = AEGfxTextureLoad("../Assets/sprites/sprites.png");
		cornerWall.pTex = AEGfxTextureLoad("../Assets/Textures/cornerwall.png");
		leftWall.pTex = AEGfxTextureLoad("../Assets/Textures/leftwall0.png");
		rightWall.pTex = AEGfxTextureLoad("../Assets/Textures/rightwall0.png");
		platform.pTex[0] = AEGfxTextureLoad("../Assets/Textures/floor0.png");
		platform.pTex[1] = AEGfxTextureLoad("../Assets/Textures/floor1.png");
		platform.pTex[2] = AEGfxTextureLoad("../Assets/Textures/floor2.png");
		platform.pTex[3] = AEGfxTextureLoad("../Assets/Textures/floor3.png");
		fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12);
		windowWidth = AEGetWindowWidth();
		windowHeight = AEGetWindowHeight();
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
		/*
		player.obj.width = 30, player.obj.height = 30, player.obj.rotation = 0, player.obj.pos.x = 100, player.obj.pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 1.0f / 5.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 8.0f, 1.0f / 5.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f / 8.0f, 0.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 8.0f, 1.0f / 5.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		player.obj.pMesh = AEGfxMeshEnd();
		player.State = Enum::CS_IDLE, player.velocity_x = 0.0f, player.velocity_y = 0.0f;
		*/

	}

	void Level2_Update() {
		using namespace CollisionHandler;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);
		//int direction = InputHandler::playerMovement(player);

		/*UPDATE LOGIC*/
		/*
		switch (direction) {
		case Enum::RIGHT:
			player.velocity_x = 100.f;
			player.obj.pos.x += player.velocity_x * AEFrameRateControllerGetFrameTime();
			break;
		case Enum::LEFT:
			player.velocity_x = -100.f;
			player.obj.pos.x += player.velocity_x * AEFrameRateControllerGetFrameTime();
			break;
		}
		*/
		/*Check for any collision*/
		//for (int i = 0; i < sizeof(objs) / sizeof(Object*); i++) {
			//f32 depth;
			//Vector normal;
			//if (SAT_Collision(player.obj, *objs[i], depth, normal)) {
				/*Collision resolution*/
				//normal.x *= depth;
				//normal.y *= depth;
				//player.obj.pos.x -= normal.x;
				//player.obj.pos.y -= normal.y;
			//}
		//}
	}

	void Level2_Draw() {
		AEGfxSetBackgroundColor(0.f,0.f,0.f);
		
		
		RenderWall(cornerWall);
		RenderWall(leftWall);
		RenderWall(rightWall);
		RenderFloor(platform);
		//RenderObject(player.obj);
	}

	void Level2_Free() {
		AEGfxMeshFree(cornerWall.pMesh);
		AEGfxMeshFree(leftWall.pMesh);
		AEGfxMeshFree(rightWall.pMesh);
		AEGfxMeshFree(platform.pMesh);
		//AEGfxMeshFree(player.pMesh);
	}

	void Level2_Unload() {
		AEGfxTextureUnload(cornerWall.pTex);
		AEGfxTextureUnload(leftWall.pTex);
		AEGfxTextureUnload(rightWall.pTex);
		AEGfxTextureUnload(platform.pTex[0]);
		AEGfxTextureUnload(platform.pTex[1]);
		AEGfxTextureUnload(platform.pTex[2]);
		AEGfxTextureUnload(platform.pTex[3]);
		//AEGfxMeshFree(player.pTex);
	}
}