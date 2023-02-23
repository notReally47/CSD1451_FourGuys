#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "GSM.h"
#include "DataFiles.h"
#include "AnimationHandler.h"
#include "PhysicsHandler.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace Level2
{
	const static f32 MIN_CAM_HEIGHT = -65.f;

	using namespace GameObjects;
	Object player, floor, wall, deco, portrait, landscape, platform;
	Character p_player;
	ObjectInst objInst[87];
	f32 windowWidth, windowHeight;
	Object* objs[]{ &player, &floor, &wall, &deco, &portrait, &landscape, &platform };

	const std::string level_number = "02";

	std::vector<Load_Data_From_File::ObjectShape> vOS;
	std::vector<Load_Data_From_File::ObjectTransform> vOT;
	Load_Data_From_File::PlayerProperties* sPP;

	void Level2_Load() {
		vOS = Load_Data_From_File::Load_Shape_From_YAML(level_number);
		vOT = Load_Data_From_File::Load_Transform_From_YAML(level_number, vOS);
		sPP = Load_Data_From_File::Load_Player_Stats_From_YAML(level_number);

		//Extract_Data_To_File::Extract_Shape_Data_Out(vOS, level_number);
		//Extract_Data_To_File::Extract_Transform_Data_Out(vOT, *sPP, level_number);

		Load_Data_From_File::Load_Shape_To_Object(vOS, objs);
	}

	void Level2_Init()
	{
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());

		/*TRANSFORM OBJECTS*/
		Level_Initializer::Init_Object(vOT, objs, objInst, (sizeof(objInst) / sizeof(objInst[0])));

		/*CREATE PLAYER*/
		Level_Initializer::Init_Player(sPP, p_player, &player, &objInst[0]);
	}

	void Level2_Update()
	{
		using namespace Enum;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);

		p_player.pObjInst->flag = (InputHandler::PlayerJump(p_player)) ?
			p_player.pObjInst->flag | JUMPING : p_player.pObjInst->flag & ~JUMPING;
		p_player.pObjInst->flag = (InputHandler::PlayerMovement(p_player)) ? 
			p_player.pObjInst->flag | ACTIVE : p_player.pObjInst->flag & ~ACTIVE;

		/*MOVEMENT*/
		PhysicsHandler::MovePlayer(p_player);

		//check if player if near portrait
		for (size_t i{ 0 }; i < sizeof(objInst) / sizeof(objInst[0]); i++)
		{
			if (objInst[i].pObj->type == PORTRAIT ||
				objInst[i].pObj->type == LANDSCAPE)
			{
				objInst[i].flag = (CollisionHandler::GetDistance(objInst[i].GetPosX(),
					objInst[i].GetPosY(), p_player.pObjInst->GetPosX(),
					p_player.pObjInst->GetPosY()) < 40.0)
					? static_cast<unsigned long>(ACTIVE) : IDLE;
			}
		}

		/*COLLISIONS*/
		//TODO: Collision

		/*ANIMATION*/
		AEGfxSetCamPosition(0.f, max(p_player.pObjInst->GetPosY(), MIN_CAM_HEIGHT));
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
		AEGfxMeshFree(platform.pMesh);
	}

	void Level2_Unload()
	{
		AEGfxTextureUnload(player.pTex);
		AEGfxTextureUnload(wall.pTex);
		AEGfxTextureUnload(floor.pTex);
		AEGfxTextureUnload(deco.pTex);
		AEGfxTextureUnload(portrait.pTex);
		AEGfxTextureUnload(landscape.pTex);
		AEGfxTextureUnload(platform.pTex);
	}
}