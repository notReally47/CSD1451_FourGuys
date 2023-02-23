#pragma once
#include "GameObjects.h"
namespace InputHandler
{
	void MoveObject(float&, float&);
	void ChangeTexture(float&, float&);
	void MoveCamera(float&, float&);
	void ExitGame(int&);
	bool playerMovement(GameObjects::Character& player);
	bool buttonClick(float buttonX, float buttonY);
	bool PlayerJump(GameObjects::Character& player);
}

