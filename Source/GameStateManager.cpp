/*!***********************************************************************
  \file   GameStateManager.cpp
  \authors

  \brief 
  This file contains the implementation of the game state manager

  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "PCH.h"

namespace GSM
{
	FP
	fpLoad		= nullptr,
	fpInit		= nullptr,
	fpUpdate	= nullptr,
	fpDraw		= nullptr,
	fpFree		= nullptr,
	fpUnload	= nullptr;

	GAME_STATES
	current		= GAME_STATES::RESTART,
	previous	= GAME_STATES::RESTART,
	next		= GAME_STATES::RESTART;

	f32 
	gameTime 	= .0f;
	s8	
	fontId		= 0;

	/*!***********************************************************************
	  \brief Initialise the game state manager
	  
	  \param start 
	*************************************************************************/
	void Initialise(GAME_STATES start)
	{
		current		= previous
					= next
					= start;
	}

	/*!***********************************************************************
	  \brief Update the game state manager
	  
	*************************************************************************/
	void Update()
	{
		switch (current) {
		case GAME_STATES::QUIT:
			break;
		case GAME_STATES::MAINMENU:
		using namespace Menu;
			fpLoad		= Menu_Load;
			fpInit		= Menu_Init;
			fpUpdate	= Menu_Update;
			fpDraw		= Menu_Draw;
			fpFree		= Menu_Free;
			fpUnload	= Menu_Unload;
			break;
		case GAME_STATES::LEVEL1:
		using namespace Level1;
			fpLoad		= Level1_Load;
			fpInit		= Level1_Init;
			fpUpdate	= Level1_Update;
			fpDraw		= Level1_Draw;
			fpFree		= Level1_Free;
			fpUnload	= Level1_Unload;
			break;
		case GAME_STATES::RESTART:
			break;
		}
	}
}