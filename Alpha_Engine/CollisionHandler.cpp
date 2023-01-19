#include "CollisionHandler.h"
#include "pch.h"

namespace CollisionHandler {
	using namespace GameObjects;

	/*AABB Collision*/
	bool Collided(Object obj1, Object obj2) {
		return obj1.pos.x - (obj1.width) < obj2.pos.x + (obj2.width) &&
			obj1.pos.x + (obj1.width) > obj2.pos.x - (obj2.width) &&
			obj1.pos.y - (obj1.height) < obj2.pos.y + (obj2.height) &&
			obj1.pos.y + (obj1.height) > obj2.pos.y - (obj2.height);
	}

	void ResetPosition(Character &movingObj, int direction) {
		switch (direction) {
		case Enum::RIGHT:
			//movingObj.obj.pos.x -= movingObj.velocity_x * AEFrameRateControllerGetFrameTime();
			movingObj.velocity_x = -movingObj.velocity_x;
			break;
		case Enum::LEFT:
			//movingObj.obj.pos.x -= movingObj.velocity_x * AEFrameRateControllerGetFrameTime();
			movingObj.velocity_x = -movingObj.velocity_x;
			break;
		default:
			break;
		}
	}
}