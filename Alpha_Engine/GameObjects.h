#pragma once
#include "pch.h"

namespace GameObjects
{
	/*EXTERN*/
	extern s8						fontId;
	extern const unsigned char		FLAG_INACTIVE;
	extern const unsigned char		FLAG_ACTIVE;
	extern const unsigned char		FLAG_ALT1_S;
	extern const unsigned char		FLAG_ALT1_E;
	extern const unsigned char		FLAG_ALT2_S;
	extern const unsigned char		FLAG_ALT2_E;

	/*GAME OBJECT STRUCTURE*/
	struct Object {
		unsigned long				type;
		AEGfxTexture*				pTex;
		AEGfxVertexList*			pMesh;
	};

	/*TODO*/
	/*GAME OBJECT INSTANCE STRUCTURE*/
	struct ObjectInst {
		Object*						pObj;
		unsigned char				flag;
		AEVec2						tex_offset;
		/*  [0][0] scale_x,   [0][1] 0(shearx),       [0][2] pos x,
			[1][0] 0(sheary),		[1][1] scale_y,	[1][2] pos y,
			[2][0] width, [2][1] length,		[2][2] height*/
		AEMtx33						transform;
	};

	/*CHARACTER STRUCTURE*/
	struct Character {
		ObjectInst					pObjInst;
		AEVec2						dir;
		AEVec2						input;
		f32							rotation;
		f32							speed;
		int							spriteIteration;
		// width 128, height 152
	};

	/*FUNCTIONS*/
	void	RenderSettings(void);
	void	RenderObject(ObjectInst& obj);
	AEVec2* GetVertices(const ObjectInst obj);
}
