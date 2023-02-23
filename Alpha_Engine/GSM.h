#pragma once
#include "pch.h"

namespace GSM {
	typedef void(*FP)(void);

	extern int current, previous, next;
	extern f32 gameTime;
	extern FP fpLoad, fpInit, fpUpdate, fpDraw, fpFree, fpUnload;

	void GSM_Init(int startingState);
	void GSM_Update();
}

