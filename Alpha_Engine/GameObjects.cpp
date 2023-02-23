#include "pch.h"
#include "AnimationHandler.h"
//#include <string>
//#include <iostream>

namespace GameObjects
{
	/*DEFINES*/
	s8 fontId;

	// Scale of Object Instance in width
	f32& ObjectInst::GetScaleX() { return this->transform.m[0][0]; } // check if this is used anywhere

	// Position X in world screen coordinates
	f32& ObjectInst::GetPosX() { return this->transform.m[0][2]; }

	f32 ObjectInst::GetPosX() const { return this->transform.m[0][2]; }

	// Scale of Object Instance in height
	f32& ObjectInst::GetScaleY() { return this->transform.m[1][1]; }

	// Position Y in world screen coordinates
	f32& ObjectInst::GetPosY() { return this->transform.m[1][2]; }

	f32 ObjectInst::GetPosY() const { return this->transform.m[1][2]; }

	// Elapsed time of animation
	f32& ObjectInst::GetElapsed() { return this->transform.m[2][0]; }

	// Speed of the player's movement
	f32& ObjectInst::GetPlayerSpeed() { return this->transform.m[2][1]; }

	// Elevation of the Object Instance
	f32& ObjectInst::GetPosZ() { return this->transform.m[2][2]; }

	f32 ObjectInst::GetPosZ() const { return this->transform.m[2][2]; }

	AEVec2 ObjectInst::GetPosXY() { return { this->GetPosX(), this->GetPosY() }; }


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
			if (obj.flag == Enum::FLAG::ACTIVE) {
				/*TRANSFORMATION (TRS)*/
				AEMtx33 highlight{ obj.transform };
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
			if (obj.flag == Enum::FLAG::ISO_UP) {
				obj.GetElapsed() += dt;
				obj.GetPosX() -= dt * 10.f;
				obj.GetPosY() += dt * 5.f;
				obj.flag = (obj.GetElapsed() > 5.f) ? (obj.GetElapsed() = .0f, Enum::FLAG::ISO_UP) : obj.flag;
			}
			else if (obj.flag == Enum::FLAG::ISO_DOWN) {
				obj.GetElapsed() += dt;
				obj.GetPosX() += dt * 10.f;
				obj.GetPosY() -= dt * 5.f;
				obj.flag = (obj.GetElapsed() > 5.f) ? (obj.GetElapsed() = .0f, Enum::FLAG::ISO_DOWN) : obj.flag;
			}
			else if (obj.flag == Enum::FLAG::ISO_LEFT) {
				obj.GetElapsed() += dt;
				obj.GetPosX() -= dt * 10.f;
				obj.GetPosY() -= dt * 5.f;
				obj.flag = (obj.GetElapsed() > 5.f) ? (obj.GetElapsed() = .0f, Enum::FLAG::ISO_LEFT) : obj.flag;
			}
			else if (obj.flag == Enum::FLAG::ISO_RIGHT) {
				obj.GetElapsed() += dt;
				obj.GetPosX() += dt * 10.f;
				obj.GetPosY() += dt * 5.f;
				obj.flag = (obj.GetElapsed() > 5.f) ? (obj.GetElapsed() = .0f, Enum::FLAG::ISO_RIGHT) : obj.flag;
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
	//		AEVec2{ obj.GetPosX() - obj.transform.m[0][0], obj.GetPosY() + obj.transform.m[1][1] },
	//		AEVec2{ obj.GetPosX() + obj.transform.m[0][0], obj.GetPosY() + obj.transform.m[1][1] },
	//		AEVec2{ obj.GetPosX() + obj.transform.m[0][0], obj.GetPosY() - obj.transform.m[1][1] },
	//		AEVec2{ obj.GetPosX() - obj.transform.m[0][0], obj.GetPosY() - obj.transform.m[1][1] }
	//	};

	//	/* Get vertex after rotation. Vertex rotates around the center of the mesh */
	//	for (int i = 0; i < 4; i++) {
	//		f32 posX = original[i].x - obj.GetPosX();
	//		f32 posY = original[i].y - obj.GetPosY();
	//		vertices[i].x = posX * static_cast<f32>(cos(-.0f)) - posY * static_cast<f32>(sin(-.0f)) + obj.GetPosX();
	//		vertices[i].y = posX * static_cast<f32>(sin(-.0f)) + posY * static_cast<f32>(cos(-.0f)) + obj.GetPosY();
	//	}

	//	return vertices;
	//}

	AEVec2* GetVerticesXY(const ObjectInst& obj, int& count) {
		count = 4;

		AEVec2* xyCoords = { new AEVec2[count] };
		xyCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosY() + obj.pObj->length / 2 }; //top right
		xyCoords[1] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosY() + obj.pObj->length / 2 }; //top left
		xyCoords[2] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosY() - obj.pObj->length / 2 }; //bot right
		xyCoords[3] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosY() - obj.pObj->length / 2 }; //bot left

		//TODO: Any rotatation 
		return xyCoords;
	}

	AEVec2* GetVerticesYZ(const ObjectInst& obj, int& count) {
		count = 4;
		AEVec2* yzCoords = { new AEVec2[count] };
		yzCoords[0] = AEVec2{ obj.GetPosY() - obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; //top right
		yzCoords[1] = AEVec2{ obj.GetPosY() + obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; //top left
		yzCoords[2] = AEVec2{ obj.GetPosY() - obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; //bot right
		yzCoords[3] = AEVec2{ obj.GetPosY() + obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; //bot left

		//TODO: Any rotatation 
		return yzCoords;
	}

	AEVec2* GetVerticesXZ(const ObjectInst& obj, int& count) {
		if (1) { //TODO: Change to check if not a staircase
			count = 4;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; // top right
			xzCoords[1] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosZ() + obj.pObj->height / 2 }; // top left
			xzCoords[2] = AEVec2{ obj.GetPosX() - obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; // bot right
			xzCoords[3] = AEVec2{ obj.GetPosX() + obj.pObj->width / 2, obj.GetPosZ() - obj.pObj->height / 2 }; // bot left
			return xzCoords;
		}
		else {
			count = 3;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.GetPosX() - obj.pObj->width / 3,
									obj.GetPosZ() - obj.pObj->height / 3 };		// bot left

			xzCoords[1] = AEVec2{ obj.GetPosX() - obj.pObj->width / 3,
									obj.GetPosZ() + (2 * obj.pObj->height) / 3 }; // top left

			xzCoords[2] = AEVec2{ obj.GetPosX() + (2 * obj.pObj->width) / 3,
									obj.GetPosZ() - obj.pObj->height / 3 };		// bot right

			return xzCoords;
		}
	}

	AEMtx33 ConvertIsometric(const ObjectInst& obj) {
		AEMtx33 transform = obj.transform;
		transform.m[0][2] = obj.GetPosX() + obj.GetPosY();
		transform.m[1][2] = -0.5f * obj.GetPosX() + 0.5f * obj.GetPosY() + obj.GetPosZ();
		return transform;
	}
}