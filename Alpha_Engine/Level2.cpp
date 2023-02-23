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
	Character p_player;
	f32 windowWidth, windowHeight;
  
	const std::string level_number = "02";

	std::vector<Object> vOBJ;
	std::vector<ObjectInst> vOBJ_INST;
	Character* sCHARACTER;

	void Level2_Load() {
		vOBJ = Load_Data_From_File::Load_Shape_From_YAML(level_number);
		vOBJ_INST = Load_Data_From_File::Load_Transform_From_YAML(level_number, vOBJ);
		sCHARACTER = Load_Data_From_File::Load_Player_Stats_From_YAML(level_number);


		for (auto &iter : vOBJ_INST) {
			//if (iter.OS.type == Enum::TYPE::PLAYER) {
				iter.transform.m[0][0] /= 2;
				iter.transform.m[0][1] /= 2;
				iter.transform.m[0][2] /= 2;
				iter.transform.m[1][0] /= 2;
				iter.transform.m[1][1] /= 2;
				iter.transform.m[1][2] /= 2;
			//}
		}
		
	}

	void Level2_Init()
	{
		windowWidth = static_cast<f32>(AEGetWindowWidth());
		windowHeight = static_cast<f32>(AEGetWindowHeight());

		/*TRANSFORM OBJECTS*/
		//Level_Initializer::Init_Object_From_Vector(vOBJ_INST, objInst, (sizeof(objInst) / sizeof(objInst[0])));


		/*CREATE PLAYER*/
		Level_Initializer::Init_Player(&vOBJ_INST[0], sCHARACTER, p_player);

		/*Extract Using Vector vOBJ_INST & p_player*/
		//Extract_Data_To_File::Extract_Transform_Data_Out(vOBJ_INST, p_player, level_number);

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
		for (size_t i{ 0 }; i < vOBJ_INST.size(); i++)
		{
			if (vOBJ_INST[i].pObj->type == PORTRAIT ||
				vOBJ_INST[i].pObj->type == LANDSCAPE)
			{
				vOBJ_INST[i].flag = (CollisionHandler::GetDistance(vOBJ_INST[i].GetPosX(),
					vOBJ_INST[i].GetPosY(), p_player.pObjInst->GetPosX(),
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
		for (int i{ 1 }; i < vOBJ_INST.size(); i++)
			RenderObject(vOBJ_INST[i]);
		AnimationHandler::AnimateCharacter(p_player);
	}

	void Level2_Free()
	{
		for (size_t i{ 0 }; i < vOBJ.size(); i++)
			AEGfxMeshFree(vOBJ[i].pMesh);
	}

	void Level2_Unload()
	{
		for (size_t i{ 0 }; i < vOBJ.size(); i++)
			AEGfxTextureUnload(vOBJ[i].pTex);
		vOBJ.clear();
		vOBJ_INST.clear();
	}
}