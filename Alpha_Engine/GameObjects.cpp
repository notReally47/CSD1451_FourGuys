#include "pch.h"
#include "AnimationHandler.h"
#include <iostream>
//#include <string>
//#include <iostream>

namespace GameObjects
{
	/*DEFINES*/
	s8 fontId;
	const unsigned char		FLAG_INACTIVE = 0x0;
	const unsigned char		FLAG_ACTIVE = 0x1;
	const unsigned char		FLAG_ALT1_S = 0x2;
	const unsigned char		FLAG_ALT1_E = 0x3;
	const unsigned char		FLAG_ALT2_S = 0x4;
	const unsigned char		FLAG_ALT2_E = 0x5;

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
	void RenderObject(ObjectInst& obj)
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
			/*if (obj.flag == FLAG_ALT1_S) {
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
			}*/
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

		AEGfxSetTransform(GameObjects::ConvertIsometric(obj).m);
		//AEGfxSetTransform(obj.transform.m);
		/*DRAW MESH*/
		AEGfxMeshDraw(obj.pObj->pMesh, AE_GFX_MDM_TRIANGLES);
		//AEGfxSetTransparency(1.0f);

	}

	f32 GetLineFromDirection(ObjectInst obj, ObjectInst player, int direction) {
		AEVec2 line[2];
		switch (direction) {
		case Enum::NORTH: // y increaseing
			line[0] = AEVec2{ obj.transform.m[0][2] - 0.5f, obj.transform.m[1][2] - 0.5f };
			line[1] = AEVec2{ obj.transform.m[0][2] + 0.5f, obj.transform.m[1][2] - 0.5f };
			break;
		case Enum::SOUTH:
			line[0] = AEVec2{ obj.transform.m[0][2] - 0.5f, obj.transform.m[1][2] + 0.5f };
			line[1] = AEVec2{ obj.transform.m[0][2] + 0.5f, obj.transform.m[1][2] + 0.5f };
			break;
		case Enum::EAST:
			line[0] = AEVec2{ obj.transform.m[0][2] - 0.5f, obj.transform.m[1][2] - 0.5f };
			line[1] = AEVec2{ obj.transform.m[0][2] - 0.5f, obj.transform.m[1][2] + 0.5f };
			break;
		case Enum::WEST:
			line[0] = AEVec2{ obj.transform.m[0][2] + 0.5f, obj.transform.m[1][2] - 0.5f };
			line[1] = AEVec2{ obj.transform.m[0][2] + 0.5f, obj.transform.m[1][2] + 0.5f };
			break;
		default:
			break;
		}
		AEVec2 pos = { player.transform.m[0][2],
						player.transform.m[1][2] };
		f32 distance = 1.f / distanceFromAEVec2ToLine(pos, line);

		//distance *= obj.pObj->length * distance;
		std::cout << distance << std::endl;
		//return line;
		return distance;
	}

	AEVec2* GetVerticesXY(const ObjectInst obj, int& count) {
		count = 4;
		AEVec2* xyCoords = { new AEVec2[count] };

		xyCoords[0] = AEVec2{ obj.transform.m[0][2] * obj.pObj->width - obj.pObj->width / 2.f, obj.transform.m[1][2] * obj.pObj->length + obj.pObj->length / 2.f }; //top right
		xyCoords[1] = AEVec2{ obj.transform.m[0][2] * obj.pObj->width + obj.pObj->width / 2.f, obj.transform.m[1][2] * obj.pObj->length + obj.pObj->length / 2.f }; //top left
		xyCoords[2] = AEVec2{ obj.transform.m[0][2] * obj.pObj->width + obj.pObj->width / 2.f, obj.transform.m[1][2] * obj.pObj->length - obj.pObj->length / 2.f }; //bot right
		xyCoords[3] = AEVec2{ obj.transform.m[0][2] * obj.pObj->width - obj.pObj->width / 2.f, obj.transform.m[1][2] * obj.pObj->length - obj.pObj->length / 2.f }; //bot left

		//TODO: Any rotatation 
		return xyCoords;
	}

	AEVec2* GetVerticesXZ(const ObjectInst obj, int& count) {
		if (/*obj.pObj->type != Enum::PLATFORM*/1) { //TODO: Change to check if not a staircase
			count = 4;
			AEVec2* xzCoords = { new AEVec2[count] };
			xzCoords[0] = AEVec2{ obj.transform.m[0][2] - obj.pObj->width / 2, obj.transform.m[1][2] + obj.pObj->height / 2 }; //top right
			xzCoords[1] = AEVec2{ obj.transform.m[0][2] + obj.pObj->width / 2, obj.transform.m[1][2] + obj.pObj->height / 2 }; //top left
			xzCoords[2] = AEVec2{ obj.transform.m[0][2] + obj.pObj->width / 2, obj.transform.m[1][2] - obj.pObj->height / 2 }; //bot right
			xzCoords[3] = AEVec2{ obj.transform.m[0][2] - obj.pObj->width / 2, obj.transform.m[1][2] - obj.pObj->height / 2 }; //bot left
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

	AEVec2* GetVerticesYZ(const ObjectInst obj, int& count) {
		if (obj.pObj->type == Enum::PLAYER) {
			count = 4;
			AEVec2* yzCoords = { new AEVec2[count] };
			yzCoords[0] = AEVec2{ obj.transform.m[1][2] - obj.pObj->width / 2, obj.transform.m[2][2] + obj.pObj->height / 2 }; //top right
			yzCoords[3] = AEVec2{ obj.transform.m[1][2] + obj.pObj->width / 2, obj.transform.m[2][2] + obj.pObj->height / 2 }; //top left
			yzCoords[1] = AEVec2{ obj.transform.m[1][2] - obj.pObj->width / 2, obj.transform.m[2][2] - obj.pObj->height / 2 }; //bot right
			yzCoords[2] = AEVec2{ obj.transform.m[1][2] + obj.pObj->width / 2, obj.transform.m[2][2] - obj.pObj->height / 2 }; //bot left

			//TODO: Any rotatation 
			return yzCoords;
		}
		count = 3;
		AEVec2* yzCoords = { new AEVec2[count] };
		//yzCoords[0] = AEVec2{ obj.transform.m[1][2] - obj.pObj->length / 2, obj.transform.m[2][2] + obj.pObj->height / 2 }; //top right
		yzCoords[0] = AEVec2{ obj.transform.m[1][2] + obj.pObj->width / 2, obj.transform.m[2][2] + obj.pObj->height / 2 }; //top left
		yzCoords[1] = AEVec2{ obj.transform.m[1][2] - obj.pObj->length / 2, obj.transform.m[2][2] - obj.pObj->height / 2 }; //bot right
		yzCoords[2] = AEVec2{ obj.transform.m[1][2] + obj.pObj->length / 2, obj.transform.m[2][2] - obj.pObj->height / 2 }; //bot left

		//TODO: Any rotatation 
		return yzCoords;
	}

	AEMtx33 ConvertIsometric(const ObjectInst& obj) {
		AEMtx33 transform = obj.transform;
		f32 xPos = obj.transform.m[0][2];
		f32 yPos = obj.transform.m[1][2];
		f32 zPos = obj.transform.m[2][2];

		transform.m[0][2] = (xPos - yPos) * 64.f;
		transform.m[1][2] = (xPos + yPos) * 64.f / 2.f + zPos + obj.pObj->height / 2.f;
		return transform;
	}

	void ConvertWorld(f32& x, f32& y) {
		f32 x1, y1;
		x1 = x;
		y1 = y;

		x = y + x / 2;
		y = y - x / 2;
	}

	AEVec2* SquareCollider(AEVec2 center, f32 width, f32 height, int& count) {
		AEVec2* out = new AEVec2[4];
		out[0] = AEVec2{ center.x - width / 2.f, center.y + height / 2.f };
		out[1] = AEVec2{ center.x + width / 2.f, center.y + height / 2.f };
		out[2] = AEVec2{ center.x - width / 2.f, center.y - height / 2.f };
		out[3] = AEVec2{ center.x - width / 2.f, center.y - height / 2.f };
		count = 4;
		return out;
	}

	f32 distance(AEVec2 p1, AEVec2 p2) {
		return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	}

	// Calculate the distance from a AEVec2 to a line
	f32 distanceFromAEVec2ToLine(AEVec2 p, AEVec2* l) {
		f32 A = p.x - l[0].x;
		f32 B = p.y - l[0].y;
		f32 C = l[1].x - l[0].x;
		f32 D = l[1].y - l[0].y;

		f32 dot = A * C + B * D;
		f32 len_sq = C * C + D * D;
		f32 param = dot / len_sq;

		f32 xx, yy;

		if (param < 0) {
			xx = l[0].x;
			yy = l[0].y;
		}
		else if (param > 1) {
			xx = l[1].x;
			yy = l[1].y;
		}
		else {
			xx = l[0].x + param * C;
			yy = l[0].y + param * D;
		}

		return distance(p, { xx, yy });
	}
}