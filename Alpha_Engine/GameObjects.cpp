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

	/*
	 * Render objects that have textures.
	 */
	void RenderObject(ObjectInst &obj) {
		delta_time += AEFrameRateControllerGetFrameTime();
		//std::cout << delta_time << std::endl;
		if (obj.pObj->type == Enum::TYPE::PORTRAIT) {
			//obj.flag = (delta_time > 2.0f) ? (delta_time = .0f, FLAG_INACTIVE) : (delta_time < 1.5f) ? FLAG_ACTIVE : obj.flag;
			/*Set texture*/
			//(obj.flag) ? AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x + 0.25f, obj.tex_offset.y):
				AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y);
		}	
		else if (obj.pObj->type == Enum::TYPE::PLATFORM) {
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
			AEVec2{ obj.transform.m[0][2] - obj.transform.m[0][0], obj.transform.m[1][2] + obj.transform.m[1][1] },
			AEVec2{ obj.transform.m[0][2] + obj.transform.m[0][0], obj.transform.m[1][2] + obj.transform.m[1][1] },
			AEVec2{ obj.transform.m[0][2] + obj.transform.m[0][0], obj.transform.m[1][2] - obj.transform.m[1][1] },
			AEVec2{ obj.transform.m[0][2] - obj.transform.m[0][0], obj.transform.m[1][2] - obj.transform.m[1][1] }
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