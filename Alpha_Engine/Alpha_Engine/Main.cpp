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

#ifdef DEBUG

#endif // DEBUG

	using namespace GSM;
	using namespace Enum;

	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);
	AESysSetWindowTitle("My New Demo!");
	AESysReset();
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	GSM_Init(current);
	
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

			fpUpdate();
			fpDraw();

			AESysFrameEnd();
		}

		fpFree();
		if (next != GS_RESTART) {
			fpUnload();
		}
		previous = current;
		current = next;
	}

	AESysExit();
}