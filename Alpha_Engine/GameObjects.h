#pragma once
#include "pch.h"

namespace GameObjects
{
	/*EXTERN*/
	extern s8						fontId;

	/*GAME OBJECT STRUCTURE*/
	struct Object {
		AEGfxTexture*				pTex;
		AEGfxVertexList*			pMesh;
		unsigned long				type;
		f32							width;
		f32							length;
		f32							height;
	};

	/*TODO*/
	/*GAME OBJECT INSTANCE STRUCTURE*/
	struct ObjectInst {
		Object*						pObj;
		unsigned long				flag;
		AEVec2						tex_offset;
		AEMtx33						transform;

		f32& GetScaleX(); // check if this is used anywhere
		f32& GetPosX();
		f32 GetPosX() const;
		f32& GetScaleY();
		f32& GetPosY();
		f32 GetPosY() const;
		f32& GetElapsed();
		f32& GetPlayerSpeed();
		f32& GetPosZ();
		f32 GetPosZ() const;
		AEVec2 GetPosXY();
	};

	/*CHARACTER STRUCTURE*/
	struct Character {
		ObjectInst*					pObjInst;
		AEVec2						dir;
		AEVec2						input;
		f32							zVel;
		int							spriteIteration;
	};

	/*FUNCTIONS*/
	void	RenderSettings(void);
	void	RenderObject(ObjectInst& obj);

	/*GET VERTICES*/
	//AEVec2* GetVertices(const ObjectInst obj);
	AEVec2* GetVerticesXY(const ObjectInst& obj, int& count);
	AEVec2* GetVerticesYZ(const ObjectInst& obj, int& count);
	AEVec2* GetVerticesXZ(const ObjectInst& obj, int& count);
	AEMtx33 ConvertIsometric(const ObjectInst& obj);
}
