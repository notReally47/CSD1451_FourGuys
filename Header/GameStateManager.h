#pragma once
#include "Enumeration.h"
#include "AEEngine.h"

namespace GSM
{
	/*DEFINES*/
	typedef void(*FP)(void);

	extern f32					gameTime;
	extern s8					fontId;

	extern FP					fpLoad;
	extern FP					fpInit;
	extern FP					fpUpdate;
	extern FP					fpDraw;
	extern FP					fpFree;
	extern FP					fpUnload;
	extern GAME_STATES			current;
	extern GAME_STATES			previous;
	extern GAME_STATES			next;

	void				Initialise(GAME_STATES);
	void				Update();
}

namespace Level1
{
	void				Level1_Load();
	void				Level1_Init();
	void				Level1_Update();
	void				Level1_Draw();
	void				Level1_Free();
	void				Level1_Unload();
};

namespace Menu
{
	void				Menu_Load();
	void				Menu_Init();
	void				Menu_Update();
	void				Menu_Draw();
	void				Menu_Free();
	void				Menu_Unload();
};

namespace Options
{
	void				Options_Load();
	void				Options_Init();
	void				Options_Update();
	void				Options_Draw();
	void				Options_Free();
	void				Options_Unload();
};
