#include "GSM.h"
#include "Enum.h"
#include "Level1.h"
#include "Level2.h"
#include "MainMenu.h"

namespace GSM
{
	int current{Enum::GS_LEVEL2}, previous{0}, next{0};
	f64 gameTime;
	FP fpLoad = nullptr, fpInit = nullptr, fpUpdate = nullptr, fpDraw = nullptr, fpFree = nullptr, fpUnload = nullptr;

	void GSM_Init(int start)
	{
		current = previous = next = start;
	}

	void GSM_Update()
	{
		using namespace Enum;
		switch (current)
		{
		case GS_QUIT:
			break;
		case GS_MENU:
			fpLoad = MainMenu::MainMenu_Load;
			fpInit = MainMenu::MainMenu_Init;
			fpUpdate = MainMenu::MainMenu_Update;
			fpDraw = MainMenu::MainMenu_Draw;
			fpFree = MainMenu::MainMenu_Free;
			fpUnload = MainMenu::MainMenu_Unload;
			break;
		case GS_LEVEL1:
			fpLoad = Level1::Level1_Load;
			fpInit = Level1::Level1_Init;
			fpUpdate = Level1::Level1_Update;
			fpDraw = Level1::Level1_Draw;
			fpFree = Level1::Level1_Free;
			fpUnload = Level1::Level1_Unload;
			break;
		case GS_LEVEL2:
			fpLoad = Level2::Level2_Load;
			fpInit = Level2::Level2_Init;
			fpUpdate = Level2::Level2_Update;
			fpDraw = Level2::Level2_Draw;
			fpFree = Level2::Level2_Free;
			fpUnload = Level2::Level2_Unload;
			break;
		case GS_RESTART:
			break;
		}
	}
}
