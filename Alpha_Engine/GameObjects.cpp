#include "pch.h"
#include "AnimationHandler.h"
//#include <string>
//#include <iostream>

namespace GameObjects
{
	/*DEFINES*/
	s8 fontId;
	const unsigned char		FLAG_INACTIVE	= 0x0;
	const unsigned char		FLAG_ACTIVE		= 0x1;
	const unsigned char		FLAG_ALT1_S		= 0x2;
	const unsigned char		FLAG_ALT1_E		= 0x3;
	const unsigned char		FLAG_ALT2_S		= 0x4;
	const unsigned char		FLAG_ALT2_E		= 0x5;

	/*Set rendering modes, colour tints, blending and transparency*/
	void RenderSettings(void) 
	{
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
	}

	/*
	 * Render objects that have textures.
	 */
	void RenderObject(ObjectInst &obj) 
	{
		f32 dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
		if (obj.pObj->type == Enum::TYPE::PORTRAIT || obj.pObj->type == Enum::TYPE::LANDSCAPE)
		{
			/*Set texture*/
			AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y);
			if (obj.flag == FLAG_ACTIVE) {
				/*TRANSFORMATION (TRS)*/
				AEMtx33 highlight = obj.transform;
				highlight.m[0][0] += 5.f;
				highlight.m[1][1] += 5.f;
				AEGfxSetTransform(highlight.m);
				AEGfxSetBlendColor(1.0f, 1.0f, 1.0f, 0.7f);
				/*DRAW MESH*/
				AEGfxMeshDraw(obj.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
				AEGfxSetBlendColor(1.0f, 1.0f, 1.0f, 0.0f);
			}
		}	
		else if (obj.pObj->type == Enum::TYPE::PLATFORM) 
		{
			if (obj.flag == FLAG_ALT1_S) {
				obj.transform.m[2][0] += dt;
				obj.transform.m[0][2] -= dt * 10.f;
				obj.transform.m[1][2] += dt * 5.f;
				obj.flag = (obj.transform.m[2][0] > 5.f) ? (obj.transform.m[2][0] = .0f, FLAG_ALT1_E) : obj.flag;
			}
			else if (obj.flag == FLAG_ALT1_E) {
				obj.transform.m[2][0] += dt;
				obj.transform.m[0][2] += dt * 10.f;
				obj.transform.m[1][2] -= dt * 5.f;
				obj.flag = (obj.transform.m[2][0] > 5.f) ? (obj.transform.m[2][0] = .0f, FLAG_ALT1_S) : obj.flag;
			}
			else if (obj.flag == FLAG_ALT2_S) {
				obj.transform.m[2][0] += dt;
				obj.transform.m[0][2] -= dt * 10.f;
				obj.transform.m[1][2] -= dt * 5.f;
				obj.flag = (obj.transform.m[2][0] > 5.f) ? (obj.transform.m[2][0] = .0f, FLAG_ALT2_E) : obj.flag;
			}
			else if (obj.flag == FLAG_ALT2_E) {
				obj.transform.m[2][0] += dt;
				obj.transform.m[0][2] += dt * 10.f;
				obj.transform.m[1][2] += dt * 5.f;
				obj.flag = (obj.transform.m[2][0] > 5.f) ? (obj.transform.m[2][0] = .0f, FLAG_ALT2_S) : obj.flag;
			}
			/*Set texture*/
			AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y);
		}
		else if (obj.pObj->type == Enum::TYPE::WALL)
		{
			/*Set texture*/
			AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y);
			//AEGfxSetTransparency(0.5f);
			
		}
		else 
		{
			/*Set texture*/
			AEGfxTextureSet(obj.pObj->pTex, obj.tex_offset.x, obj.tex_offset.y);
		}
		
		/*TRANSFORMATION (TRS)*/
		//TODO
		//AEMtx33 trans;
		//trans.m = obj.transform.m;
		//m[0][2] = //iso convert x;
		//m[1][2] = //iso convert y + z;

		AEGfxSetTransform(obj.transform.m);
		/*DRAW MESH*/
		AEGfxMeshDraw(obj.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
		//AEGfxSetTransparency(1.0f);
		
	}

	//AEVec2* GetVertices(const ObjectInst obj) {
	//	AEVec2* vertices = { new AEVec2[4] };
	//	AEVec2 original[4] = {
	//		/* object position x +- object width - object position y +- object height */
	//		AEVec2{ obj.transform.m[0][2] - obj.transform.m[0][0], obj.transform.m[1][2] + obj.transform.m[1][1] },
	//		AEVec2{ obj.transform.m[0][2] + obj.transform.m[0][0], obj.transform.m[1][2] + obj.transform.m[1][1] },
	//		AEVec2{ obj.transform.m[0][2] + obj.transform.m[0][0], obj.transform.m[1][2] - obj.transform.m[1][1] },
	//		AEVec2{ obj.transform.m[0][2] - obj.transform.m[0][0], obj.transform.m[1][2] - obj.transform.m[1][1] }
	//	};

	//	/* Get vertex after rotation. Vertex rotates around the center of the mesh */
	//	for (int i = 0; i < 4; i++) {
	//		f32 posX = original[i].x - obj.transform.m[0][2];
	//		f32 posY = original[i].y - obj.transform.m[1][2];
	//		vertices[i].x = posX * static_cast<f32>(cos(-.0f)) - posY * static_cast<f32>(sin(-.0f)) + obj.transform.m[0][2];
	//		vertices[i].y = posX * static_cast<f32>(sin(-.0f)) + posY * static_cast<f32>(cos(-.0f)) + obj.transform.m[1][2];
	//	}

	//	return vertices;
	//}

	AEVec2* GetVerticesXY(const ObjectInst obj, int& count) {
		count = 4;
		AEVec2* xyCoords = { new AEVec2[count] };
		xyCoords[0] = AEVec2{ obj.transform.m[0][2] - obj.pObj->width / 2, obj.transform.m[1][2] + obj.pObj->length / 2 }; //top right
		xyCoords[1] = AEVec2{ obj.transform.m[0][2] + obj.pObj->width / 2, obj.transform.m[1][2] + obj.pObj->length / 2 }; //top left
		xyCoords[2] = AEVec2{ obj.transform.m[0][2] - obj.pObj->width / 2, obj.transform.m[1][2] - obj.pObj->length / 2 }; //bot right
		xyCoords[3] = AEVec2{ obj.transform.m[0][2] + obj.pObj->width / 2, obj.transform.m[1][2] - obj.pObj->length / 2 }; //bot left

		//TODO: Any rotatation 
		return xyCoords;
	}

	AEVec2* GetVerticesYZ(const ObjectInst obj, int& count) {
		count = 4;
		AEVec2* yzCoords = { new AEVec2[count] };
		yzCoords[0] = AEVec2{ obj.transform.m[1][2] - obj.pObj->width / 2, obj.transform.m[2][2] + obj.pObj->height / 2 }; //top right
		yzCoords[1] = AEVec2{ obj.transform.m[1][2] + obj.pObj->width / 2, obj.transform.m[2][2] + obj.pObj->height / 2 }; //top left
		yzCoords[2] = AEVec2{ obj.transform.m[1][2] - obj.pObj->width / 2, obj.transform.m[2][2] - obj.pObj->height / 2 }; //bot right
		yzCoords[3] = AEVec2{ obj.transform.m[1][2] + obj.pObj->width / 2, obj.transform.m[2][2] - obj.pObj->height / 2 }; //bot left

		//TODO: Any rotatation 
		return yzCoords;
	}

	AEVec2* GetVerticesXZ(const ObjectInst obj, int& count) {
		if (1) { //TODO: Change to check if not a staircase
			count = 4;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.transform.m[0][2] - obj.pObj->width / 2, obj.transform.m[2][2] + obj.pObj->height / 2 }; // top right
			xzCoords[1] = AEVec2{ obj.transform.m[0][2] + obj.pObj->width / 2, obj.transform.m[2][2] + obj.pObj->height / 2 }; // top left
			xzCoords[2] = AEVec2{ obj.transform.m[0][2] - obj.pObj->width / 2, obj.transform.m[2][2] - obj.pObj->height / 2 }; // bot right
			xzCoords[3] = AEVec2{ obj.transform.m[0][2] + obj.pObj->width / 2, obj.transform.m[2][2] - obj.pObj->height / 2 }; // bot left
			return xzCoords;
		}
		else {
			count = 3;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.transform.m[0][2] - obj.pObj->width / 3,
									obj.transform.m[2][2] - obj.pObj->height / 3 };		// bot left

			xzCoords[1] = AEVec2{ obj.transform.m[0][2] - obj.pObj->width / 3,
									obj.transform.m[2][2] + (2 * obj.pObj->height) / 3 }; // top left

			xzCoords[2] = AEVec2{ obj.transform.m[0][2] + (2 * obj.pObj->width) / 3,
									obj.transform.m[2][2] - obj.pObj->height / 3 };		// bot right

			return xzCoords;
		}
	}

	AEMtx33 ConvertIsometric(const ObjectInst& obj) {
		AEMtx33 transform = obj.transform;
		transform.m[0][2] = obj.transform.m[0][2] + obj.transform.m[1][2];
		transform.m[1][2] = -0.5f * obj.transform.m[0][2] + 0.5f * obj.transform.m[1][2] + obj.transform.m[2][2];
		return transform;
	}
}