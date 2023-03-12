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
	using enum TYPE;
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
		if (pO->type == STAIRS && flag & Enum::ACTIVE)
			AnimateStairs();
		AEGfxTextureSet(pO->pTex, texture.x, texture.y);
		/*		if (this->pO->type == BUBBLE)
		{
			AEGfxSetTransparency(0.5f);
		}
		if (this->pO->type == BUTTON || this->pO->type == BACKGROUND)
		{
			AEGfxSetTransform(this->transf.m);
		}
		else*/

			AEGfxSetTransform(ConvertIsometric(*this).m);
			//AEGfxSetTransform(transf.m);
		AEGfxMeshDraw(pO->pMesh, AE_GFX_MDM_TRIANGLES);
	}
	/*!***********************************************************************
	  \brief Animate the character

	*************************************************************************/
	void Character::AnimateCharacter()
	{
		SetOffsetX();
		SetOffsetY();
		// pOI->RenderShadow();
		pOI->RenderObject();
	}
	void ObjectInst::AnimateStairs()
	{
		SetCounter(GSM::gameTime);
		if (GetCounter() >= 0.1f)
		{
			texture.x += 0.0476190476190476f;
			ResetCounter();
		}
		if (texture.x >= 0.89f && texture.x >= 0.91f)
		{
			flag &= ~Enum::FLAG::ACTIVE;
		}
	}
	/*!***********************************************************************
	  \brief Render the shadow of the character

	*************************************************************************/
	void ObjectInst::RenderShadow()
	{
		/*
		AEGfxSetTransform(ConvertIsometric(*this).m);

		AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 1.0f);
		AEGfxSetTransparency(0.2f);

		AEGfxMeshDraw(pO->pMesh, AE_GFX_MDM_TRIANGLES);

		AEGfxSetBlendColor(1.0f, 1.0f, 1.0f, 0.0f);
		AEGfxSetTransparency(1.0f);*/
	}
	/*!***********************************************************************
	  \brief Render the glow of the portraits

	*************************************************************************/
	void ObjectInst::RenderGlow()
	{
		ObjectInst glow(*this);

		glow.SetScale(1.1f);

		AEGfxSetBlendColor(1.0f, 1.0f, 0.0f, 0.7f);
		glow.RenderObject();
		AEGfxSetBlendColor(1.0f, 1.0f, 1.0f, 0.0f);
	}
	f32 GetScreenXPercentage(f32 posX)
	{
		return -1.0f + ((static_cast<f32>(AEGetWindowWidth()) / 2.0f + posX) / AEGetWindowWidth()) * 2.0f;
	}
	f32 GetScreenYPercentage(f32 posY)
	{
		return -1.0f + ((static_cast<f32>(AEGetWindowHeight()) / 2.0f + posY) / AEGetWindowHeight()) * 2.0f;
	}

}