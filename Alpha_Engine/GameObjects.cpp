#include "GameObjects.h"
#include "pch.h"
#include <string>

namespace GameObjects {
	// does nothing right now
	const f32
		i_x = 0.5,
		i_y = 0.25,
		j_x = -0.5,
		j_y = 0.25;

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

		/*CLOCKWISE ROTATION*/
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, AEDegToRad(obj.rotation));

		/*SCALING*/
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, obj.width, obj.height);

		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		//AEMtx33MultVec(&transform, &transform, Isometric(obj));
		AEGfxSetTransform(transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
	}

	void RenderWall(Object obj) {
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

		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &translate, &scale);
		AEGfxSetTransform(transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
		
		if (strcmp(obj.pTex->mpName, "../Assets/Textures/cornerwall.png") == 0)
			for (int i = 0; i < 6; i++) {
				/*TRANSFORMATION (TRS)*/
				AEMtx33Trans(&translate, 0, 80);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);

				/*DRAW MESH*/
				AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
			}
		else
			for (int i = 0; i < 6; i++) {
				/*DRAW MESH*/
				AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
				f32 x = (strcmp(obj.pTex->mpName, "../Assets/Textures/rightwall0.png") == 0) ? 64 : -64;
				for (int j = 0; j < 3; j++) {
					/*TRANSFORMATION (TRS)*/
					AEMtx33Trans(&translate, x, -32);
					AEMtx33Concat(&transform, &translate, &transform);
					AEGfxSetTransform(transform.m);

					/*DRAW MESH*/
					AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
				}
				/*TRANSFORMATION (TRS)*/	// translate back to original x position
				AEMtx33Trans(&translate, -x*3, 176);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
			}
		
	}

	void RenderFloor(Floor obj) {
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		/*SCALING*/
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, obj.width, obj.height);

		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &translate, &scale);
		AEGfxSetTransform(transform.m);

		for (int i = 0; i < 9; i++) {
			/*Set texture*/
			AEGfxTextureSet(obj.pTex[i % 4], 0, 0);
			
			/*DRAW MESH*/
			AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
			for (int j = 0; j < 8; j++) {
				/*Set texture*/
				AEGfxTextureSet(obj.pTex[j % 2], 0, 0);
				/*TRANSFORMATION (TRS)*/
				AEMtx33Trans(&translate, -32, -16); //-32, -16
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);

				/*DRAW MESH*/
				AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
			}

			/*TRANSFORMATION (TRS)*/
			AEMtx33Trans(&translate, 288, 112);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
			
		}
	}

	Vector* GetVertices(const Object obj) {
		Vector* vertices = { new Vector[4] };
		Vector original[4] = {
			Vector{ obj.pos.x - obj.width - 10, obj.pos.y + obj.height - 10 },
			Vector{ obj.pos.x + obj.width - 10, obj.pos.y + obj.height - 10 },
			Vector{ obj.pos.x + obj.width - 10, obj.pos.y - obj.height - 10 },
			Vector{ obj.pos.x - obj.width - 10, obj.pos.y - obj.height - 10 }
		};

		/* Get vertex after rotation. Vertex rotates around the center of the mesh */
		for (int i = 0; i < 4; i++) {
			vertices[i].x = (original[i].x - obj.pos.x) * cos(-obj.rotation) - (original[i].y - obj.pos.y) * sin(-obj.rotation) + obj.pos.x;
			vertices[i].y = (original[i].x - obj.pos.x) * sin(-obj.rotation) + (original[i].y - obj.pos.y) * cos(-obj.rotation) + obj.pos.y;
		}

		return vertices;
	}

	// does nothing right now
	Vector* Isometric(const Object obj) {
		Vector* coordinates = { new Vector };
		coordinates->x = (obj.pos.x * i_x * obj.width) + (obj.pos.y * j_x * obj.width);
		coordinates->y = (obj.pos.x * i_y * obj.height) + (obj.pos.y * j_y * obj.height);
		return coordinates;
	}
}