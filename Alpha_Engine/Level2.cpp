#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"
#include "LoadValues.h"
#include "LoadTextures.h"
#include "LevelInitializer.h"
#include "AnimationHandler.h"
#include <iostream>

namespace Level2
{
	using namespace GameObjects;
	Object wall, floor, deco, portraits[4], player, pHighlight; // platform,  pHighlight
	Character p_player;
	ObjectInst objInst[123];
	f32 windowWidth, windowHeight;
	Object *objs[]{&wall, &floor, &deco, &portraits[0], &portraits[1], &portraits[2], &portraits[3], &pHighlight};
  
  const std::string level_number = "02";
	std::vector<Load_Values::ValueFromFile> vff;
	std::vector<Load_Texture::TextureFromFile> tff;
  
#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

	void Level2_Load()
	{
		player.type = Enum::TYPE::PLAYER;
		wall.type = Enum::TYPE::WALL;
		floor.type = Enum::TYPE::FLOOR;
		deco.type = Enum::TYPE::DECO;
		portraits[0].type = Enum::TYPE::PORTRAIT;
		portraits[1].type = Enum::TYPE::PORTRAIT2;
		portraits[2].type = Enum::TYPE::MPORTRAIT;
		portraits[3].type = Enum::TYPE::LPORTRAIT;
		vff = Load_Values::Load_Values_From_File(level_number);
		tff = Load_Texture::Load_Texture_From_File(level_number);
		Load_Texture::Load_Texture_To_Object(tff, player);
		Load_Texture::Load_Texture_To_Object(tff, wall);
		Load_Texture::Load_Texture_To_Object(tff, floor);
		Load_Texture::Load_Texture_To_Object(tff, deco);
		Load_Texture::Load_Texture_To_Object(tff, portraits[0]);
		Load_Texture::Load_Texture_To_Object(tff, portraits[1]);
		Load_Texture::Load_Texture_To_Object(tff, portraits[2]);
		Load_Texture::Load_Texture_To_Object(tff, portraits[3]);
	}

	void Level2_Init()
	{
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());
		/*CREATE WALL*/
		Level_Initializer::Init_Mesh_From_File(vff, wall);

		/*CREATE FLOOR*/
		Level_Initializer::Init_Mesh_From_File(vff, floor);

		/*CREATE PAINTINGS*/
		Level_Initializer::Init_Mesh_From_File(vff, portraits[0]);
		Level_Initializer::Init_Mesh_From_File(vff, portraits[1]);
		Level_Initializer::Init_Mesh_From_File(vff, portraits[2]);
		Level_Initializer::Init_Mesh_From_File(vff, portraits[3]);

		/*TRANSFORM OBJECTS*/
		Level_Initializer::Init_Object_Instance(vff, objs, objInst, (sizeof(objInst) / sizeof(objInst[0])));

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
		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, .0f, .125f,
			0.5f, -0.5f, 0xFFFF0000, 1.0f / 11.0f, .125f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
		);
		AEGfxTriAdd(
			0.5f, 0.5f, 0xFFFF0000, 1.0f / 11.0f, .0f,
			0.5f, -0.5f, 0xFFFF0000, 1.0f / 11.0f, .125f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f
		);
		player.pMesh = AEGfxMeshEnd();
		p_player.pObjInst.pObj = &player;
		p_player.pObjInst.flag = FLAG_INACTIVE;
		p_player.pObjInst.tex_offset = { .0f, .0f };
		p_player.pObjInst.transform = { 38.0f, .0f, -265.0f,
									.0f, 38.0f, -140.0f,
									.0f, .0f, 0.5f };
		p_player.dir = { .0f, .0f };
		p_player.input = { .0f, .0f };
		p_player.rotation = .0f;
		p_player.speed = 100.0f;
		p_player.spriteIteration = 0;

		/*CREATE PORTRAIT HIGHLIGHTS*/
		AEGfxMeshStart();
		AEGfxTriAdd(
			-1.0f, -1.0f, 0xFFFF0000, .0f, 1.0f / 3.0f,	 // left bottom
			1.0f, -0.5f, 0xFFFF0000, 0.25f, 1.0f / 3.0f, // right bottom
			-1.0f, 0.5f, 0xFFFF0000, .0f, .0f			 // left top		y = 0.5f
		);
		AEGfxTriAdd(
			1.0f, 1.0f, 0xFFFF0000, 0.25f, .0f,			 // right top	y = 0.5f
			1.0f, -0.5f, 0xFFFF0000, 0.25f, 1.0f / 3.0f, // right bottom
			-1.0f, 0.5f, 0xFFFF0000, .0f, .0f			 // left top		y = 0.5f
		);
		pHighlight.pMesh = AEGfxMeshEnd();
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
			for (size_t i{0}; i < sizeof(objInst) / sizeof(objInst[0]); i++)
			{
				if (objInst[i].pObj->type == Enum::TYPE::PORTRAIT 
				|| objInst[i].pObj->type == Enum::TYPE::PORTRAIT2 
				|| objInst[i].pObj->type == Enum::TYPE::MPORTRAIT
				|| objInst[i].pObj->type == Enum::TYPE::LPORTRAIT)
				{
					if (DistanceBetweenPlayerAndPortrait(objInst[i].transform.m[0][2],
														 objInst[i].transform.m[1][2],
														 p_player.pObjInst.transform.m[0][2],
														 p_player.pObjInst.transform.m[1][2]) < 55.0)
						objInst[i].flag = FLAG_ACTIVE;
            
          else 
            objInst[i].flag = FLAG_INACTIVE;
				}
			}
		}

		/*ANIMATION*/
		AEGfxSetCamPosition(0.f, max(p_player.pObjInst.transform.m[1][2], -85.f));

#ifdef DEBUG
		std::cout << p_player.pObjInst.transform.m[0][2] << ' ' << p_player.pObjInst.transform.m[1][2] << std::endl;
#endif // DEBUG

		/*LEFT AND RIGHT BOUNDARY*/
		p_player.pObjInst.transform.m[0][2] += checkBoundary(p_player);
		bool check = checkPlatform(p_player);
		std::cout << check << std::endl;

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
		{
			RenderObject(objInst[i]);
			if (objInst[i].pObj->type == Enum::TYPE::PORTRAIT
			|| objInst[i].pObj->type == Enum::TYPE::PORTRAIT2 
			|| objInst[i].pObj->type == Enum::TYPE::MPORTRAIT
			|| objInst[i].pObj->type == Enum::TYPE::LPORTRAIT)
			{
				if (objInst[i].flag == FLAG_ACTIVE)
					RenderColor(pHighlight, objInst[i].transform.m[0][0], objInst[i].transform.m[1][1], objInst[i].transform.m[0][2], objInst[i].transform.m[1][2]);
			}
			RenderSettings();
			RenderObject(objInst[i]);
		}
		AnimationHandler::AnimateCharacter(p_player);
	}

	void Level2_Free()
	{
		AEGfxMeshFree(floor.pMesh);
		AEGfxMeshFree(player.pMesh);
		AEGfxMeshFree(wall.pMesh);
		//AEGfxMeshFree(deco.pMesh);
		AEGfxMeshFree(portraits[0].pMesh);
		AEGfxMeshFree(portraits[1].pMesh);
		AEGfxMeshFree(portraits[2].pMesh);
		AEGfxMeshFree(portraits[3].pMesh);
	}

	void Level2_Unload()
	{
		AEGfxTextureUnload(floor.pTex);
		AEGfxTextureUnload(player.pTex);
		AEGfxTextureUnload(wall.pTex);
		AEGfxTextureUnload(deco.pTex);
		AEGfxTextureUnload(portraits[0].pTex);
		AEGfxTextureUnload(portraits[1].pTex);
		AEGfxTextureUnload(portraits[2].pTex);
		AEGfxTextureUnload(portraits[3].pTex);
		vff.clear();
		tff.clear();
	}
}