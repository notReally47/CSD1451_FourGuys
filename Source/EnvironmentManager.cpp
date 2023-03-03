/*!***********************************************************************
  \file   EnvironmentManager.cpp
  \authors

  \brief
  This file contains the implementation of the environment manager

  \copyright
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/

#include "EnvironmentManager.h"
#include "AEEngine.h"

namespace EM
{
	/*!***********************************************************************
	  \brief Creates the window instance

	  \param hInstance
	  \param nCmdShow
	*************************************************************************/
	void WindowCreate(HINSTANCE hInstance, s32 nCmdShow)
	{
		RECT window;
		const HWND hwindow = GetDesktopWindow();
		SetProcessDPIAware();
		GetWindowRect(hwindow, &window);
		AESysInit(hInstance, nCmdShow, static_cast<s32>(window.right) / 2, static_cast<s32>(window.bottom) / 2, 1, 60, true, NULL);
		//AESysToggleFullScreen(1);
		AESysSetWindowTitle("HopWards");
		AESysReset();
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	}
}