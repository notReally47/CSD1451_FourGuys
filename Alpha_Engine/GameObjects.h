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
		Vector pos;
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
		f32 velocity_x, velocity_y;
		int State;
	};

	void RenderObject(Object obj);
	void RenderWall(Object obj);
	void RenderFloor(Floor obj);
	Vector* GetVertices(const Object obj);
	Vector* Isometric(const Object obj);
}
