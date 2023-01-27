#pragma once

namespace Enum {
	enum GAME_STATES {
		GS_RESTART,
		GS_LEVEL1,
		GS_LEVEL2,
		GS_MENU,
		GS_QUIT = -1
	};

	enum CHARACTER_STATES {
		CS_IDLE,
		CS_MOVING
	};
	
	enum DIRECTION {
		NONE,
		RIGHT,
		LEFT
	};

	enum TYPE {
		PLAYER,
		WALL,
		FLOOR,
		DECO,
		PORTRAIT,
		PLATFORM
	};
}
