#include "Level2.h"
#include "pch.h"
#include "InputHandler.h"
#include "CollisionHandler.h"
#include "PhysicsHandler.h"
#include "GSM.h"
#include "DataFiles.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace Level2
{
	/*DEFINES*/
	const static std::string level_number = "02";
	const static f32 MIN_CAM_HEIGHT = -65.f;
	using namespace GameObjects;

	Character p_player;
	std::vector<Object> vOBJ;
	std::vector<ObjectInst> vOBJ_INST;
	Character* sCHARACTER;

	void Level2_Load() 
	{
		vOBJ = Load_Data_From_File::Load_Shape_From_YAML(level_number);
		vOBJ_INST = Load_Data_From_File::Load_Transform_From_YAML(level_number, vOBJ);
		sCHARACTER = Load_Data_From_File::Load_Player_Stats_From_YAML(level_number);
	}

	void Level2_Init()
	{
		/*CREATE PLAYER*/
		Level_Initializer::Init_Player(&vOBJ_INST[0], sCHARACTER, p_player);

		/*SCALE OBJECTS*/
		Level_Initializer::Option_Change(vOBJ_INST);

		/*DO NOT DELETE*/
		
		//for (auto& it : vOBJ_INST) {
			//AEVec2 a{ it.GetPosY() + (it.GetPosX() / 2.0f ), it.GetPosY() - (it.GetPosX() / 2.0f) };
			//it.GetPosX() = a.x;
			//it.GetPosY() = a.y;
		//}

		/*Extract Using Vector vOBJ_INST & p_player*/
		Extract_Data_To_File::Extract_Transform_Data_Out(vOBJ_INST, p_player, level_number);
	}

	void Level2_Update()
	{
		using namespace Enum;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);

		/*SET PLAYER BIT FLAG FOR MOVEMENT OR JUMPING*/
		unsigned long& flag{ p_player.pObjInst->flag };
		flag = (InputHandler::PlayerJump(p_player)) ? flag | JUMPING : flag & ~JUMPING;
		flag = (InputHandler::PlayerMovement(p_player)) ? flag | ACTIVE : flag & ~ACTIVE;

		/*MOVEMENT*/
		//PhysicsHandler::Move::MoveCharacter();
		p_player.MoveCharacter();

		//check if player if near portrait
		for (size_t i{ 0 }; i < vOBJ_INST.size(); i++)
		{
			if (vOBJ_INST[i].pObj->type == PORTRAIT || vOBJ_INST[i].pObj->type == LANDSCAPE)
			{
				vOBJ_INST[i].flag = (CollisionHandler::GetDistance(vOBJ_INST[i].GetPosX(),
					vOBJ_INST[i].GetPosY(), p_player.pObjInst->GetPosX(),
					p_player.pObjInst->GetPosY()) < 40.0) ? static_cast<unsigned long>(ACTIVE) : IDLE;
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
			vOBJ_INST[i].RenderObject();
		p_player.AnimateCharacter();
	}

	void Level2_Free()
	{
		for (size_t i{ 0 }; i < vOBJ.size(); i++)
			AEGfxMeshFree(vOBJ[i].pMesh);
		vOBJ_INST.clear();
	}

	void Level2_Unload()
	{
		for (size_t i{ 0 }; i < vOBJ.size(); i++)
			AEGfxTextureUnload(vOBJ[i].pTex);
		vOBJ.clear();

	}
}