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

		// Scale of Object Instance in width
		f32& GetScaleX() { return this->transform.m[0][0]; } // check if this is used anywhere

		// Position X in world screen coordinates
		f32& GetPosX() { return this->transform.m[0][2]; }

		f32 GetPosX() const { return this->transform.m[0][2]; }

		// Scale of Object Instance in height
		f32& GetScaleY() { return this->transform.m[1][1]; }

		// Position Y in world screen coordinates
		f32& GetPosY() { return this->transform.m[1][2]; }

		f32 GetPosY() const { return this->transform.m[1][2]; }

		// Elapsed time of animation
		f32& GetElapsed() { return this->transform.m[2][1]; }

		// Elevation of the Object Instance
		f32& GetPosZ() { return this->transform.m[2][2]; }

		f32 GetPosZ() const { return this->transform.m[2][2]; }

		AEVec2 GetPosXY() { return {this->GetPosX(), this->GetPosY()}; }
	};

	/*CHARACTER STRUCTURE*/
	struct Character {
		ObjectInst*					pObjInst;
		AEVec2						dir;
		AEVec2						input;
		bool						isMoving;
		bool						isJumping;
		f32							zVel;
		f32							speed;
		int							spriteIteration;
		// width 128, height 152
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
