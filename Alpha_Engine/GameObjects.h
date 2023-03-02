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
		/*  
			[0][0] scale_x,		[0][1] 0(shearx),	[0][2] world x,
			[1][0] 0(sheary),	[1][1] scale_y,		[1][2] world y,
			[2][0] e,			[2][1] 0,			[2][2] world z
		*/
		AEMtx33						transform;
		//f32							elevation;
	};

	/*CHARACTER STRUCTURE*/
	struct Character {
		ObjectInst					pObjInst;
		AEVec2						dir;
		AEVec2						input;
		bool						isMoving;
		bool						isJumping;
		f32							rotation;
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
	AEVec2* GetVerticesXY(const ObjectInst obj, int& count);
	AEVec2* GetVerticesXZ(const ObjectInst obj, int& count);
	AEVec2* GetVerticesYZ(const ObjectInst obj, int& count);
	AEMtx33 ConvertIsometric(const ObjectInst& obj);
	void ConvertWorld(f32& x, f32& y);
	f32 distance(AEVec2 p1, AEVec2 p2);
	f32 distanceFromAEVec2ToLine(AEVec2 p, AEVec2* l);
	f32 GetLineFromDirection(ObjectInst obj, ObjectInst player, int direction);
}
