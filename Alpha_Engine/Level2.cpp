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

namespace Level2 {
	using namespace	GameObjects;
	Object	wall, floor, deco, portraits[4], platform, player;
	Character p_player;
	ObjectInst objInst[125];
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
		player.direction = AEVec2{ 0.f,0.f }, player.input = AEVec2{ 0,0 }, player.speed = 100.0f;
		player.spriteX = 11, player.spriteY = 8, player.spriteIteration = 0;
		player.pTexOffsetX = 0, player.pTexOffsetY = 0;
		player.isMoving = false;

		/*CREATE DECO*/
		deco.type = Enum::TYPE::DECO;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f, // left bottom
			1.0f, -1.0f, 0xFFFF0000, .2f, 1.0f,	 // right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f	 // left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, .2f, .0f,	// right top	y = 0.5f

		/*CREATE PORTRAITS*/
		portraits[0].type = Enum::TYPE::PORTRAIT;
		portraits[1].type = Enum::TYPE::PORTRAIT;
		portraits[2].type = Enum::TYPE::PORTRAIT;
		portraits[3].type = Enum::TYPE::PORTRAIT;
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
		/*DATA FOR SMALL PORTRAITS*/
		objInst[113].pObj = &portraits[0];
		objInst[113].flag = FLAG_INACTIVE;
		objInst[113].tex_offset = { .0f, .0f };
		objInst[113].transform = { 24.3f, .0f, -70.0f,
								.0f, 40.3f, .0f,
								.0f, .0f, 1.0f };

		objInst[114].pObj = &portraits[0];
		objInst[114].flag = FLAG_ACTIVE;
		objInst[114].tex_offset = { .0f, 1.0f/3.0f };
		objInst[114].transform = { 24.3f, .0f, -220.0f,
								.0f, 40.3f, 165.0f,
								.0f, .0f, 1.0f };
		objInst[115].pObj = &portraits[0];
		objInst[115].flag = FLAG_INACTIVE;
		objInst[115].tex_offset = { .5f, 2.0f / 3.0f };
		objInst[115].transform = { 24.3f, .0f, 185.0f,
								.0f, 40.3f, 185.0f,
								.0f, .0f, 1.0f };
		/*DATA FOR SMALL PORTRAITS 2*/
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 0.5f,	// left bottom
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 0.5f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 0.25f, .0f,		// right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 0.5f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		portraits[1].pMesh = AEGfxMeshEnd();
		objInst[116].pObj = &portraits[1];
		objInst[116].flag = FLAG_ACTIVE;
		objInst[116].tex_offset = { 0.5f, .0f };
		objInst[116].transform = { 28.3f, .0f, 200.0f,
								.0f, 45.0f, 20.0f,
								.0f, .0f, 1.0f };
		objInst[117].pObj = &portraits[1];
		objInst[117].flag = FLAG_INACTIVE;
		objInst[117].tex_offset = { 0.5f, .5f };
		objInst[117].transform = { 28.3f, .0f, 75.0f,
								.0f, 46.0f, 160.0f,
								.0f, .0f, 1.0f };
		/*DATA FOR MEDIUM PORTRAITS*/
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
		portraits[2].pMesh = AEGfxMeshEnd();
		objInst[118].pObj = &portraits[2];
		objInst[118].flag = FLAG_ACTIVE;
		objInst[118].tex_offset = { .5f, .0f };
		objInst[118].transform = { 32.3f, .0f, 240.0f,
								.0f, 37.6f, 80.0f,
								.0f, .0f, 1.0f };
		objInst[119].pObj = &portraits[2];
		objInst[119].flag = FLAG_INACTIVE;
		objInst[119].tex_offset = { .0f, 1.0f/3.0f };
		objInst[119].transform = { 32.3f, .0f, -80.0f,
								.0f, 37.6f, 155.0f,
								.0f, .0f, 1.0f };
		objInst[120].pObj = &portraits[2];
		objInst[120].flag = FLAG_ACTIVE;
		objInst[120].tex_offset = { .0f, 2.0f/3.0f };
		objInst[120].transform = { 32.3f, .0f, -200.0f,
								.0f, 37.6f, 15.0f,
								.0f, .0f, 1.0f };
		/*DATA FOR LARGE PORTRAITS*/
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 0.5f,	// left bottom
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 0.5f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 0.25f, .0f,		// right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 0.25f, 0.5f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		portraits[3].pMesh = AEGfxMeshEnd();
		objInst[121].pObj = &portraits[3];
		objInst[121].flag = FLAG_INACTIVE;
		objInst[121].tex_offset = { .0f, .0f };
		objInst[121].transform = { 40.32f, .0f, -245.0f,
								.0f, 39.6f, 75.0f,
								.0f, .0f, 1.0f };
		objInst[122].pObj = &portraits[3];
		objInst[122].flag = FLAG_ACTIVE;
		objInst[122].tex_offset = { .5f, 0.5f };
		objInst[122].transform = { 40.32f, .0f, 80.0f,
								.0f, 39.6f, 75.0f,
								.0f, .0f, 1.0f };

		/*DATA FOR PLATFORM*/
		platform.type = Enum::TYPE::PLATFORM;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f,	// left bottom
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .5f		// left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f, .5f,		// right top	y = 0.5f
			1.0f, -1.0f, 0xFFFF0000, 1.0f, 1.0f,	// right bottom
			-1.0f, 1.0f, 0xFFFF0000, .0f, .5f		// left top		y = 0.5f
		);
		platform.pMesh = AEGfxMeshEnd();
		objInst[123].pObj = &platform;
		objInst[123].flag = FLAG_INACTIVE;
		objInst[123].tex_offset = { .0f, .0f };
		objInst[123].transform = { 38.0f, .0f, .0f,
								.0f, 38.0f, -16.0f,
								.0f, .0f, 1.0f };
		objInst[124].pObj = &platform;
		objInst[124].flag = FLAG_ACTIVE;
		objInst[124].tex_offset = { .0f, .0f };
		objInst[124].transform = { 38.0f, .0f, 20.0f,
								.0f, 38.0f, -80.0f,
								.0f, .0f, 1.0f };

		/*CREATE PLAYER*/
		player.type = Enum::TYPE::PLAYER;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, .125f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, .125f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 1.0f / 11.0f, .0f,
			1.0f, -1.0f, 0xFFFF0000, 1.0f / 11.0f, .125f,
			-1.0f, 1.0f, 0xFFFF0000, 0.0f, 0.0f
		);
		player.pMesh = AEGfxMeshEnd();
		p_player.pObjInst.pObj = &player;
		p_player.pObjInst.flag = FLAG_INACTIVE;
		p_player.pObjInst.tex_offset = { .0f, .0f };
		p_player.pObjInst.transform = { 38.0f, .0f, -20.0f,
									.0f, 38.0f, -20.0f,
									.0f, .0f, 1.0f };
		p_player.dir = { .0f, .0f };
		p_player.input = { .0f, .0f };
		//p_player.rotation = { .0f, .0f };
		p_player.speed = 100.0f;
		p_player.spriteIteration = 0;
			-1.0f, 1.0f, 0xFFFF0000, .0f, .0f		// left top		y = 0.5f
		);
		portraits[0].pMesh = AEGfxMeshEnd();
		
	}

	void Level2_Update()
	{
		using namespace CollisionHandler;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);
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
		if (p_player.pObjInst.flag) {
			f32 unitSpeed = p_player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AEVec2Normalize(&p_player.dir, &p_player.dir);
			AEVec2Scale(&p_player.dir, &p_player.dir, unitSpeed);
			p_player.pObjInst.transform.m[0][2] += p_player.dir.x;
			p_player.pObjInst.transform.m[1][2] += p_player.dir.y;
			f32 unitSpeed = player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AEVec2Normalize(&player.direction, &player.direction);
			AEVec2Scale(&player.direction, &player.direction, unitSpeed);
			AEVec2Add(&player.obj.pos, &player.obj.pos, &player.direction);
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

		for (int i = 0; i < (sizeof(objInst) / sizeof(objInst[0])); i++)
			RenderObject(objInst[i]);
		//RenderObject(Enum::TYPE::PLATFORM, *platform->pObj);
		//RenderObject(Enum::TYPE::PLAYER, player.obj);
		for (int i=0; i<125; i++)
			RenderObject(objInst[i]);
		AnimationHandler::AnimateCharacter(p_player);
		RenderObject(Enum::TYPE::FLOOR, floor);
		RenderObject(Enum::TYPE::DECO, deco);
		RenderObject(Enum::TYPE::PLAYER, player.obj);
		RenderObject(Enum::TYPE::PORTRAIT, portraits[0]);
	}

	void Level2_Free()
	{
		AEGfxMeshFree(floor.pMesh);
		AEGfxMeshFree(player.pMesh);
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
		AEGfxTextureUnload(portraits[1].pTex);
		AEGfxTextureUnload(portraits[2].pTex);
		AEGfxTextureUnload(portraits[3].pTex);
		AEGfxTextureUnload(portraits[1].pTex);
		AEGfxTextureUnload(portraits[2].pTex);
		AEGfxTextureUnload(portraits[3].pTex);
		vff.clear();
		tff.clear();
		AEGfxTextureUnload(floor.pTex);
		AEGfxTextureUnload(player.pTex);
		AEGfxTextureUnload(portraits[0].pTex);

	}
}