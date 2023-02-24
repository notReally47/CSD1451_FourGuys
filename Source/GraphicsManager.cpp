#include "PCH.h"

namespace OM
{
	/*Set rendering modes, colour tints, blending and transparency*/
	void RenderSettings()
	{
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
	}

	/*Render objects that have textures*/
	void ObjectInst::RenderObject()
	{
		AEGfxTextureSet(this->pObj->pTex, this->tex_offset.x, this->tex_offset.y);
		AEGfxSetTransform(ConvertIsometric(*this).m);
		//AEGfxSetTransform(this->transform.m);
		AEGfxMeshDraw(this->pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	void Character::AnimateCharacter()
	{
		this->SetOffsetX();
		this->SetOffsetY();
		this->pObjInst->RenderObject();
	}
}