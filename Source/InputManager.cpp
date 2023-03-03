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

		if (AEInputCheckTriggered(AEVK_SPACE) && player.pObjInst->GetPosZ() == 0) {
			player.zVel = sqrt(2 * -GRAVITY * (JUMP_HEIGHT));
		}

		player.pObjInst->GetPosZ() = player.zVel * (f32)AEFrameRateControllerGetFrameTime() + player.pObjInst->GetPosZ();
		if (player.pObjInst->GetPosZ() < 0)
			player.pObjInst->GetPosZ() = 0;

		return player.pObjInst->GetPosZ() > 0;
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
	bool ButtonClick(s32 mouseX, s32 mouseY, float buttonX, float buttonY) {
		AEInputGetCursorPosition(&mouseX, &mouseY);
		if (AEInputCheckReleased(AEVK_LBUTTON) && mouseX <= static_cast<s32>(buttonX + 100.f) && mouseX >= static_cast<s32>(buttonX)
			&& mouseY <= static_cast<s32>(buttonY + 50.f) && mouseY >= static_cast<s32>(buttonY))
		{
			std::cout << "true\n";
			return true;
		}
		return false;
	}
}