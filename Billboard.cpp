
/*-----------------------------------------------------------

　　　　　　　　　　　ビルボードの関数

------------------------------------------------------------*/


#include <d3dx9.h>
#include "Mydirect3d.h"
#include "Config.h"
#include "TextureManager.h"

//頂点構造体
typedef struct BillboardVertex_tag
{
	D3DXVECTOR3 Position;
	D3DCOLOR    Color;
	D3DXVECTOR2 TexCoord;

}BillboardVertex;

//順番
#define FVF_BILLBOARDVERTEX3D (D3DFVF_XYZ| D3DFVF_DIFFUSE|D3DFVF_TEX1)
/*---------------------
　　　グローバル変数
-----------------------*/

static D3DXMATRIX g_MtxView;
static D3DCOLOR g_Color = 0xffffffff;



void Billboard_Init() 
{
	D3DXMatrixIdentity(&g_MtxView);
}

void Billboard_SetViewMatrix(const D3DXMATRIX& mtxview) 
{
	g_MtxView = mtxview;

}


void Billboard_Uninit() 
{

}


void Billboard_Draw(int textureID, float x, float y, float z ,float sizex , float sizey,float size) 
{
	BillboardVertex Billboard[] = {
	{{-sizex,-sizey,0.0f},g_Color,{0.0f,1.0f}} ,
	{{-sizex, sizey,0.0f},g_Color,{0.0f,0.0f}} ,
	{{ sizex,-sizey,0.0f},g_Color,{1.0f,1.0f}} ,
	{{ sizex, sizey,0.0f},g_Color,{1.0f,0.0f}} 
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MtxWorld,MtxT,mtxS;
	D3DXMATRIX MtxInvView = g_MtxView;
	//ビュー行列の逆行列なんだけど平行移動成分がxyz = 0
	MtxInvView._41 = 0.0f;
	MtxInvView._42 = 0.0f;
	MtxInvView._43 = 0.0f;
	//Transpose(転置行列)は重いので、なるべくつかわない
	//D3DXMatrixTranspose(&MtxInvView, &MtxInvView);
	
	D3DXMatrixInverse(&MtxInvView, NULL, &MtxInvView);
	D3DXMatrixTranslation(&MtxT,x,y,z);
	D3DXMatrixScaling(&mtxS, size, size, size);
	MtxWorld = mtxS * MtxInvView * MtxT;

	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//
	////Zバッファーへの書き込みはしない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);
	pDevice->SetFVF(FVF_BILLBOARDVERTEX3D);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2, Billboard,sizeof(BillboardVertex));
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//
	////Zバッファーへの書き込みはしない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void Billboard_DrawNonZBuffer(int textureID, float x, float y, float z, float sizex, float sizey, float size)
{
	BillboardVertex Billboard[] = {
	{{-sizex,-sizey,0.0f},g_Color,{0.0f,1.0f}} ,
	{{-sizex, sizey,0.0f},g_Color,{0.0f,0.0f}} ,
	{{ sizex,-sizey,0.0f},g_Color,{1.0f,1.0f}} ,
	{{ sizex, sizey,0.0f},g_Color,{1.0f,0.0f}}
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MtxWorld, MtxT, mtxS;
	D3DXMATRIX MtxInvView = g_MtxView;
	//ビュー行列の逆行列なんだけど平行移動成分がxyz = 0
	MtxInvView._41 = 0.0f;
	MtxInvView._42 = 0.0f;
	MtxInvView._43 = 0.0f;
	//Transpose(転置行列)は重いので、なるべくつかわない
	//D3DXMatrixTranspose(&MtxInvView, &MtxInvView);

	D3DXMatrixInverse(&MtxInvView, NULL, &MtxInvView);
	D3DXMatrixTranslation(&MtxT, x, y, z);
	D3DXMatrixScaling(&mtxS, size, size, size);
	MtxWorld = mtxS * MtxInvView * MtxT;

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	
	//Zバッファーへの書き込みはしない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);
	pDevice->SetFVF(FVF_BILLBOARDVERTEX3D);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Billboard, sizeof(BillboardVertex));
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	//Zバッファーへの書き込みはしない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}


void Billboard_DrawAnimation(int textureID, float x, float y, float z, float sizex, float sizey, int tcx, int tcy, int tcw, int tch)
{

	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;


	BillboardVertex Billboard[] = {
	{{-sizex,-sizey,0.0f},g_Color,{u0, v1}} ,
	{{-sizex, sizey,0.0f},g_Color,{u0, v0}} ,
	{{ sizex,-sizey,0.0f},g_Color,{u1, v1}} ,
	{{ sizex, sizey,0.0f},g_Color,{u1, v0}}
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MtxWorld, MtxT;
	D3DXMATRIX MtxInvView = g_MtxView;
	//ビュー行列の逆行列なんだけど平行移動成分がxyz = 0
	MtxInvView._41 = 0.0f;
	MtxInvView._42 = 0.0f;
	MtxInvView._43 = 0.0f;
	//Transpose(転置行列)は重いので、なるべくつかわない
	//D3DXMatrixTranspose(&MtxInvView, &MtxInvView);

	D3DXMatrixInverse(&MtxInvView, NULL, &MtxInvView);
	D3DXMatrixTranslation(&MtxT, x, y, z);
	MtxWorld = MtxInvView * MtxT;

	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//
	////Zバッファーへの書き込みはしない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);
	pDevice->SetFVF(FVF_BILLBOARDVERTEX3D);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Billboard, sizeof(BillboardVertex));
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//
	////Zバッファーへの書き込みはしない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}





void Billboard_DrawAnimationNonZBuffer(int textureID, float x, float y, float z, float sizex, float sizey, int tcx, int tcy, int tcw, int tch)
{

	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;


	BillboardVertex Billboard[] = {
	{{-sizex,-sizey,0.0f},g_Color,{u0, v1}} ,
	{{-sizex, sizey,0.0f},g_Color,{u0, v0}} ,
	{{ sizex,-sizey,0.0f},g_Color,{u1, v1}} ,
	{{ sizex, sizey,0.0f},g_Color,{u1, v0}}
	};

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX MtxWorld, MtxT;
	D3DXMATRIX MtxInvView = g_MtxView;
	//ビュー行列の逆行列なんだけど平行移動成分がxyz = 0
	MtxInvView._41 = 0.0f;
	MtxInvView._42 = 0.0f;
	MtxInvView._43 = 0.0f;
	//Transpose(転置行列)は重いので、なるべくつかわない
	//D3DXMatrixTranspose(&MtxInvView, &MtxInvView);

	D3DXMatrixInverse(&MtxInvView, NULL, &MtxInvView);
	D3DXMatrixTranslation(&MtxT, x, y, z);
	MtxWorld = MtxInvView * MtxT;

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	
	//Zバッファーへの書き込みはしない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);
	pDevice->SetFVF(FVF_BILLBOARDVERTEX3D);
	pDevice->SetTexture(0, Texture_GetTexture(textureID));
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Billboard, sizeof(BillboardVertex));
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	//Zバッファーへの書き込みはしない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void Billboard_SetColor(D3DCOLOR color)
{
	g_Color = color;
}