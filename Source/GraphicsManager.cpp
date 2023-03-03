/*!***********************************************************************
  \file   GraphicsManager.cpp
  \authors 

  \brief 
  This file contains the implementation of the graphics manager

  \copyright  
  Copyright (C) 2023 DigiPen Institute of Technology.
  Reproduction or disclosure of this file or its contents without the
  prior written consent of DigiPen Institute of Technology is prohibited.
*************************************************************************/
#include "PCH.h"

namespace OM
{
	/*!***********************************************************************
	  \brief Set rendering modes, colour tints, blending and transparency
	  
	*************************************************************************/
	void RenderSettings()
	{
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);
	}

	/*!***********************************************************************
	  \brief Render objects that have textures
	  
	*************************************************************************/
	void ObjectInst::RenderObject()
	{
		AEGfxTextureSet(pObj->pTex, tex_offset.x, tex_offset.y);
		AEGfxSetTransform(ConvertIsometric(*this).m);
		//AEGfxSetTransform(transform.m);
		AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);
	}

	/*!***********************************************************************
	  \brief Animate the character
	  
	*************************************************************************/
	void Character::AnimateCharacter()
	{
		SetOffsetX();
		SetOffsetY();
		//pObjInst->RenderShadow();
		pObjInst->RenderObject();
	}

	/*!***********************************************************************
	  \brief Render the shadow of the character

	*************************************************************************/
	void ObjectInst::RenderShadow()
	{
		AEMtx33 shadow{transform};

		AEVec2 scale = GetScaleXY();

		AEVec2Scale(&scale, &scale, 1.1f);
		AEGfxSetTransform(ConvertIsometric(*this).m);

		AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 1.0f);
		AEGfxSetTransparency(0.2f);

		AEGfxMeshDraw(pObj->pMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxSetBlendColor(1.0f, 1.0f, 1.0f, 0.0f);
		AEGfxSetTransparency(1.0f);
	}
}