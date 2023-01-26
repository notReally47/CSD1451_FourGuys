#pragma once
#include "pch.h"

namespace GameObjects
{
	extern const f32 wall_dim;

	extern s8 fontId;
	struct Vector {
		f32 x, y;
	};

	struct Object {
		AEGfxTexture* pTex;
		AEGfxVertexList* pMesh;
		f32 width, height, rotation;
		AEVec2 pos;
	};

	struct Character {
		Object obj;
		AEVec2 direction;
		f32 speed;
		int State;
		void render();
		bool isMoving;
		int spriteX, spriteY, spriteIteration, pTexOffsetX, pTexOffsetY;
	};

	void RenderSettings(void);
	void RenderObject(Object obj);
	void RenderWall(Object obj);
	void RenderFloor(Object obj);
	void RenderDeco(Object obj);
	void RenderPortrait(Object obj);
	f32 Interpolate(f64 &dt, f64 frametime);
	AEVec2* GetVertices(const Object obj);
	AEVec2* Isometric(const Object obj);
}
