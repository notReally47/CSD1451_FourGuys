#pragma once
namespace GSM
{
	typedef void(*FP)(void);

	extern int current, previous, next;

	extern FP fpLoad, fpInit, fpUpdate, fpDraw, fpFree, fpUnload;

	void GSM_Init(int startingState);
	void GSM_Update();
}

