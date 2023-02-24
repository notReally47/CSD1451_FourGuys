#include "SystemHandler.h"
#include "AEEngine.h"

namespace SystemHandler {

	void System_Initialize(HINSTANCE hInstance, s32 nCmdShow) {
		RECT window;
		const HWND hwindow = GetDesktopWindow();
		SetProcessDPIAware();
		GetWindowRect(hwindow, &window);
		AESysInit(hInstance, nCmdShow, static_cast<s32>(window.right)/2, static_cast<s32>(window.bottom)/2, 1, 60, true, NULL);
		//AESysToggleFullScreen(1);
		AESysSetWindowTitle("My New Demo!");
		AESysReset();
		AEGfxSetBackgroundColor(.0f, .0f, .0f);
	}
}