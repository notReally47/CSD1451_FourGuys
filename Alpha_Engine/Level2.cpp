#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"
#include "VectorMath.h"
#include "AnimationHandler.h"

namespace Level2 {
	using namespace GameObjects;
	Object wall, platform, deco, portraits[4];
	Character player;
	
	f32 windowWidth, windowHeight;
	Object* objs[3] { &wall, &platform, &deco };

	void Level2_Load() {
		AE_ASSERT_MESG(player.obj.pTex = AEGfxTextureLoad("../Assets/Sprites/player.png"), "Failed to load texture");
		AE_ASSERT_MESG(wall.pTex = AEGfxTextureLoad("../Assets/Textures/wall.png"), "Failed to load texture");
		AE_ASSERT_MESG(deco.pTex = AEGfxTextureLoad("../Assets/Props/fire05.png"), "Failed to load texture");
		AE_ASSERT_MESG(platform.pTex = AEGfxTextureLoad("../Assets/Textures/floor.png"), "Failed to load texture");
		AE_ASSERT_MESG(portraits[0].pTex = AEGfxTextureLoad("../Assets/Props/smallportraits.png"), "Failed to load texture");
		//AE_ASSERT_MESG(portraits[1].pTex = AEGfxTextureLoad("../Assets/Props/smallportraits2.png"), "Failed to load texture");
		//AE_ASSERT_MESG(portraits[2].pTex = AEGfxTextureLoad("../Assets/Props/mediumportraits.png"), "Failed to load texture");
		//AE_ASSERT_MESG(portraits[3].pTex = AEGfxTextureLoad("../Assets/Props/largeportraits.png"), "Failed to load texture");
		AE_ASSERT_MESG(fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12), "Failed to load font");
	}

	void Level2_Init() {
		objs[2] = new Object;
		objs[2]->pMesh = new AEGfxVertexList[5];
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());
		
		/*CREATE WALL*/
		wall.width = 64, wall.height = 128, wall.pos.x = 0, wall.pos.y = 64;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f,
			1.0f, -1.0f, 0xFFFF0000, wall_dim, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, wall_dim, .0f,
			1.0f, -1.0f, 0xFFFF0000, wall_dim, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f
		);
		wall.pMesh = AEGfxMeshEnd();
			
		/*CREATE PLATFORM*/
		platform.width = 48, platform.height = 48, platform.pos.x = 0, platform.pos.y = -16;
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
		player.obj.width = 32, player.obj.height = 64, player.obj.rotation = 0, player.obj.pos.x = 100, player.obj.pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, 0.0f, 0.125f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, 0.125f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f / 11.0f, 0.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, 0.125f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		player.obj.pMesh = AEGfxMeshEnd();
		player.State = Enum::CS_IDLE, player.direction = AEVec2{ 0,0 }, player.speed = 100.0f;

		/*CREATE DECO*/
		deco.width = 6, deco.height = 18, deco.pos.x = 380, deco.pos.y = 280;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f,	// left bottom
			1.0f, -1.0f, 0xFFFF0000, 1.0f/6.0f, 1.0f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f / 6.0f, .0f,		// right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 6.0f, 1.0f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		deco.pMesh = AEGfxMeshEnd();

		/*CREATE SMALL PORTRAITS*/
		portraits[0].width = 24.3, portraits[0].height = 40.3, portraits[0].pos.x = -70, portraits[0].pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f / 3.0f,	// left bottom
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 1.0f / 3.0f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 0.25f, .0f,		// right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 1.0f / 3.0f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		portraits[0].pMesh = AEGfxMeshEnd();
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
		RenderSettings();
		
		RenderWall(wall);
		RenderFloor(platform);
		RenderDeco(deco);
		RenderObject(player.obj);
		RenderPortrait(portraits[0]);
	}

	void Level2_Free() {
		AEGfxMeshFree(platform.pMesh);
		AEGfxMeshFree(player.obj.pMesh);
		AEGfxMeshFree(wall.pMesh);
		AEGfxMeshFree(deco.pMesh);
		AEGfxMeshFree(portraits[0].pMesh);
	}

	void Level2_Unload() {
		AEGfxTextureUnload(wall.pTex);
		AEGfxTextureUnload(deco.pTex);
		AEGfxTextureUnload(platform.pTex);
		AEGfxTextureUnload(player.obj.pTex);
		AEGfxTextureUnload(portraits[0].pTex);

	}
}