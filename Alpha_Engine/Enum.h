#pragma once

namespace Enum {
	enum GAME_STATES {
		GS_RESTART,
		GS_LEVEL1,
		GS_LEVEL2,
		GS_MENU,
		GS_QUIT = -1
	};

	enum DIRECTION : int {
		UPRIGHT,
		RIGHT,
		DOWNRIGHT,
		DOWN,
		DOWNLEFT,
		LEFT,
		UPLEFT,
		UP
	};

	enum TYPE : unsigned long {
		PLAYER,
		FLOOR,
		WALL,
		DECO,
		PORTRAIT,
		LANDSCAPE,
		PLATFORM
	};

	enum FLAG : unsigned long {
		IDLE,
		ACTIVE,
		JUMPING,
		ISO_UP,
		ISO_DOWN,
		ISO_LEFT,
		ISO_RIGHT,
		DOOR
	};
}
