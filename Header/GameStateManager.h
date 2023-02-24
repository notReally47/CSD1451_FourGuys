#pragma once
#include "Enumeration.h"

/*DEFINES*/
typedef void(*FP)(void);

namespace GSM
{
	struct GameStateManager
	{
		/*CONSTRUCTORS*/
		GameStateManager();
		~GameStateManager();

		/*MEMBER FUNCTIONS*/
		void				Initialise(GAME_STATES);
		void				Update();

		/*PUBLIC DATA*/
		FP					fpLoad;
		FP					fpInit;
		FP					fpUpdate;
		FP					fpDraw;
		FP					fpFree;
		FP					fpUnload;
		GAME_STATES			current;
		GAME_STATES			previous;
		GAME_STATES			next;
	};

	struct Level1
	{
		/*MEMBER FUNCTIONS*/
		void				Level1_Load();
		void				Level1_Init();
		void				Level1_Update();
		void				Level1_Draw();
		void				Level1_Free();
		void				Level1_Unload();
	};

	struct MainMenu
	{
		/*MEMBER FUNCTIONS*/
		void				MainMenu_Load();
		void				MainMenu_Init();
		void				MainMenu_Update();
		void				MainMenu_Draw();
		void				MainMenu_Free();
		void				MainMenu_Unload();
	};

	struct Options
	{
		/*MEMBER FUNCTIONS*/
		void				Options_Load();
		void				Options_Init();
		void				Options_Update();
		void				Options_Draw();
		void				Options_Free();
		void				Options_Unload();
	};
}
