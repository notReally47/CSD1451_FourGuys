#pragma once
#include "PCH.h"

namespace OM
{
	/*GAME OBJECT STRUCTURE*/
	struct Object
	{
		/*CONSTRUCTORS*/
		Object();
		~Object();

		/*PUBLIC DATA*/
		AEGfxTexture*		pTex;
		AEGfxVertexList*	pMesh;
		unsigned long		type;
		f32					width;
		f32					length;
		f32					height;
	};

	/*GAME OBJECT INSTANCE STRUCTURE*/
	struct ObjectInst
	{
		/*PUBLIC DATA*/
		Object*				pObj;
		unsigned long		flag;
		AEVec2				tex_offset;
		AEMtx33				transform;

		/*MEMBER FUNCTIONS*/
		f32&				GetScaleX(); // check if this is used anywhere
		f32&				GetPosX();
		f32					GetPosX() const;
		f32&				GetScaleY();
		f32&				GetPosY();
		f32					GetPosY() const;
		f32&				GetElapsed();
		f32&				GetPlayerSpeed();
		f32&				GetPosZ();
		f32					GetPosZ() const;
		AEVec2				GetPosXY();
		void				RenderObject();
	};

	/*CHARACTER STRUCTURE*/
	struct Character
	{
		/*PUBLIC DATA*/
		ObjectInst*			pObjInst;
		AEVec2				dir;
		AEVec2				input;
		f32					zVel;
		int					spriteIteration;

		/*MEMBER FUNCTIONS*/
		int					CheckDirection();
		AEVec2&				GetOffset();
		void				SetOffsetY();
		void				SetOffsetX();
		void				AnimateCharacter();
		void				MoveCharacter();
	};

	/*FUNCTIONS*/
	void					RenderSettings();

	/*GET VERTICES*/
	AEVec2*					GetVerticesXY(const ObjectInst& obj, int& count);
	AEVec2*					GetVerticesYZ(const ObjectInst& obj, int& count);
	AEVec2*					GetVerticesXZ(const ObjectInst& obj, int& count);
	AEMtx33					ConvertIsometric(const ObjectInst& obj);
}
