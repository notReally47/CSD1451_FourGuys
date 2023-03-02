#include "EnvironmentManager.h"
#include "AEEngine.h"

namespace EM
{
	void WindowCreate(HINSTANCE hInstance, s32 nCmdShow)
	{
		RECT window;
		const HWND hwindow = GetDesktopWindow();
		SetProcessDPIAware();
		GetWindowRect(hwindow, &window);
		AESysInit(hInstance, nCmdShow, static_cast<s32>(window.right)/2, static_cast<s32>(window.bottom)/2, 1, 60, true, NULL);
		//AESysToggleFullScreen(1);
		AESysSetWindowTitle("HopWards");
		AESysReset();
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	}
}