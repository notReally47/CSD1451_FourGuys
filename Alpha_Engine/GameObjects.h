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

	struct Character {
		Object obj;
		f32 velocity_x, velocity_y;
		int State;
	};

	void RenderObject(Object& obj);
	Vector* GetVertices(const Object obj);
}
