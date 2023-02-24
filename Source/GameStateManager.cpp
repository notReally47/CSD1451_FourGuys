#include "PCH.h"

namespace GSM
{
	GameStateManager::GameStateManager()
	{
		using enum GAME_STATES;

		this->fpLoad		= nullptr;
		this->fpInit		= nullptr;
		this->fpUpdate		= nullptr;
		this->fpDraw		= nullptr;
		this->fpFree		= nullptr;
		this->fpUnload		= nullptr;

		this->current		= RESTART;
		this->previous		= RESTART;
		this->next			= RESTART;

		gameTime			= .0f;
	}

	GameStateManager::~GameStateManager()
	{

	}

	void GameStateManager::Initialise(GAME_STATES start)
	{
		this->current		= this->previous
							= this->next
							= start;
	}

	void GameStateManager::Update()
	{
		using enum			GAME_STATES;

		switch (this->current) {
		case QUIT:
			break;
		case MAINMENU:
			this->fpLoad	= MainMenu::MainMenu_Load;
			this->fpInit	= MainMenu::MainMenu_Init;
			this->fpUpdate	= MainMenu::MainMenu_Update;
			this->fpDraw	= MainMenu::MainMenu_Draw;
			this->fpFree	= MainMenu::MainMenu_Free;
			this->fpUnload	= MainMenu::MainMenu_Unload;
			break;
		case LEVEL1:
			this->fpLoad	= Level1::Level1_Load;
			this->fpInit	= Level1::Level1_Init;
			this->fpUpdate	= Level1::Level1_Update;
			this->fpDraw	= Level1::Level1_Draw;
			this->fpFree	= Level1::Level1_Free;
			this->fpUnload	= Level1::Level1_Unload;
			break;
		case RESTART:
			break;
		}
	}
}
