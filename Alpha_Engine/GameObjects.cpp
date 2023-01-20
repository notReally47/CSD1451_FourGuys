#include "GameObjects.h"
#include "pch.h"

namespace GameObjects {
	/*
	* Render objects that have textures.
	*/
	void RenderObject(Object obj) {
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
		f32 x0, y0, x1, y1, x2, y2, x3, y3;

		/*Get original vertex*/
		x0 = obj.pos.x - obj.width - 10;
		y0 = obj.pos.y + obj.height - 10;

		x1 = obj.pos.x + obj.width - 10;
		y1 = obj.pos.y + obj.height - 10;

		x2 = obj.pos.x + obj.width - 10;
		y2 = obj.pos.y - obj.height - 10;

		x3 = obj.pos.x - obj.width - 10;
		y3 = obj.pos.y - obj.height - 10;

		/*
		* Get vertex after rotation.
		* Vertex rotates around the center of the mesh
		*/
		vertices[0].x = (x0 - obj.pos.x) * cos(-obj.rotation) - (y0 - obj.pos.y) * sin(-obj.rotation) + obj.pos.x;
		vertices[0].y = (x0 - obj.pos.x) * sin(-obj.rotation) + (y0 - obj.pos.y) * cos(-obj.rotation) + obj.pos.y;

		vertices[1].x = (x1 - obj.pos.x) * cos(-obj.rotation) - (y1 - obj.pos.y) * sin(-obj.rotation) + obj.pos.x;
		vertices[1].y = (x1 - obj.pos.x) * sin(-obj.rotation) + (y1 - obj.pos.y) * cos(-obj.rotation) + obj.pos.y;

		vertices[2].x = (x2 - obj.pos.x) * cos(-obj.rotation) - (y2 - obj.pos.y) * sin(-obj.rotation) + obj.pos.x;
		vertices[2].y = (x2 - obj.pos.x) * sin(-obj.rotation) + (y2 - obj.pos.y) * cos(-obj.rotation) + obj.pos.y;

		vertices[3].x = (x3 - obj.pos.x) * cos(-obj.rotation) - (y3 - obj.pos.y) * sin(-obj.rotation) + obj.pos.x;
		vertices[3].y = (x3 - obj.pos.x) * sin(-obj.rotation) + (y3 - obj.pos.y) * cos(-obj.rotation) + obj.pos.y;

		return vertices;
	}
}