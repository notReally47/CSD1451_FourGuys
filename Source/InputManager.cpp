/*!***********************************************************************
  \file   InputManager.cpp
  \authors 
  
  \brief 
  This file contains the implementation of the input manager

  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "PCH.h"
#include "InputManager.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

namespace IM
{
	/*DEFINES*/
	const static f32 GRAVITY		= -1000.f;
	const static f32 JUMP_HEIGHT	= 50.f;

	/*COMMON NAMESPACE*/
	using namespace OM;

	/*!***********************************************************************
	  \brief Checks if escape key is pressed
	  
	  \param next 
	*************************************************************************/
	void ExitGame(GAME_STATES next) {
		if (AEInputCheckTriggered(AEVK_ESCAPE))
			next = GAME_STATES::QUIT;
	}
	/*!***********************************************************************
	  \brief Checks if the player is moving
	  
	  \param player 
	  \return true 
	  \return false 
	*************************************************************************/
	bool PlayerMovement(Character& player) {
		AEVec2 dir{ .0f,.0f };
		if (AEInputCheckCurr(AEVK_A)) {
			dir.x--;
		}
		if (AEInputCheckCurr(AEVK_D)) {
			dir.x++;
		}
		if (AEInputCheckCurr(AEVK_W)) {
			dir.y++;
		}
		if (AEInputCheckCurr(AEVK_S)) {
			dir.y--;
		}

		player.input = dir;
		player.dir = dir;
		return dir.x || dir.y;
	}
	/*!***********************************************************************
	  \brief Checks if the player is jumping
	  
	  \param player 
	  \return true 
	  \return false 
	*************************************************************************/
	bool PlayerJump(Character& player) {
		player.zVel = GRAVITY * (f32)AEFrameRateControllerGetFrameTime() + player.zVel;

		if (AEInputCheckTriggered(AEVK_SPACE) && player.pOI->GetPosZ() == 0) {
			player.zVel = sqrt(2 * -GRAVITY * (JUMP_HEIGHT));
		}

		player.pOI->GetPosZ() = player.zVel * (f32)AEFrameRateControllerGetFrameTime() + player.pOI->GetPosZ();
		if (player.pOI->GetPosZ() < 0)
			player.pOI->GetPosZ() = 0;

		return player.pOI->GetPosZ() > 0;
	}
	/*!***********************************************************************
	  \brief Checks if the mouse clicked on a button
	  
	  \param mouseX 
	  \param mouseY 
	  \param buttonX 
	  \param buttonY 
	  \return true 
	  \return false 
	*************************************************************************/
	bool ButtonClick(float buttonX, float buttonY)
	{
		s32 mouseX, mouseY;
		AEInputGetCursorPosition(&mouseX, &mouseY);
		if (AEInputCheckReleased(AEVK_LBUTTON) && mouseX <= static_cast<s32>(AEGetWindowWidth() / 2 + (buttonX + 50.f)) && mouseX >= static_cast<s32>(AEGetWindowWidth() / 2 + (buttonX - 50.f)) && mouseY <= static_cast<s32>(AEGetWindowHeight() / 2 + (buttonY + 25.f)) && mouseY >= static_cast<s32>(AEGetWindowHeight() / 2 + (buttonY - 25.f)))
			return true;
		return false;
	}
	void PlayerInteractionF(Character& player, std::vector<ObjectInst>& obj, size_t index)
	{
		if (AEInputCheckCurr(AEVK_F))
		{
			for (size_t i{ 0 }; i < obj.size(); i++)
			{
				if (i == index)
					continue;
				if (obj[i].pO->type == TYPE::WALL && obj[i].flag & Enum::FLAG::DOOR && obj[i].flag & Enum::FLAG::ACTIVE )
				{
					AEVec2 pos{};
					pos.x = obj[i].GetPos().x + obj[i].GetPosZ();
					pos.y = obj[i].GetPos().y + obj[i].GetPosZ();
					player.pOI->transf.m[0][2] = pos.x;
					player.pOI->transf.m[1][2] = pos.y;
				}
			}
		}
	}

	
}