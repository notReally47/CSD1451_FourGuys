#pragma once
#include "pch.h"

namespace GameObjects
{
	/*EXTERN*/
	extern s8						fontId;
	extern const unsigned char		FLAG_INACTIVE;
	extern const unsigned char		FLAG_ACTIVE;		//todo
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
		AEMtx33						transform;	// {w, 0, x, 0, h, y, 0, 0, 1}
	};

	/*CHARACTER STRUCTURE*/
	struct Character {
		ObjectInst					pObjInst;
		AEVec2						dir;
		AEVec2						input;
		//AEVec2					rotation;
		f32							speed;
		int							spriteIteration;
	};

	/*FUNCTIONS*/
	void	RenderSettings	(void);
	void	RenderObject	(ObjectInst &obj);
	void 	RenderColor(Object &object, f32 width, f32 height, f32 x, f32 y);
	AEVec2* GetVertices		(const ObjectInst obj);
}
