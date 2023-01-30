#pragma once
#include "pch.h"

namespace GameObjects
{
	/*EXTERN*/
	extern s8						fontId;
	extern const unsigned char		FLAG_INACTIVE;
	extern const unsigned char		FLAG_ACTIVE;		

	/*GAME OBJECT STRUCTURE*/
	struct Object {
		unsigned long				type;
		AEGfxTexture* pTex;
		AEGfxVertexList* pMesh;
	};

	/*TODO*/
	/*GAME OBJECT INSTANCE STRUCTURE*/
	struct ObjectInst {
		Object* pObj;
		unsigned char				flag;
		AEVec2						tex_offset;
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
	};

	/*FUNCTIONS*/
	void	RenderSettings(void);
	void	RenderObject(ObjectInst& obj);
	AEVec2* GetVertices(const ObjectInst obj);
}
