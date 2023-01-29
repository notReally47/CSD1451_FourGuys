#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"
#include "VectorMath.h"
#include "LoadValues.h"
#include "LoadTextures.h"
#include "LevelInitializer.h"
#include "AnimationHandler.h"
#include <iostream>

namespace Level2 {
	/*DEFINES*/
	const unsigned char		FLAG_ACTIVE = 0x1;		//todo
	const unsigned char		FLAG_INACTIVE = 0x0;

	using namespace GameObjects;
	Object wall, floor, deco, portraits[4], pHighlight;
	Character player;
	ObjectInst objInst[123];

	f32 windowWidth, windowHeight;
	Object* objs[7]{ &wall, &floor, &deco, &portraits[0], &portraits[1], &portraits[2], &portraits[3]};

	const std::string level_number = "02";
	std::vector<Load_Values::ValueFromFile> vff;
	std::vector<Load_Texture::TextureFromFile> tff;

	void Level2_Load() {
		player.obj.type = Enum::TYPE::PLAYER;
		wall.type = Enum::TYPE::WALL;
		floor.type = Enum::TYPE::FLOOR;
		deco.type = Enum::TYPE::DECO;
		portraits[0].type = Enum::TYPE::PORTRAIT;
		portraits[1].type = Enum::TYPE::PORTRAIT2;
		portraits[2].type = Enum::TYPE::MPORTRAIT;
		portraits[3].type = Enum::TYPE::LPORTRAIT;
		vff = Load_Values::Load_Values_From_File(level_number);
		tff = Load_Texture::Load_Texture_From_File(level_number);
		Load_Texture::Load_Texture_To_Object(tff, player.obj);
		Load_Texture::Load_Texture_To_Object(tff, wall);
		Load_Texture::Load_Texture_To_Object(tff, floor);
		Load_Texture::Load_Texture_To_Object(tff, deco);
		Load_Texture::Load_Texture_To_Object(tff, portraits[0]);
		Load_Texture::Load_Texture_To_Object(tff, portraits[1]);
		Load_Texture::Load_Texture_To_Object(tff, portraits[2]);
		Load_Texture::Load_Texture_To_Object(tff, portraits[3]);
		AE_ASSERT_MESG(fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12), "Failed to load font");
	}

	void Level2_Init()
	{
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());

		/*CREATE WALL*/
		Level_Initializer::Init_Mesh_From_File(vff, wall);

		/*CREATE FLOOR*/
		Level_Initializer::Init_Mesh_From_File(vff, floor);

		/*CRAETE PAINTINGS*/
		Level_Initializer::Init_Mesh_From_File(vff, portraits[0]);
		Level_Initializer::Init_Mesh_From_File(vff, portraits[1]);
		Level_Initializer::Init_Mesh_From_File(vff, portraits[2]);
		Level_Initializer::Init_Mesh_From_File(vff, portraits[3]);

		/*TRANSFORM OBJECTS*/
		Level_Initializer::Init_Object_Instance(vff, objs, objInst, (sizeof(objInst) / sizeof(objInst[0])));


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
		for (int i = 0; i < (sizeof(objInst) / sizeof(objInst[0])); i++)
			RenderObject(objInst[i]);
		//RenderObject(Enum::TYPE::PLATFORM, *platform->pObj);
		//RenderObject(Enum::TYPE::PLAYER, player.obj);
	}

	void Level2_Free()
	{
		AEGfxMeshFree(floor.pMesh);
		AEGfxMeshFree(player.obj.pMesh);
		AEGfxMeshFree(wall.pMesh);
		AEGfxMeshFree(deco.pMesh);
		AEGfxMeshFree(portraits[0].pMesh);
		AEGfxMeshFree(portraits[1].pMesh);
		AEGfxMeshFree(portraits[2].pMesh);
		AEGfxMeshFree(portraits[3].pMesh);
	}

	void Level2_Unload()
	{
		AEGfxTextureUnload(wall.pTex);
		AEGfxTextureUnload(deco.pTex);
		AEGfxTextureUnload(floor.pTex);
		AEGfxTextureUnload(player.obj.pTex);
		AEGfxTextureUnload(portraits[0].pTex);
		AEGfxTextureUnload(portraits[1].pTex);
		AEGfxTextureUnload(portraits[2].pTex);
		AEGfxTextureUnload(portraits[3].pTex);
		vff.clear();
		tff.clear();
	}
}