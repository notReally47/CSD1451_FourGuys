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
		TYPE				type;
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
		unsigned short		layer;
		unsigned short		flag;
		AEVec2				texture;
		AEMtx33				transf;
		void*				pair;


		/*MEMBER FUNCTIONS FOR TRANSFORMATIONS*/
		f32					GetCounter() const;
		void				SetCounter(f32);
		void				ResetCounter();

		f32&				GetPlayerSpeed();
		f32&				GetPosZ();
		f32					GetPosZ() const;
		AEVec2				GetPos() const;
		void				SetPos(AEVec2);
		AEVec2				GetScale(f32);
		void				SetScale(f32);

		/*GRAPHICS MANAGER*/
		void				RenderObject();
		void 				RenderShadow();
		void				RenderGlow();
		void				AnimateStairs();

		void				PairObject();
	};

	struct ObjectLayer
	{
		/*PUBLIC DATA*/
		short					data[36];
		unsigned short			layer;
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

	AEMtx33					ConvertIsometric(const ObjectInst& obj);

	int						PointLineClassification(AEVec2 point, AEVec2 pt1, AEVec2 pt2);
	f32 GetScreenXPercentage(f32 posX);
	f32 GetScreenYPercentage(f32 posY);
}

