#pragma once
#include "pch.h"

namespace GameObjects
{
	struct Vector {
		f32 x, y;
	};

	struct Object {
		AEGfxTexture* pTex;
		AEGfxVertexList* pMesh;
		f32 width, height, rotation;
		AEVec2 pos;
	};

	struct Wall {
		AEGfxTexture* pTex;
		AEGfxVertexList* pMesh;
		f32 width, height;
		Vector pos;
	};

	struct Floor {
		AEGfxTexture* pTex[4];
		AEGfxVertexList* pMesh;
		f32 width, height;
		Vector pos;
	};

	struct Character {
		Object obj;
		AEVec2 direction;
		AEVec2 input;
		f32 speed;
		bool isMoving;
		int spriteX, spriteY, spriteIteration, pTexOffsetX, pTexOffsetY;
	};

	void RenderObject(Object obj);
	void RenderWall(Object obj);
	void RenderFloor(Floor obj);
	AEVec2* GetVertices(const Object obj);
	Vector* Isometric(const Object obj);
}
