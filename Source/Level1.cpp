#include "PCH.h"
#include "InputManager.h"
#include "CollisionDetectionManager.h"
#include "FileManager.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace GSM
{
	/*DEFINES*/
	const static std::string level_number = "01";
	const static f32 MIN_CAM_HEIGHT = -65.f;

	OM::Character player;
	std::vector<OM::Object> vOBJ;
	std::vector<OM::ObjectInst> vOBJ_INST;
	OM::Character* sCHARACTER;

	void Level1::Level1_Load()
	{
		vOBJ = Load_Data_From_File::Load_Shape_From_YAML(level_number);
		vOBJ_INST = Load_Data_From_File::Load_Transform_From_YAML(level_number, vOBJ);
		sCHARACTER = Load_Data_From_File::Load_Player_Stats_From_YAML(level_number);
	}

	void Level1::Level1_Init()
	{
		/*CREATE PLAYER*/
		Level_Initializer::Init_Player(&vOBJ_INST[0], sCHARACTER, player);

		/*SCALE OBJECTS*/
		Level_Initializer::Option_Change(vOBJ_INST);

		/*DO NOT DELETE*/

		//for (auto& it : vOBJ_INST) {
			//AEVec2 a{ it.GetPosY() + (it.GetPosX() / 2.0f ), it.GetPosY() - (it.GetPosX() / 2.0f) };
			//it.GetPosX() = a.x;
			//it.GetPosY() = a.y;
		//}

		/*Extract Using Vector vOBJ_INST & p_player*/
		Extract_Data_To_File::Extract_Transform_Data_Out(vOBJ_INST, player, level_number);
	}

	void Level1::Level1_Update()
	{
		using namespace Enum;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);

		/*SET PLAYER BIT FLAG FOR MOVEMENT OR JUMPING*/
		unsigned long& flag{ player.pObjInst->flag };
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
	void Level1::Level1_Draw()
	{
		OM::RenderSettings();
		// Initialise i to 1 to skip player
		for (int i{ 1 }; i < vOBJ_INST.size(); i++)
			vOBJ_INST[i].RenderObject();
		player.AnimateCharacter();
	}

	void Level1::Level1_Free()
	{
		for (size_t i{ 0 }; i < vOBJ.size(); i++)
			AEGfxMeshFree(vOBJ[i].pMesh);
		vOBJ_INST.clear();
	}

	void Level1::Level1_Unload()
	{
		for (size_t i{ 0 }; i < vOBJ.size(); i++)
			AEGfxTextureUnload(vOBJ[i].pTex);
		vOBJ.clear();

	}
}
