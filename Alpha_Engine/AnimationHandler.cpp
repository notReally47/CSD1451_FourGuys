#include "pch.h"
#include "AnimationHandler.h"
#include "GSM.h"

namespace AnimationHandler {
	using namespace GameObjects;

	/*Get direction the player is facing and set according to the spritesheet row.*/
	void setTextureOffsetY(Character& character) {
		if (checkDirection(character, 1, 1)) { //UPRIGHT
			character.pTexOffsetY = 1;
		}
		else if (checkDirection(character, 1, 0)) { //UP
			character.pTexOffsetY = 2;
		}
		else if (checkDirection(character, 1, -1)) { //UPLEFT
			character.pTexOffsetY = 3;
		}
		else if (checkDirection(character, 0, -1)) { //LEFT
			character.pTexOffsetY = 4;
		}
		else if (checkDirection(character, -1, -1)) { //DOWNLEFT
			character.pTexOffsetY = 5;
		}
		else if (checkDirection(character, -1, 0)) { //DOWN
			character.pTexOffsetY = 6;
		}
		else if (checkDirection(character, -1, 1)) { //DOWNRIGHT
			character.pTexOffsetY = 7;
		}
		else if (checkDirection(character, 0, 1)) { //RIGHT
			character.pTexOffsetY = 0;
		}
	}

	/*Iterates through the spritesheets columns if the player is moving*/
	void setTextureOffsetX(Character& character) {
		if (character.isMoving) {
			if (GSM::gameTime >= 0.1f) {
				character.spriteIteration++;
				character.spriteIteration %= (character.spriteX - 1);
				GSM::gameTime = 0.f;
			}
			character.pTexOffsetX = character.spriteIteration + 1;
		}
		else {
			character.pTexOffsetX = 0;
		}
	}

	/*Helper function to compare the x and y coordinates with 2 respective values.*/
	bool checkDirection(Character character, int a, int b) {
		int x = static_cast<int>(character.input.x);
		int y = static_cast<int>(character.input.y);
		return (x == a && y == b);
	}

	/*Set the texture offset and render the player. This will create the animation.*/
	void AnimateCharacter(Character& character) {
		/*SETTINGS*/
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		/*Set texture*/
		setTextureOffsetX(character);
		setTextureOffsetY(character);
		AEGfxTextureSet(character.obj.pTex,
			static_cast<f32>(character.pTexOffsetX) / static_cast<f32>(character.spriteX),
			static_cast<f32>(character.pTexOffsetY) / static_cast<f32>(character.spriteY));

		/*CLOCKWISE ROTATION*/
		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, AEDegToRad(character.obj.rotation));

		/*SCALING*/
		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, character.obj.width, character.obj.height);

		/*TRANSLATION/POSITION*/
		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, character.obj.pos.x, character.obj.pos.y);

		/*TRANSFORMATION (TRS)*/
		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);
		AEGfxSetTransform(transform.m);

		/*DRAW MESH*/
		AEGfxMeshDraw(character.obj.pMesh, AE_GFX_MDM_TRIANGLES);
	}
}