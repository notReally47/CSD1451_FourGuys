#pragma once
#include "pch.h"

namespace GameObjects
{
	/*EXTERN*/
	extern s8 fontId;
	extern bool glow;
	/*GAME OBJECT STRUCTURE*/
	struct Object {
		unsigned long		type;
		AEGfxTexture* pTex;
		AEGfxVertexList* pMesh;
		f32					width;
		f32					height;
		f32					rotation;
		AEVec2				scale;		//todo
		AEVec2				pos;
	};

	/*TODO*/
	/*GAME OBJECT INSTANCE STRUCTURE*/
	struct ObjectInst {
		Object* pObj;
		unsigned char		flag;
		AEMtx33				transform;
	};

	/*CHARACTER STRUCTURE*/
	struct Character {
		Object obj;
		AEVec2 direction;
		AEVec2 input;
		f32 speed;
		int State;
		bool isMoving;
		int spriteX, spriteY, spriteIteration, pTexOffsetX, pTexOffsetY;
	};

	/*FUNCTIONS*/
	void RenderSettings(void);
	void RenderColorSettings(void);
	void RenderObject(unsigned long type, Object obj);
	f32 Interpolate(f64& dt, f64 frametime);	//todo
	AEVec2* GetVertices(const Object obj);
}