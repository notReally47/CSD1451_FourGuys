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
namespace Level1
{
	/*DEFINES*/
	const static std::string level_number = "02";
	const static f32 MIN_CAM_HEIGHT = -65.f;
	using namespace GameObjects;
	Character p_player;
	// char str[100];
	// std::string strBuffer;
	// int cont{};
	// const std::string text = "Tutorial this is a portrait, and you can interact with it by pressing the F";
	std::vector<Object> vOBJ;
	std::vector<ObjectInst> vOBJ_INST;
	Character *sCHARACTER;
	Object bubble;
	ObjectInst objInst[1];

	void Level1_Load()
	{
		vOBJ = Load_Data_From_File::Load_Shape_From_YAML(level_number);
		vOBJ_INST = Load_Data_From_File::Load_Transform_From_YAML(level_number, vOBJ);
		sCHARACTER = Load_Data_From_File::Load_Player_Stats_From_YAML(level_number);

		using namespace GameObjects;
		bubble.type = Enum::TYPE::BUBBLE;
	}

	/*INITIALIZE DATA*/
	void Level1_Init()
	{
		/*CREATE PLAYER*/
		Level_Initializer::Init_Player(&vOBJ_INST[0], sCHARACTER, p_player);

		/*SCALE OBJECTS*/
		Level_Initializer::Option_Change(vOBJ_INST);

		/*DO NOT DELETE*/

		// for (auto& it : vOBJ_INST) {
		// AEVec2 a{ it.GetPosY() + (it.GetPosX() / 2.0f ), it.GetPosY() - (it.GetPosX() / 2.0f) };
		// it.GetPosX() = a.x;
		// it.GetPosY() = a.y;
		//}

		/*Extract Using Vector vOBJ_INST & p_player*/
		Extract_Data_To_File::Extract_Transform_Data_Out(vOBJ_INST, p_player, level_number);

		// strBuffer = "";

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
			0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 1.0f);
		// Saving the mesh (list of triangles) in pMesh
		bubble.pMesh = AEGfxMeshEnd();
		objInst[0].pObj = &bubble;
		objInst[0].flag = Enum::FLAG::IDLE;
		objInst[0].tex_offset = {.0f, .0f};
		objInst[0].transform = {150.f, .0f, .0f + .0f,
								.0f, 150.0f, 0.f,
								.0f, .0f, .0f};
		objInst[0].pObj->pTex = AEGfxTextureLoad("../Assets/Textures/bubble.jpg");
	}

	void Level1_Update()
	{
		using namespace Enum;
		/*HANDLE INPUT*/
		InputHandler::ExitGame(GSM::next);

		/*SET PLAYER BIT FLAG FOR MOVEMENT OR JUMPING*/
		unsigned long &flag{p_player.pObjInst->flag};
		flag = (InputHandler::PlayerJump(p_player)) ? flag | JUMPING : flag & ~JUMPING;
		flag = (InputHandler::PlayerMovement(p_player)) ? flag | ACTIVE : flag & ~ACTIVE;

		// collision detection for isometric

		/*MOVEMENT*/
		// PhysicsHandler::Move::MoveCharacter();
		p_player.MoveCharacter();

		// check if player if near portrait
		for (size_t i{0}; i < vOBJ_INST.size(); i++)
		{

			if (vOBJ_INST[i].pObj->type == PORTRAIT || vOBJ_INST[i].pObj->type == LANDSCAPE)
			{
				vOBJ_INST[i].flag = (CollisionHandler::GetDistance(vOBJ_INST[i].GetPosX(),
																   vOBJ_INST[i].GetPosY(), vOBJ_INST[i].transform.m[0][0], vOBJ_INST[i].transform.m[1][1], p_player.pObjInst->GetPosX(),
																   p_player.pObjInst->GetPosY()) < 10.0)
										? static_cast<unsigned long>(ACTIVE)
										: IDLE;
				if (vOBJ_INST[i].flag == ACTIVE)
				{
					objInst[0].GetPosX() = vOBJ_INST[i].GetPosX();
					objInst[0].GetPosY() = vOBJ_INST[i].GetPosY();
					objInst[0].GetPosZ() = vOBJ_INST[i].GetPosZ() + 100.0f;
					objInst[0].flag = ACTIVE;
				}
			}
			//! When player reaches the door, set the flag ( |= isUnlocked).
			//! TODO because of wall sprite offset issue
			// if (vOBJ_INST[i].pObj->type == WALL && vOBJ_INST[i].flag == DOOR ){
			// 	if(CollisionHandler::GetDistance(vOBJ_INST[i].GetPosX() ,
			// 		vOBJ_INST[i].GetPosY() + vOBJ_INST[i].GetPosZ(), vOBJ_INST[i].transform.m[0][0] ,vOBJ_INST[i].transform.m[1][1] ,p_player.pObjInst->GetPosX(),
			// 		p_player.pObjInst->GetPosY()) == 0.0){
			// 			std::cout << "inside\n";
			// 		vOBJ_INST[i].flag |= static_cast<unsigned long>(ACTIVE);
			// 		}
			// }
		}
		if (objInst[0].flag == ACTIVE)
		{
			// if(std::strlen(str) < 99)
			// if (cont < text.size())
			// // add to string buffer one letter each frame
			// {
			// 	strBuffer += text[cont];
			// 	cont++;
			// }
			objInst[0].GetElapsed() += GSM::gameTime;
		}
		if (objInst[0].GetElapsed() > 3.f)
		{

			objInst[0].flag = IDLE;
			objInst[0].GetElapsed() = {};
		}
		InputHandler::PlayerInteractionF(p_player);

		/*COLLISIONS*/
		// TODO: Collision
		/*ANIMATION*/
		AEGfxSetCamPosition(0.f, max(p_player.pObjInst->GetPosY(), MIN_CAM_HEIGHT));
	}

	void Level1_Draw()
	{
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		RenderSettings();
		// Initialise i to 1 to skip player
		for (int i{1}; i < vOBJ_INST.size(); i++)
			vOBJ_INST[i].RenderObject();
		p_player.AnimateCharacter();
		if (objInst[0].flag == Enum::FLAG::ACTIVE)
		{
			objInst[0].RenderObject();
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			// memset(str, 0, 10 * sizeof(char));
			// sprintf_s(str, strBuffer.c_str());
			// AEGfxPrint(fontId, str, GetScreenXPercentage(-93), GetScreenYPercentage(50), 1.0f, 0.0f, 0.f, 0.f);
		}
	}

	void Level1_Free()
	{
		for (size_t i{0}; i < vOBJ.size(); i++)
			AEGfxMeshFree(vOBJ[i].pMesh);
		vOBJ_INST.clear();
		AEGfxMeshFree(objInst[0].pObj->pMesh);
	}

	void Level1_Unload()
	{
		for (size_t i{0}; i < vOBJ.size(); i++)
			AEGfxTextureUnload(vOBJ[i].pTex);
		vOBJ.clear();
		AEGfxTextureUnload(objInst[0].pObj->pTex);
	}
}