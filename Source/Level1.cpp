/*!***********************************************************************
  \file   Level1.cpp
  \authors 
  
  \brief 
  This file contains the implementation of the level 1
  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "PCH.h"
#include "InputManager.h"
#include "CollisionDetectionManager.h"
#include "FileManager.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace Level1
{
	/*DEFINES*/
	const static std::string level_number = "01";
	const static f32 MIN_CAM_HEIGHT = -65.f;

	OM::Character player;
	FM::Import ImportData;
	FM::Export ExportData;
	OM::Character* sCHARACTER;
	
	/*!***********************************************************************
	  \brief Load level 1 data
	  
	*************************************************************************/
	void Level1_Load()
	{
		ImportData.vO = *ImportData.Load_Shape_From_YAML(level_number);
		ImportData.vOI = *ImportData.Load_Transform_From_YAML(level_number);
		sCHARACTER = ImportData.Load_Player_Stats_From_YAML(level_number);
	}
	
	/*!***********************************************************************
	  \brief Initialise level 1
	  
	*************************************************************************/
	void Level1_Init()
	{ 
		/*CREATE PLAYER*/
		FM::Init_Player(&ImportData.vOI[0], sCHARACTER, player);

		/*SCALE OBJECTS*/
		FM::Option_Change(ImportData.vOI);

		/*DO NOT DELETE*/

		//for (auto& it : vOBJ_INST) {
			//AEVec2 a{ it.GetPosY() + (it.GetPosX() / 2.0f ), it.GetPosY() - (it.GetPosX() / 2.0f) };
			//it.GetPosX() = a.x;
			//it.GetPosY() = a.y;
		//}

		/*Extract Using Vector vOBJ_INST & player*/
		ExportData.Extract_Transform_Data_Out(ImportData.vOI, player, level_number);
	}

	/*!***********************************************************************
	  \brief Update player and objects based on input and collisions
	  
	*************************************************************************/
	void Level1_Update()
	{
		using namespace Enum;
		/*HANDLE INPUT*/
		IM::ExitGame(GSM::next);

		/*SET PLAYER BIT FLAG FOR MOVEMENT OR JUMPING*/
		unsigned long& flag{ player.pObjInst->flag };
		flag = (IM::PlayerJump(player)) ? flag | JUMPING : flag & ~JUMPING;
		flag = (IM::PlayerMovement(player)) ? flag | ACTIVE : flag & ~ACTIVE;

		/*MOVEMENT*/
		//PhysicsHandler::Move::MoveCharacter();
		player.MoveCharacter();

		//check if player if near portrait
		for (size_t i{ 0 }; i < ImportData.vOI.size(); i++)
		{
			if (ImportData.vOI[i].pObj->type == PORTRAIT || ImportData.vOI[i].pObj->type == LANDSCAPE)
			{
				ImportData.vOI[i].flag = (CDM::GetDistance(ImportData.vOI[i].GetPosX(),
					ImportData.vOI[i].GetPosY(), player.pObjInst->GetPosX(),
					player.pObjInst->GetPosY()) < 40.0) ? static_cast<unsigned long>(ACTIVE) : IDLE;
			}
		}

		/*COLLISIONS*/
		//TODO: Collision

		/*ANIMATION*/
		AEGfxSetCamPosition(0.f, max(player.pObjInst->GetPosY(), MIN_CAM_HEIGHT));
	}

	/*!***********************************************************************
	  \brief Render game objects
	  
	*************************************************************************/
	void Level1_Draw()
	{
		OM::RenderSettings();
		// Initialise i to 1 to skip player
		for (int i{ 1 }; i < ImportData.vOI.size(); i++)
			ImportData.vOI[i].RenderObject();
		player.AnimateCharacter();
	}

	/*!***********************************************************************
	  \brief Free level 1 data
	  
	*************************************************************************/
	void Level1_Free()
	{
		for (size_t i{ 0 }; i < ImportData.vO.size(); i++)
			AEGfxMeshFree(ImportData.vO[i].pMesh);
		ImportData.vOI.clear();
	}

	/*!***********************************************************************
	  \brief Unload level 1 data
	  
	*************************************************************************/
	void Level1_Unload()
	{
		for (size_t i{ 0 }; i < ImportData.vO.size(); i++)
			AEGfxTextureUnload(ImportData.vO[i].pTex);
		ImportData.vO.clear();

	}
}
