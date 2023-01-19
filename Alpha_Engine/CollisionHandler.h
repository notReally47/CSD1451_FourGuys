#pragma once
#include "pch.h"

namespace CollisionHandler {
	using namespace GameObjects;
	bool Collided(GameObjects::Object obj1, GameObjects::Object obj2);
	void ResetPosition(GameObjects::Character& movingObj, int direction);
}
