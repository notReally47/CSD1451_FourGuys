#include "GameObjects.h"
#include "pch.h"

namespace GameObjects {
	/*
	* Render objects that have textures.
	*/
	void RenderObject(Object& obj) {
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		/*Set texture*/
		AEGfxTextureSet(obj.pTex, 0, 0);

		/*SCALING*/
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, obj.width, obj.height);

		/*CLOCKWISE ROTATION*/
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, -obj.rotation);

		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
	}

	Vector* GetVertices(const Object obj) {
		Vector* vertices = { new Vector[4] };

		vertices[0].x = obj.pos.x - obj.width / 2;
		vertices[0].y = obj.pos.y + obj.height / 2;

		vertices[1].x = obj.pos.x + obj.width / 2;
		vertices[1].y = obj.pos.y + obj.height / 2;

		vertices[2].x = obj.pos.x + obj.width / 2;
		vertices[2].y = obj.pos.y - obj.height / 2;

		vertices[3].x = obj.pos.x - obj.width / 2;
		vertices[3].y = obj.pos.y - obj.height / 2;

		return vertices;
	}
}