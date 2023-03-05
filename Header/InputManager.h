#pragma once
#include "ObjectManager.h"
#include <vector>
namespace IM
{
	void ExitGame(GAME_STATES);
	bool PlayerMovement(OM::Character& player);
	bool PlayerJump(OM::Character& player);
	bool ButtonClick(s32 mouseX, s32 mouseY, float buttonX, float buttonY);
	void PlayerInteractionF(OM::Character& player, std::vector<OM::ObjectInst>& obj, size_t index);
}

