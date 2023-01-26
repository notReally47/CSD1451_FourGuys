#include "pch.h"
#include <string>

namespace GameObjects {
	s8 fontId;
	// does nothing right now
	const f32
		i_x = 0.5,
		i_y = 0.25,
		j_x = -0.5,
		j_y = 0.25;
	const f32
		wall_dim = 1.f / 7.f;
	f64 dt{ 0.0 }, ani{1.f/6.f};
	bool interpolate{ true };
	f32 Interpolate(f64 &dt, f64 frametime) {
		interpolate = (dt >= 1.f) ? false : (dt <= .0f) ? true : interpolate;
		return dt += (interpolate) ? frametime : -frametime;
	}
	void RenderSettings(void) {
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
	}
	/*
	* Render objects that have textures.
	*/
	void RenderObject(Object obj) {
		/*Set texture*/
		AEGfxTextureSet(obj.pTex, 0, 0);

		/*SCALING*/
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, obj.width, obj.height);
		
		///*TRANSLATION/POSITION*/
		//AEMtx33 translate = { 0 };
		//AEVec2 animate = { obj.pos.x , obj.pos.y + 10.f };
		//if (AEInputCheckCurr(AEVK_SPACE))
			//AEVec2Lerp(&obj.pos, &obj.pos, &animate, Interpolate(dt, AEFrameRateControllerGetFrameTime()));
		//AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);
		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &translate, &scale);
		//AEMtx33MultVec(&transform, &transform, Isometric(obj));
		AEGfxSetTransform(transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
	}

	void RenderWall(Object obj) {
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
			AEVec2 init_trans;
			switch (i) {
			case 0: // corner wall
				/*Set texture*/
				AEGfxTextureSet(obj.pTex, wall_dim * 3.0f, 0);
				init_trans = { 64,-432 };
				break;
			case 1: // plain right wall
			case 3:
			case 4:
				/*Set texture*/
				AEGfxTextureSet(obj.pTex, wall_dim * 4.0f, 0);
				init_trans.x = (i == 4) ? -320 : 64;
				init_trans.y = (i == 1) ? -432 : (i == 3) ? -512 : -384;
				break;
			case 2: // column right wall
				/*Set texture*/
				AEGfxTextureSet(obj.pTex, wall_dim * 5.0f, 0);
				init_trans = { 64,-512 };
				break;
			case 5: // plain left wall
			case 7:
			case 8:
				/*Set texture*/
				AEGfxTextureSet(obj.pTex, wall_dim * 2.0f, 0);
				init_trans.x = -64;
				init_trans.y = (i == 5) ? -432 : -512;
				break;
			case 6: // column left wall
				/*Set texture*/
				AEGfxTextureSet(obj.pTex, wall_dim, 0);
				init_trans = { -64,-512 };
				break;
			}
			for (int j = 0; j < 6; j++) {
				if (j == 5 && (i == 0 || i == 1 || i == 5))
					break;
				/*DRAW MESH*/
				AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);

				/*TRANSFORMATION (TRS)*/
				AEMtx33Trans(&translate, 0, 80);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
			}
			/*TRANSFORMATION (TRS)*/
			AEMtx33Trans(&translate, init_trans.x, init_trans.y);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
		}
		
	}

	void RenderFloor(Object obj) {
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

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				/*DRAW MESH*/
				AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);

				/*TRANSFORMATION (TRS)*/
				AEMtx33Trans(&translate, -32, -16);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
			}
			/*TRANSFORMATION (TRS)*/
			AEMtx33Trans(&translate, 320, 128);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
		}
	}
	void RenderDeco(Object obj) {
		
		dt += (interpolate) ? AEFrameRateControllerGetFrameTime() : -AEFrameRateControllerGetFrameTime();
		interpolate = (dt >= 1.f) ? false : (dt <= .0f) ? true : interpolate;
		
		/*Set texture*/
		AEGfxTextureSet(obj.pTex, ani, 0);

		/*CLOCKWISE ROTATION*/
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, AEDegToRad(obj.rotation));

		/*SCALING*/
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, obj.width, obj.height);

		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEVec2 animate = { obj.pos.x , obj.pos.y + 5.f };
		AEVec2Lerp(&obj.pos, &obj.pos, &animate, Interpolate(dt,AEFrameRateControllerGetFrameTime()));
		AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &translate, &scale);
		AEGfxSetTransform(transform.m);

		for (int i = 0; i < 5; i++) {
			/*DRAW MESH*/
			AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
			/*TRANSFORMATION (TRS)*/
			AEMtx33Trans(&translate, -32, -16);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
		}
		for (int i = 0; i < 5; i++) {
			/*DRAW MESH*/
			AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
			/*TRANSFORMATION (TRS)*/
			AEMtx33Trans(&translate, 32, -16);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);
		}
		/*TRANSFORMATION (TRS)*/
		AEMtx33Trans(&translate, 0, 128);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);
	}
	void RenderPortrait(Object obj) {
		/*Set texture*/
		(interpolate) ? AEGfxTextureSet(obj.pTex, 0, 0):
			AEGfxTextureSet(obj.pTex, 0.25, 0);

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
	}

	AEVec2* GetVertices(const Object obj) {
		AEVec2* vertices = { new AEVec2[4] };
		AEVec2 original[4] = {
			AEVec2{ obj.pos.x - obj.width - 10, obj.pos.y + obj.height - 10 },
			AEVec2{ obj.pos.x + obj.width - 10, obj.pos.y + obj.height - 10 },
			AEVec2{ obj.pos.x + obj.width - 10, obj.pos.y - obj.height - 10 },
			AEVec2{ obj.pos.x - obj.width - 10, obj.pos.y - obj.height - 10 }
		};

		/* Get vertex after rotation. Vertex rotates around the center of the mesh */
		for (int i = 0; i < 4; i++) {
			f32 posX = original[i].x - obj.pos.x;
			f32 posY = original[i].y - obj.pos.y;
			vertices[i].x = posX * static_cast<f32>(cos(-obj.rotation)) - posY * static_cast<f32>(sin(-obj.rotation)) + obj.pos.x;
			vertices[i].y = posX * static_cast<f32>(sin(-obj.rotation)) + posY * static_cast<f32>(cos(-obj.rotation)) + obj.pos.y;
		}

		return vertices;
	}

	// does nothing right now
	AEVec2* Isometric(const Object obj) {
		AEVec2* coordinates = { new AEVec2 };
		coordinates->x = (obj.pos.x * i_x * obj.width) + (obj.pos.y * j_x * obj.width);
		coordinates->y = (obj.pos.x * i_y * obj.height) + (obj.pos.y * j_y * obj.height);
		return coordinates;
	}
}