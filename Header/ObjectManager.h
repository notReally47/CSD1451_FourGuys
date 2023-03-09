#pragma once
#include "PCH.h"
#include <utility>
#include <vector>
#include <string>

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
		unsigned long		flag;
	};

	/*GAME OBJECT INSTANCE STRUCTURE*/
	struct ObjectInst
	{
		/*CONSTRUCTORS*/
		ObjectInst();
		ObjectInst(const ObjectInst&);
		~ObjectInst();


		/*PUBLIC DATA*/
		Object*				pO;
		unsigned long		flag;
		AEVec2				texture;
		AEMtx33				transf;
		unsigned long*		pair;


		/*MEMBER FUNCTIONS FOR TRANSFORMATIONS*/
		f32&				GetElapsed();
		f32&				GetPlayerSpeed();
		f32&				GetPosZ();
		f32					GetPosZ() const;
		AEVec2				GetPos() const;
		void				SetPos(const AEVec2&);
		AEVec2				GetScale(const f32&);
		void				SetScale(const f32&);

		/*GRAPHICS MANAGER*/
		void				RenderObject();
		void 				RenderShadow();
		void				RenderGlow();
		void				AnimateStairs();

		/*SIMULATION MANAGER*/
		void				SetCollider();
	};

	struct ObjectLayer
	{
		/*CONSTRUCTORS*/
		//ObjectLayer();
		//~ObjectLayer();

		/*PUBLIC DATA*/
		short					data[25];
		short					layer;
		f32						transp;
		AEVec2					offset;
	};

	/*CHARACTER STRUCTURE*/
	struct Character
	{
		/*PUBLIC DATA*/
		ObjectInst*			pOI;
		AEVec2				dir;
		AEVec2				input;
		f32					zVel;
		int					iter;

		/*MEMBER FUNCTIONS*/
		int					CheckDirection();
		AEVec2&				GetOffset();
		void				SetOffsetY();
		void				SetOffsetX();
		void				AnimateCharacter();
		void				MoveCharacter();

		bool				InCell(ObjectInst cell);
		f32					PointLineDist(ObjectInst cell);
		f32					SlopeHeight(ObjectInst cell);
	};

	struct Platform
	{
		ObjectInst* pOI;
	};

	struct Portraits
	{
		ObjectInst* pOI;
	};


	/*FUNCTIONS*/
	void					RenderSettings();

	/*GET VERTICES*/
	AEVec2*					GetVerticesXY(const ObjectInst& obj, int& count);
	AEVec2*					GetVerticesYZ(const ObjectInst& obj, int& count);
	AEVec2*					GetVerticesXZ(const ObjectInst& obj, int& count);
	AEMtx33					ConvertIsometric(const ObjectInst& obj);

	int						PointLineClassification(AEVec2 point, AEVec2 pt1, AEVec2 pt2);
	f32 GetScreenXPercentage(f32 posX);
	f32 GetScreenYPercentage(f32 posY);
}

