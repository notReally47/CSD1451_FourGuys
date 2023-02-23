#pragma once
#include "GameObjects.h"
namespace InputHandler
{
	void MoveObject(float&, float&);
	void ChangeTexture(float&, float&);
	void MoveCamera(float&, float&);
	void ExitGame(int&);
	bool PlayerMovement(GameObjects::Character& player);
	bool PlayerJump(GameObjects::Character& player);
	bool buttonClick(s32 mouseX, s32 mouseY, float buttonX, float buttonY);
}

