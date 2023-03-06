#pragma once
#include "PCH.h"
#include <utility>

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
		unsigned long		direction; // slope direction; none if not a slope

		/*COLLIDER VERTICES*/
		// Not required to be added to YAML, calculated at run time
		AEVec2				topLeft;
		AEVec2				topRight;
		AEVec2				botLeft;
		AEVec2				botRight;

		/*MEMBER FUNCTIONS*/
		f32&				GetScaleX();
		f32&				GetPosX();
		f32					GetPosX() const;
		f32&				GetScaleY();
		f32&				GetPosY();
		f32					GetPosY() const;
		f32&				GetElapsed();
		f32&				GetPlayerSpeed();
		f32&				GetPosZ();
		f32					GetPosZ() const;
		AEVec2				GetScaleXY();
		AEVec2				GetPosXY();
		void				RenderObject();
		void 				RenderShadow();
		void				SetCollider();
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
		unsigned int		layer;

		/*MEMBER FUNCTIONS*/
		int					CheckDirection();
		AEVec2&				GetOffset();
		void				SetOffsetY();
		void				SetOffsetX();
		void				AnimateCharacter();
		void				MoveCharacter();

		bool				InCell(ObjectInst cell);
		f32					PointLineDist(ObjectInst cell);
		f32					HandleSlope(ObjectInst cell);
	};

	/*FUNCTIONS*/
	void					RenderSettings();

	/*GET VERTICES*/
	AEVec2*					GetVerticesXY(const ObjectInst& obj, int& count);
	AEVec2*					GetVerticesYZ(const ObjectInst& obj, int& count);
	AEVec2*					GetVerticesXZ(const ObjectInst& obj, int& count);
	AEMtx33					ConvertIsometric(const ObjectInst& obj);

	int						PointLineClassification(AEVec2 point, AEVec2 pt1, AEVec2 pt2);
}

