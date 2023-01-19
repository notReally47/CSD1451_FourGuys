#pragma once
#include "GameObjects.h"
namespace InputHandler
{
	void MoveObject(float&, float&);
	void ChangeTexture(float&, float&);
	void MoveCamera(float&, float&);
	void ExitGame(int&);
	int playerMovement(GameObjects::Character& player);
}

