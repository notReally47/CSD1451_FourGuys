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
	using namespace GSM;

	//// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	/*INITIALIZATIONS*/
	EM::WindowCreate(hInstance, nCmdShow);

	AE_ASSERT_MESG(GSM::fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12), "Failed to load font");

	Initialise(GAME_STATES::LEVEL1);
	
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