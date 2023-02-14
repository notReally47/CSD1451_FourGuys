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


namespace Level2 {
	using namespace	GameObjects;
	Object	wall, floor, deco, portraits[4], player, left, right; //platform,  pHighlight
	Character p_player;
	ObjectInst objInst[123];
	f32 windowWidth, windowHeight;
	Object* objs[7]{ &wall, &floor, &deco, &portraits[0], &portraits[1], &portraits[2], &portraits[3] };
	ObjectInst leftBound, rightBound;

	const std::string level_number = "02";
	std::vector<Load_Data_From_File::ObjectShape> vOS;
	std::vector<Load_Data_From_File::ObjectTransform> vOT;

	void Level2_Load() {
		player.type = Enum::TYPE::PLAYER;
		wall.type = Enum::TYPE::WALL;
		floor.type = Enum::TYPE::FLOOR;
		deco.type = Enum::TYPE::DECO;
		portraits[0].type = Enum::TYPE::PORTRAIT;
		portraits[1].type = Enum::TYPE::PORTRAIT2;
		portraits[2].type = Enum::TYPE::MPORTRAIT;
		portraits[3].type = Enum::TYPE::LPORTRAIT;

		vOS = Load_Data_From_File::Load_Shape_From_YAML(level_number);
		vOT = Load_Data_From_File::Load_Transform_From_YAML(level_number, vOS);
		Load_Data_From_File::Load_Texture_To_Object(vOS, player);
		Load_Data_From_File::Load_Texture_To_Object(vOS, wall);
		Load_Data_From_File::Load_Texture_To_Object(vOS, floor);
		Load_Data_From_File::Load_Texture_To_Object(vOS, deco);
		Load_Data_From_File::Load_Texture_To_Object(vOS, portraits[0]);
		Load_Data_From_File::Load_Texture_To_Object(vOS, portraits[1]);
		Load_Data_From_File::Load_Texture_To_Object(vOS, portraits[2]);
		Load_Data_From_File::Load_Texture_To_Object(vOS, portraits[3]);
		Load_Data_From_File::Extract_Shape_Data_Out(vOS, level_number);
		Load_Data_From_File::Extract_Transform_Data_Out(vOT, level_number);
	}

	void Level2_Init()
	{
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());

		/*CREATE WALL*/
		Level_Initializer::Init_Mesh(vOS, wall);

		/*CREATE FLOOR*/
		Level_Initializer::Init_Mesh(vOS, floor);

		/*CRAETE PAINTINGS*/
		Level_Initializer::Init_Mesh(vOS, portraits[0]);
		Level_Initializer::Init_Mesh(vOS, portraits[1]);
		Level_Initializer::Init_Mesh(vOS, portraits[2]);
		Level_Initializer::Init_Mesh(vOS, portraits[3]);

		/*TRANSFORM OBJECTS*/
		Level_Initializer::Init_Object(vOT, objs, objInst, (sizeof(objInst) / sizeof(objInst[0])));

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
	}

	void Level2_Update()
	{
		using namespace CollisionHandler;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);
		p_player.pObjInst.flag = (InputHandler::playerMovement(p_player)) ? FLAG_ACTIVE : FLAG_INACTIVE;

		/*UPDATE LOGIC*/
		/*MOVEMENT*/
		if (p_player.pObjInst.flag) {
			f32 unitSpeed = p_player.speed * static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AEVec2Normalize(&p_player.dir, &p_player.dir);
			AEVec2Scale(&p_player.dir, &p_player.dir, unitSpeed);
			p_player.pObjInst.transform.m[0][2] += p_player.dir.x;
			p_player.pObjInst.transform.m[1][2] += p_player.dir.y;
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
	}
	void Level2_Draw()
	{
		RenderSettings();
		for (int i = 0; i < (sizeof(objInst) / sizeof(objInst[0])); i++)
			RenderObject(objInst[i]);
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
		vOS.clear();
		vOT.clear();
	}
}