#include "pch.h"
#include <string>

namespace GameObjects {
	/*DEFINES*/
	const unsigned char		FLAG_ACTIVE = 0x1;		//todo
	s8 fontId;
	f64 dt{ 0.0 }, ani{1.f/6.f};					//todo
	bool interpolate{ true };						//todo

	/*TODO*/
	f32 Interpolate(f64 &dt, f64 frametime) {
		interpolate = (dt >= 1.f) ? false : (dt <= .0f) ? true : interpolate;
		return dt += (interpolate) ? frametime : -frametime;
	}

	/*
	* Set rendering modes, colour tints, blending and transparency
	*/
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
	void RenderObject(unsigned long type, Object obj) {
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

		if (type == Enum::TYPE::WALL)
			for (int i = 0; i < 9; i++) {
				AEVec2 init_trans;
				switch (i) {
				/*CORNER WALL*/
				case 0:
					/*Set texture*/
					AEGfxTextureSet(obj.pTex, 1.0f/7.0f * 3.0f, 0);
					init_trans = { 64,-432 };
					break;
				/*PLAIN RIGHT WALL*/
				case 1:
				case 3:
				case 4:
					/*Set texture*/
					AEGfxTextureSet(obj.pTex, 1.0f / 7.0f * 4.0f, 0);
					init_trans.x = (i == 4) ? -320 : 64;
					init_trans.y = (i == 1) ? -432 : (i == 3) ? -512 : -384;
					break;
				/*COLUMN RIGHT WALL*/
				case 2:
					/*Set texture*/
					AEGfxTextureSet(obj.pTex, 1.0f / 7.0f * 5.0f, 0);
					init_trans = { 64,-512 };
					break;
				/*PLAIN LEFT WALL*/
				case 5:
				case 7:
				case 8:
					/*Set texture*/
					AEGfxTextureSet(obj.pTex, 1.0f / 7.0f * 2.0f, 0);
					init_trans.x = -64;
					init_trans.y = (i == 5) ? -432 : -512;
					break;
				/*COLUMN LEFT WALL*/
				case 6:
					/*Set texture*/
					AEGfxTextureSet(obj.pTex, 1.0f / 7.0f, 0);
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
		else if (type == Enum::TYPE::FLOOR) {
			/*Set texture*/
			AEGfxTextureSet(obj.pTex, 0, 0);
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
		else if (type == Enum::TYPE::DECO) {
			/*TODO*/
			/*Set texture*/
			//AEGfxTextureSet(obj.pTex, ani, 0);
			/*TRANSLATION/POSITION*/
			/*
			AEMtx33 translate = { 0 };
			AEVec2 animate = { obj.pos.x , obj.pos.y + 5.f };
			AEVec2Lerp(&obj.pos, &obj.pos, &animate, Interpolate(dt, AEFrameRateControllerGetFrameTime()));
			AEMtx33Trans(&translate, obj.pos.x, obj.pos.y);
			for (int i = 0; i < 5; i++) {
				/*DRAW MESH*/
				//AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
				/*TRANSFORMATION (TRS)*//*
				AEMtx33Trans(&translate, -32, -16);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
			}
			for (int i = 0; i < 5; i++) {
				/*DRAW MESH*/
				//AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
				/*TRANSFORMATION (TRS)*//*
				AEMtx33Trans(&translate, 32, -16);
				AEMtx33Concat(&transform, &translate, &transform);
				AEGfxSetTransform(transform.m);
			}
			/*TRANSFORMATION (TRS)*/
				/*
			AEMtx33Trans(&translate, 0, 128);
			AEMtx33Concat(&transform, &translate, &transform);
			AEGfxSetTransform(transform.m);*/
		}
		else if (type == Enum::TYPE::PLATFORM) {
			/*TODO*/
		}
		else if (type == Enum::TYPE::PORTRAIT) {
			dt += (interpolate) ? AEFrameRateControllerGetFrameTime() : -AEFrameRateControllerGetFrameTime();
			interpolate = (dt >= 1.f) ? false : (dt <= .0f) ? true : interpolate;
			/*Set texture*/
			(interpolate) ? AEGfxTextureSet(obj.pTex, 0, 0) :
				AEGfxTextureSet(obj.pTex, 0.25, 0);
			/*DRAW MESH*/
			AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
		}
		else if (type == Enum::TYPE::PLAYER) {
			/*Set texture*/
			AEGfxTextureSet(obj.pTex, 0, 0);
			/*DRAW MESH*/
			AEGfxMeshDraw(obj.pMesh, AE_GFX_MDM_TRIANGLES);
		}
		
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
}