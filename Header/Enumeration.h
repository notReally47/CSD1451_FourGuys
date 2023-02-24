#pragma once

namespace
{
	/*EXTERN*/
	extern s8				fontId;
	extern f32				gameTime;
}

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
		JUMPING,
		ISO_UP,
		ISO_DOWN,
		ISO_LEFT,
		ISO_RIGHT,
		DOOR
	};
}

enum class GAME_STATES : int {
	RESTART,
	LEVEL1,
	MAINMENU,
	OPTIONS,
	QUIT = -1
};


