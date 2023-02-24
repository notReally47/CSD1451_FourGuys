#include "PCH.h"
#include "InputManager.h"
#include "EnvironmentManager.h"
#include <memory> // debug memory
#define DEBUG

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	/*COMMON NAMESPACES*/
	using enum GAME_STATES;

	//// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	/*INITIALIZATIONS*/
	EM::Window System;

	System.Create(hInstance, nCmdShow);
	//AE_ASSERT_MESG(fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12), "Failed to load font");
	
	GSM::GameStateManager GSM;

	GSM.Initialise(LEVEL1);
	
	/*GAME LOOP*/
	while (GSM.current != QUIT)
	{
		if (GSM.current != RESTART)
		{
			GSM.Update();
			GSM.fpLoad();
		}
		else
		{
			GSM.next = GSM.previous;
			GSM.current = GSM.previous;
		}

		GSM.fpInit();

		while (GSM.next == GSM.current)
		{
			AESysFrameStart();
			AEInputUpdate();
			GSM.fpUpdate();
			GSM.fpDraw();
			gameTime = static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AESysFrameEnd();
		}

		GSM.fpFree();

		if (GSM.next != RESTART)
		{
			GSM.fpUnload();
		}

		GSM.previous = GSM.current;
		GSM.current = GSM.next;
	}

	AEGfxDestroyFont(fontId);
	AESysExit();
}