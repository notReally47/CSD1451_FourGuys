#pragma once

namespace Enum {


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
		DOOR,
		JUMPING,
		ISO_UP,
		ISO_DOWN,
		ISO_LEFT,
		ISO_RIGHT,
		
		// PORTRAITS
		GLOW,
		VERTICAL,		
		HORIZONTAL
	};

	enum SLOPE : unsigned long {
		NONE,
		NORTH,
		SOUTH,
		EAST,
		WEST
	};
}

enum class GAME_STATES : int {
	RESTART,
	LEVEL1,
	MAINMENU,
	OPTIONS,
	QUIT = -1
};


