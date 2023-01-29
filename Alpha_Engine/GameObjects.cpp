#include "pch.h"
#include <string>
//#include <iostream>

namespace GameObjects
{
	/*DEFINES*/
	s8 fontId;
	const unsigned char		FLAG_INACTIVE	= 0x0;
	const unsigned char		FLAG_ACTIVE		= 0x1;		//todo
	static f64				delta_time		= .0f;
	
	/*Set rendering modes, colour tints, blending and transparency*/
	void RenderSettings(void) {
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
	}
	void RenderColorSettings(void)
	{
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	}
	/*
	 * Render objects that have textures.
	 */
	void RenderObject(unsigned long type, Object obj)
	{
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
			for (int i = 0; i < 9; i++)
			{
				AEVec2 init_trans;
				switch (i)
				{
					/*CORNER WALL*/
				case 0:
					/*Set texture*/
					AEGfxTextureSet(obj.pTex, 1.0f / 7.0f * 3.0f, 0);
					init_trans = { 64, -432 };
					break;
					/*PLAIN RIGHT WALL*/
				case 1:
				case 3:
				case 4:
					/*Set texture*/
					AEGfxTextureSet(obj.pTex, 1.0f / 7.0f * 4.0f, 0);
					init_trans.x = (i == 4) ? -320 : 64;
					init_trans.y = (i == 1) ? -432 : (i == 3) ? -512
						: -384;
					break;
					/*COLUMN RIGHT WALL*/
				case 2:
					/*Set texture*/
					AEGfxTextureSet(obj.pTex, 1.0f / 7.0f * 5.0f, 0);
					init_trans = { 64, -512 };
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
					init_trans = { -64, -512 };
					break;
				}
				for (int j = 0; j < 6; j++)
				{
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
	texture
	/*Render objects that have textures.*/
	void RenderObject(ObjectInst &obj) {
		delta_time += AEFrameRateControllerGetFrameTime();
		//std::cout << delta_time << std::endl;
		if (obj.pObj->type == Enum::TYPE::PORTRAIT) {
			obj.flag = (delta_time > 2.0f) ? (delta_time = .0f, FLAG_INACTIVE) : (delta_time < 1.5f) ? FLAG_ACTIVE : obj.flag;
			/*Set texture*/
			(obj.flag) ? AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x + 0.25f, obj.tex_offset.y):
				AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y);
		}	
		else if (obj.pObj->type == Enum::TYPE::PLATFORM) {
			if (obj.flag == 0x1) {
				obj.transform.m[1][2] -= 10.f*AEFrameRateControllerGetFrameTime();
				AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y-=0.1f*AEFrameRateControllerGetFrameTime());
			}
			/*Set texture*/
			AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y);
		}
		else {
			/*Set texture*/
			AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y);
		}
		
		/*TRANSFORMATION (TRS)*/
		AEGfxSetTransform(obj.transform.m);
		/*DRAW MESH*/
		AEGfxMeshDraw(obj.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	AEVec2* GetVertices(const ObjectInst obj) {
		AEVec2* vertices = { new AEVec2[4] };
		AEVec2 original[4] = {
			/* object position x +- object width - object position y +- object height */
			AEVec2{ obj.transform.m[0][2] - obj.transform.m[0][0] - 10, obj.transform.m[1][2] + obj.transform.m[1][1] - 10 },
			AEVec2{ obj.transform.m[0][2] + obj.transform.m[0][0] - 10, obj.transform.m[1][2] + obj.transform.m[1][1] - 10 },
			AEVec2{ obj.transform.m[0][2] + obj.transform.m[0][0] - 10, obj.transform.m[1][2] - obj.transform.m[1][1] - 10 },
			AEVec2{ obj.transform.m[0][2] - obj.transform.m[0][0] - 10, obj.transform.m[1][2] - obj.transform.m[1][1] - 10 }
		};

		/* Get vertex after rotation. Vertex rotates around the center of the mesh */
		for (int i = 0; i < 4; i++) {
			f32 posX = original[i].x - obj.transform.m[0][2];
			f32 posY = original[i].y - obj.transform.m[1][2];
			vertices[i].x = posX * static_cast<f32>(cos(-.0f)) - posY * static_cast<f32>(sin(-.0f)) + obj.transform.m[0][2];
			vertices[i].y = posX * static_cast<f32>(sin(-.0f)) + posY * static_cast<f32>(cos(-.0f)) + obj.transform.m[1][2];
		}

		return vertices;
	}
}