#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"

namespace Level2 {
	using namespace GameObjects;
	//AEGfxTexture* wallTex, * platformTex;
	Object leftWall, rightWall, platform;
	Character player;
	s8 fontId;
	f32 windowWidth, windowHeight;
	Object objs[2] = { leftWall, rightWall };

	void Level2_Load() {
		player.obj.pTex = AEGfxTextureLoad("../Assets/sprites/sprites.png");
		leftWall.pTex = AEGfxTextureLoad("../Assets/Textures/wallTex.png");
		rightWall.pTex = AEGfxTextureLoad("../Assets/Textures/wallTex.png");
		platform.pTex = AEGfxTextureLoad("../Assets/Textures/platformTex.png");
		fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12);
		windowWidth = AEGetWindowWidth();
		windowHeight = AEGetWindowHeight();
	}

	void Level2_Init() {
		/*CREATE LEFT WALL*/
		leftWall.width = static_cast<f32>(windowWidth / 10), leftWall.height = static_cast<f32>(AEGetWindowHeight() / 2), leftWall.rotation = 0, leftWall.pos.x = -static_cast<f32>(2 * AEGetWindowWidth() / 5), leftWall.pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 6.0f,
			1.0f, -1.0f, 0xFFFF0000, 2.0f, 6.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 2.0f, 0.0f,
			1.0f, -1.0f, 0xFFFF0000, 2.0f, 6.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		leftWall.pMesh = AEGfxMeshEnd();

		/*CREATE RIGHT WALL*/
		rightWall.width = static_cast<f32>(windowWidth / 10), rightWall.height = static_cast<f32>(AEGetWindowHeight() / 2), rightWall.rotation = 0, rightWall.pos.x = static_cast<f32>(2 * AEGetWindowWidth() / 5), rightWall.pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 6.0f,
			1.0f, -1.0f, 0xFFFF0000, 2.0f, 6.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 2.0f, 0.0f,
			1.0f, -1.0f, 0xFFFF0000, 2.0f, 6.0f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		rightWall.pMesh = AEGfxMeshEnd();

		/*CREATE PLATFORM*/
		//platform.width = 50, platform.height = 50, platform.rotation = 0, platform.pos.x = 0, platform.pos.y = 0;
		//AEGfxMeshStart();
		//AEGfxTriAdd(
		//	-1.0f, -1.0f, 0xFFFF0000, 0.0f, 1.0f,
		//	1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,
		//	-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		//);
		//AEGfxTriAdd(
		//	1.0f, 1.0f, 0xFFFF0000, 1.0f, 0.0f,
		//	1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,
		//	-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		//);
		//platform.pMesh = AEGfxMeshEnd();

		/*CREATE PLAYER*/
		player.obj.width = 30, player.obj.height = 30, player.obj.rotation = 0, player.obj.pos.x = 0, player.obj.pos.y = 0;
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
	}

	void Level2_Update() {
		using namespace CollisionHandler;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);
		int direction = InputHandler::playerMovement(player);

		/*UPDATE LOGIC*/
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

		if (direction != Enum::NONE) {
			if (SAT_Collision(player.obj, leftWall) || SAT_Collision(player.obj, rightWall)) {
				player.obj.pos.x -= player.velocity_x * AEFrameRateControllerGetFrameTime();
			}
		}
	}

	void Level2_Draw() {
		AEGfxSetBackgroundColor(45.f / 255.f, 218.f / 255.f, 222.f / 255.f);

		RenderObject(leftWall);
		RenderObject(rightWall);
		//RenderObject(platform);
		RenderObject(player.obj);
	}

	void Level2_Free() {
		AEGfxMeshFree(leftWall.pMesh);
		AEGfxMeshFree(rightWall.pMesh);
		//AEGfxMeshFree(platform.pMesh);
	}

	void Level2_Unload() {
		AEGfxTextureUnload(leftWall.pTex);
		AEGfxTextureUnload(rightWall.pTex);
		AEGfxTextureUnload(platform.pTex);
	}
}