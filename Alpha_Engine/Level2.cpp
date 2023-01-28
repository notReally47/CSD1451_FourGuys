#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"
#include "VectorMath.h"
#include "AnimationHandler.h"
#include <iostream>

namespace Level2
{
	using namespace GameObjects;
	Object wall, floor, deco, portraits[4], pHighlight;
	Character player;
	f32 windowWidth, windowHeight;
	Object *objs[3]{&wall, &floor, &deco};
	void Level2_Load()
	{
		AE_ASSERT_MESG(player.obj.pTex = AEGfxTextureLoad("../Assets/Sprites/player.png"), "Failed to load texture");
		AE_ASSERT_MESG(wall.pTex = AEGfxTextureLoad("../Assets/Textures/wall.png"), "Failed to load texture");
		AE_ASSERT_MESG(deco.pTex = AEGfxTextureLoad("../Assets/Props/candles.png"), "Failed to load texture");
		AE_ASSERT_MESG(floor.pTex = AEGfxTextureLoad("../Assets/Textures/floor.png"), "Failed to load texture");
		AE_ASSERT_MESG(portraits[0].pTex = AEGfxTextureLoad("../Assets/Props/smallportraits.png"), "Failed to load texture");
		// AE_ASSERT_MESG(portraits[1].pTex = AEGfxTextureLoad("../Assets/Props/smallportraits2.png"), "Failed to load texture");
		// AE_ASSERT_MESG(portraits[2].pTex = AEGfxTextureLoad("../Assets/Props/mediumportraits.png"), "Failed to load texture");
		// AE_ASSERT_MESG(portraits[3].pTex = AEGfxTextureLoad("../Assets/Props/largeportraits.png"), "Failed to load texture");
	}

	void Level2_Init()
	{
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());

		/*CREATE WALL*/
		wall.width = 64, wall.height = 128, wall.pos.x = 0, wall.pos.y = 64;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 7.0f, 1.0f, // wall_dim = 1.f / 7.f;
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f / 7.0f, .0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 7.0f, 1.0f,
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f);
		wall.pMesh = AEGfxMeshEnd();

		/*CREATE FLOOR*/
		floor.width = 48, floor.height = 48, floor.pos.x = 0, floor.pos.y = -16;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f, // left bottom
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f, // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .5f	 // left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f, .5f,	 // right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f, // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .5f	 // left top		y = 0.5f
		);
		floor.pMesh = AEGfxMeshEnd();

		/*CREATE PLAYER*/
		player.obj.width = 32, player.obj.height = 38, player.obj.rotation = 0, player.obj.pos.x = 100, player.obj.pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, .125f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, .125f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f / 11.0f, .0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, .125f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f);
		player.obj.pMesh = AEGfxMeshEnd();
		player.State = Enum::CS_IDLE, player.direction = AEVec2{0, 0}, player.speed = 100.0f;
		player.direction = AEVec2{0.f, 0.f}, player.input = AEVec2{0, 0}, player.speed = 100.0f;
		player.spriteX = 11, player.spriteY = 8, player.spriteIteration = 0;
		player.pTexOffsetX = 0, player.pTexOffsetY = 0;
		player.isMoving = false;

		/*CREATE DECO*/
		deco.width = 6, deco.height = 18, deco.pos.x = 380, deco.pos.y = 280;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f, // left bottom
			1.0f, -1.0f, 0xFFFF0000, .2f, 1.0f,	 // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f	 // left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, .2f, .0f,	// right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, .2f, 1.0f, // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f	// left top		y = 0.5f
		);
		deco.pMesh = AEGfxMeshEnd();

		/*CREATE SMALL PORTRAITS*/
		portraits[0].width = 24.3, portraits[0].height = 40.3, portraits[0].pos.x = -70, portraits[0].pos.y = 0;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f / 3.0f,	 // left bottom
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 1.0f / 3.0f, // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f			 // left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 0.25f, .0f,			 // right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 1.0f / 3.0f, // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f			 // left top		y = 0.5f
		);
		portraits[0].pMesh = AEGfxMeshEnd();
		/*CREATE PORTRAIT HIGHLIGHTS*/
		pHighlight.width = portraits[0].width, pHighlight.height = portraits[0].height, pHighlight.pos.x = portraits[0].pos.x, pHighlight.pos.y = portraits[0].pos.y;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f / 3.0f,	 // left bottom
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 1.0f / 3.0f, // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f			 // left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 0.25f, .0f,			 // right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 1.0f / 3.0f, // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f			 // left top		y = 0.5f
		);
		pHighlight.pMesh = AEGfxMeshEnd();
		glow = false;
	}

	void Level2_Update()
	{
		using namespace CollisionHandler;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);
		player.isMoving = InputHandler::playerMovement(player);

		/*UPDATE LOGIC*/
		/*MOVEMENT*/
		if (player.isMoving)
		{
			f32 unitSpeed = player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AEVec2Normalize(&player.direction, &player.direction);
			AEVec2Scale(&player.direction, &player.direction, unitSpeed);
			AEVec2Add(&player.obj.pos, &player.obj.pos, &player.direction);
			if (player.obj.pos.y - portraits->pos.y < 40)
			{
				if (DistanceBetweenPlayerAndPortrait(portraits->pos, player.obj.pos) < 55.0)
					glow = true;
				else
					glow = false;
			}
			else
				glow = false;
		}

		/*ANIMATION*/

		///*Check for any collision*/
		// for (int i = 0; i < sizeof(objs) / sizeof(Object*); i++) {
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
		// }
	}

	void Level2_Draw()
	{

		RenderSettings();
		RenderObject(Enum::TYPE::WALL, wall);
		RenderObject(Enum::TYPE::FLOOR, floor);
		RenderObject(Enum::TYPE::DECO, deco);
		RenderObject(Enum::TYPE::PLAYER, player.obj);
		if (glow)
		{
			RenderColorSettings();
			RenderObject(Enum::TYPE::pHighlight, pHighlight);
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		}
		RenderObject(Enum::TYPE::PORTRAIT, portraits[0]);
	}

	void Level2_Free()
	{
		AEGfxMeshFree(floor.pMesh);
		AEGfxMeshFree(player.obj.pMesh);
		AEGfxMeshFree(wall.pMesh);
		AEGfxMeshFree(deco.pMesh);
		AEGfxMeshFree(portraits[0].pMesh);
	}

	void Level2_Unload()
	{
		AEGfxTextureUnload(wall.pTex);
		AEGfxTextureUnload(deco.pTex);
		AEGfxTextureUnload(floor.pTex);
		AEGfxTextureUnload(player.obj.pTex);
		AEGfxTextureUnload(portraits[0].pTex);
	}
}