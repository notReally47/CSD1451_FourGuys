#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"
#include "LoadValues.h"
#include "LoadTextures.h"
#include "LoadDataFromFile.h"
#include "LevelInitializer.h"
#include "AnimationHandler.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace Level2
{
	using namespace GameObjects;
	Object player, floor, wall, deco, portrait, landscape; // platform
	Character p_player;
	ObjectInst objInst[85];
	f32 windowWidth, windowHeight;
	Object *objs[]{&player, &floor, &wall, &deco, &portrait, &landscape};
  
	const std::string level_number = "02";

	std::vector<Load_Data_From_File::ObjectShape> vOS;
	std::vector<Load_Data_From_File::ObjectTransform> vOT;

	void Level2_Load() {
		vOS = Load_Data_From_File::Load_Shape_From_YAML(level_number);
		vOT = Load_Data_From_File::Load_Transform_From_YAML(level_number, vOS);

		static int count{ 0 };
		for (auto &iter : vOT) {
/*			if (iter.OS.type == Enum::TYPE::PLAYER) {
				iter.transformation_01 *= 2;
				iter.transformation_02 *= 2;
				iter.transformation_03 *= 2;
				iter.transformation_04 *= 2;
				iter.transformation_05 *= 2;
				iter.transformation_06 *= 2;
			}*/
		}
		
		//Load_Data_From_File::Extract_Shape_Data_Out(vOS, level_number);
		//Load_Data_From_File::Extract_Transform_Data_Out(vOT, level_number);
		
		Load_Data_From_File::Load_Shape_To_Object(vOS, objs);
	}

	void Level2_Init()
	{
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());

		/*TRANSFORM OBJECTS*/
		Level_Initializer::Init_Object(vOT, objs, objInst, (sizeof(objInst) / sizeof(objInst[0])));

		/*DATA TO BE ADD INTO DATA FILES*/

		/*DATA FOR PLATFORM*/
		/*
		platform.type = Enum::TYPE::PLATFORM;
		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, .0f, 1.0f,	// left bottom
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
		*/

		/*LEFT AND RIGHT BOUNDARIES*/

		/*CREATE PLAYER*/
		p_player.pObjInst = objInst[0];
		p_player.pObjInst.pObj = &player;

		p_player.dir = { .0f, .0f };
		p_player.input = { .0f, .0f };
		p_player.rotation = .0f;
		p_player.speed = 200.0f;
		p_player.spriteIteration = 0;

	}

	void Level2_Update()
	{
		using namespace CollisionHandler;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);
		p_player.pObjInst.flag = (InputHandler::playerMovement(p_player)) ? FLAG_ACTIVE : FLAG_INACTIVE;

		/*UPDATE LOGIC*/
		/*MOVEMENT*/
		if (p_player.pObjInst.flag)
		{
			f32 unitSpeed = p_player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AEVec2Normalize(&p_player.dir, &p_player.dir);
			AEVec2Scale(&p_player.dir, &p_player.dir, unitSpeed);
			p_player.pObjInst.transform.m[0][2] += p_player.dir.x;
			p_player.pObjInst.transform.m[1][2] += p_player.dir.y;
      
			//check if player if near portrait
			for (size_t i{ 0 }; i < sizeof(objInst) / sizeof(objInst[0]); i++)
				if (objInst[i].pObj->type == Enum::TYPE::PORTRAIT ||
					objInst[i].pObj->type == Enum::TYPE::LANDSCAPE)
					objInst[i].flag = (DistanceBetweenPlayerAndPortrait(objInst[i].transform.m[0][2],
						objInst[i].transform.m[1][2], p_player.pObjInst.transform.m[0][2],
						p_player.pObjInst.transform.m[1][2]) < 40.0) ? FLAG_ACTIVE : FLAG_INACTIVE;
		}
		/*ANIMATION*/
		AEGfxSetCamPosition(0.f, max(p_player.pObjInst.transform.m[1][2], -85.0f));

#ifdef DEBUG
		//std::cout << p_player.pObjInst.transform.m[0][2] << ' ' << p_player.pObjInst.transform.m[1][2] << std::endl;
#endif // DEBUG

		/*LEFT AND RIGHT BOUNDARY*/
		p_player.pObjInst.transform.m[0][2] += checkBoundary(p_player);
		bool check = checkPlatform(p_player);

		//std::cout << check << std::endl;

		/*Check for any collision*/
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
		// Initialise i to 1 to skip player
		for (int i{ 1 }; i < (sizeof(objInst) / sizeof(objInst[0])); i++)
			RenderObject(objInst[i]);
		AnimationHandler::AnimateCharacter(p_player);
	}

	void Level2_Free()
	{
		AEGfxMeshFree(player.pMesh);
		AEGfxMeshFree(wall.pMesh);
		AEGfxMeshFree(floor.pMesh);
		AEGfxMeshFree(deco.pMesh);
		AEGfxMeshFree(portrait.pMesh);
		AEGfxMeshFree(landscape.pMesh);
	}

	void Level2_Unload()
	{
		AEGfxTextureUnload(player.pTex);
		AEGfxTextureUnload(wall.pTex);
		AEGfxTextureUnload(floor.pTex);
		AEGfxTextureUnload(deco.pTex);
		AEGfxTextureUnload(portrait.pTex);
		AEGfxTextureUnload(landscape.pTex);
	}
}