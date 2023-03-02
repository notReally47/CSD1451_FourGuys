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
		AEGfxTextureSet(pObj->pTex, tex_offset.x, tex_offset.y);
		AEGfxSetTransform(ConvertIsometric(*this).m);
		//AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	void Character::AnimateCharacter()
	{
		SetOffsetX();
		SetOffsetY();
		pObjInst->RenderObject();
	}
}