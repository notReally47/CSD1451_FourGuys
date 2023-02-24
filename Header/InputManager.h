#pragma once
#include "ObjectManager.h"

namespace IM
{
	struct Input
	{
		void ExitGame(GAME_STATES);
		bool PlayerMovement(OM::Character& player);
		bool PlayerJump(OM::Character& player);
		bool buttonClick(s32 mouseX, s32 mouseY, float buttonX, float buttonY);
	};	
}

