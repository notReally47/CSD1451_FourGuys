#include "AEEngine.h"
#include "GSM.h"
#include "Enum.h"
#include "InputHandler.h"
#include "SystemHandler.h"

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
	
	/*INITIALIZATIONS*/
	SystemHandler::System_Initialize(hInstance, nCmdShow);
	AE_ASSERT_MESG(fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12), "Failed to load font");
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
			gameTime += AEFrameRateControllerGetFrameTime();
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