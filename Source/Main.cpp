/*!***********************************************************************
  \file   Main.cpp
  \authors

  \brief
  This file contains the main function of the game

  \copyright
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "PCH.h"
#include "InputManager.h"
#include "EnvironmentManager.h"
#include <memory> // debug memory
#define DEBUG

/*!***********************************************************************
  \brief The main function of the game

  \param hInstance
  \param hPrevInstance
  \param lpCmdLine
  \param nCmdShow
  \return int
*************************************************************************/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR lpCmdLine,
					  _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	/*COMMON NAMESPACES*/
	using namespace GSM;

	//// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	/*INITIALIZATIONS*/
	EM::WindowCreate(hInstance, nCmdShow);

	AE_ASSERT_MESG(GSM::fontId = AEGfxCreateFont("../Resource/Font/fude.ttf", 24), "Failed to load font");

	Initialise(GAME_STATES::MAINMENU);

	/*GAME LOOP*/
	while (current != GAME_STATES::QUIT)
	{
		if (current != GAME_STATES::RESTART)
		{
			Update();
			fpLoad();
		}
		else
		{
			next = previous;
			current = previous;
		}

		fpInit();

		while (next == current)
		{
			AESysFrameStart();
			AEInputUpdate();
			fpUpdate();
			fpDraw();
			AESysFrameEnd();
			// check if forcing the application to quit
			if ((AESysDoesWindowExist() == false))
				next = GAME_STATES::QUIT;
			GSM::gameTime = static_cast<f32>(AEFrameRateControllerGetFrameTime());
		}

		fpFree();

		if (next != GAME_STATES::RESTART)
		{
			fpUnload();
		}

		previous = current;
		current = next;
	}

	AEGfxDestroyFont(GSM::fontId);
	AESysExit();
}