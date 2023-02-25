#include "AEEngine.h"
#include "GSM.h"
#include "Enum.h"
#include "InputHandler.h"
#include "SystemHandler.h"
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
	using namespace Enum;
	using namespace GameObjects;

	//// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	/*INITIALIZATIONS*/
	SystemHandler::System_Initialize(hInstance, nCmdShow);
	//AE_ASSERT_MESG(fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12), "Failed to load font");
	GSM_Init(current);

	/*GAME LOOP*/
	while (current != GS_QUIT) {
		if (current != GS_RESTART) {
			GSM_Update();
			fpLoad();
		}
		else {
			next = previous;
			current = previous;
		}
		fpInit();

		while (next == current) {
			AESysFrameStart();
			AEInputUpdate();
			fpUpdate();
			fpDraw();
			gameTime = static_cast<f32>(AEFrameRateControllerGetFrameTime());
			AESysFrameEnd();
		}

		fpFree();

		if (next != GS_RESTART) {
			fpUnload();
		}

		previous = current;
		current = next;
	}
	AEGfxDestroyFont(fontId);
	AESysExit();
}