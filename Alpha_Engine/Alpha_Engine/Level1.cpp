#include "Level1.h"
#include "AEEngine.h"
#include "InputHandler.h"
namespace Level1 {

	AEGfxVertexList* pMesh1, * pMesh2, * pMeshLine;
	AEGfxTexture* pTex1, * pTex2;
	float obj1X, obj1Y, objtexX, objtexY, camX, camY;
	int counter;
	s8 fontId;

	/*LOAD ASSETS*/
	void Level1_Load() {
		//pTex1 = AEGfxTextureLoad("PlanetTexture.png");
		//AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");

		//pTex2 = AEGfxTextureLoad("YellowTexture.png");
		//AE_ASSERT_MESG(pTex2, "Failed to create texture2!!");

		fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12);
	}

	/*INITIALIZE DATA*/
	void Level1_Init() {
		obj1X = 0.0f, obj1Y = 0.0f, objtexX = 0.0f, objtexX = 0.0f;
		counter = 1;
		////////////////////////////////
		// Creating the objects (Shapes)
		// 1 triangle at a time
		// X, Y, Color, texU, texV
		AEGfxMeshStart();
		AEGfxTriAdd(
			-25.5f, -25.5f, 0xFFFF0000, 0.0f, 0.0f,
			25.5f, 0.0f, 0xFFFF0000, 0.0f, 0.0f,
			-25.5f, 25.5f, 0xFFFF0000, 0.0f, 0.0f);

		// Saving the mesh (list of triangles) in pMesh1

		pMesh1 = AEGfxMeshEnd();
		AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");
		AEGfxMeshStart();
		// This shape has 2 triangles
		AEGfxTriAdd(
			-30.0f, -30.0f, 0x00FF00FF, 0.0f, 1.0f,
			30.0f, -30.0f, 0x00FFFF00, 1.0f, 1.0f,
			-30.0f, 30.0f, 0x0000FFFF, 0.0f, 0.0f);

		AEGfxTriAdd(
			30.0f, -30.0f, 0x00FFFFFF, 1.0f, 1.0f,
			30.0f, 30.0f, 0x00FFFFFF, 1.0f, 0.0f,
			-30.0f, 30.0f, 0x00FFFFFF, 0.0f, 0.0f);

		// Saving the mesh (list of triangles) in pMesh2

		pMesh2 = AEGfxMeshEnd();
		AE_ASSERT_MESG(pMesh2, "Failed to create mesh 2!!");

		// Informing the library that we're about to start adding vertices
		AEGfxMeshStart();

		// This shape has 5 vertices
		AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
		AEGfxVertexAdd(100.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
		AEGfxVertexAdd(200.0f, 150.0f, 0xFFFFFFFF, 0.0f, 0.0f);
		AEGfxVertexAdd(300.0f, -100.0f, 0xFFFFFFFF, 0.0f, 0.0f);
		AEGfxVertexAdd(100.0f, -250.0f, 0xFFFFFFFF, 0.0f, 0.0f);


		pMeshLine = AEGfxMeshEnd();
		AE_ASSERT_MESG(pMeshLine, "Failed to create line mesh!!");
	}

	void Level1_Update() {
		using namespace InputHandler;

		/*INPUT HANDLING*/
		AEInputUpdate();
		MoveObject(obj1Y, obj1X);
		ChangeTexture(objtexX, objtexY);
		MoveCamera(camX, camY);

		/*LOGIC*/
		//++counter;
		//if (counter < 120)
		//	AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
		//else if (counter < 240)
		//	AEGfxTextureSet(pTex2, objtexX, objtexY);		// Same object, different texture
		//else
		//{
		//	AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
		//	counter = 0;
		//}

		//++counter;
		//if (counter < 120)
		//	AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
		//else if (counter < 240)
		//	AEGfxTextureSet(pTex2, objtexX, objtexY);		// Same object, different texture
		//else
		//{
		//	AEGfxTextureSet(pTex1, objtexX, objtexY);		// Same object, different texture
		//	counter = 0;
		//}
	}

	void Level1_Draw() {
		// Drawing object 1
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// Set position for object 1
		AEGfxSetPosition(obj1X, obj1Y);

		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);
		// No tint
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

		// Drawing object 2 - (first) - No tint
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set position for object 2
		AEGfxSetPosition(100.0f, -60.0f);
		// No tint
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Set texture
		//AEGfxTextureSet(pTex1, objtexX, objtexY);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
		// Set Transparency
		AEGfxSetTransparency(1.0f);

		// Drawing object 3 - (Second) - Blue tint
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		// Set position for object 3
		AEGfxSetPosition(100.0f, 60.0f);
		// Add Blue tint
		AEGfxSetTintColor(0.0f, 0.0f, 1.0f, 1.0f);

		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
		// Set Transparency
		AEGfxSetTransparency(1.0f);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetPosition(0.0f, 0.0f);
		AEGfxMeshDraw(pMeshLine, AE_GFX_MDM_LINES_STRIP);

		char strBuffer[100];
		memset(strBuffer, 0, 100 * sizeof(char));
		sprintf_s(strBuffer, "Frame Time:  %.6f", AEFrameRateControllerGetFrameTime());

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxPrint(fontId, strBuffer, -0.95, -0.95, 1.0f, 1.f, 1.f, 1.f);

		f32 TextWidth, TextHeight;
		AEGfxGetPrintSize(fontId, strBuffer, 1.0f, TextWidth, TextHeight);
		AEGfxPrint(fontId, strBuffer, 0.99 - TextWidth, 0.99 - TextHeight, 1.0f, 1.f, 1.f, 1.f);
	}

	void Level1_Free() {
		AEGfxMeshFree(pMesh1);
		AEGfxMeshFree(pMesh2);
		AEGfxMeshFree(pMeshLine);
		//AEGfxTextureUnload(pTex1);
		//AEGfxTextureUnload(pTex2);
		AEGfxDestroyFont(fontId);
	}

	void Level1_Unload() {
		//something
	}
}