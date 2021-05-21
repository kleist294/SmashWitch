
/*============================================================　
　
　　　　　　影の描画

============================================================*/




#include <d3dx9.h>
#include "Mydirect3d.h"
#include "Config.h"
#include "TextureManager.h"

//頂点構造体
typedef struct Shadow3D_tag
{
	D3DXVECTOR3 Position;

	D3DXVECTOR2 TexCoord;

}Shadow3D;

//順番
#define FVF_VERTEX3D (D3DFVF_XYZ|D3DFVF_TEX1)

static int g_TextureID = INVALID_TEXTURE_ID;



/*============================================================　　
　　　　　　影の初期化
============================================================*/
void ShadowInit()
{
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\effect000.jpg");

}

/*============================================================　　
　　　　　　影の描画
============================================================*/
void ShadowDraw(float x, float y, float z , float size)
{
	static Shadow3D g_ShadowVertexs[] =
	{
		//front
		{{-0.5f, 0.0f, 0.5f},{0.0f,0.0f}},
		{{ 0.5f, 0.0f, 0.5f},{1.0f,0.0f}},
		{{-0.5f,-0.0f,-0.5f},{0.0f,1.0f}},
		{{ 0.5f,-0.0f,-0.5f},{1.0f,1.0f}},
	};

	D3DXMATRIX mtxworld, mtxT,mtxS;

	D3DXMatrixTranslation(&mtxT, x, y, z);
	D3DXMatrixScaling(&mtxS,size, size, size);
	mtxworld = mtxS * mtxT;


	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetTransform(D3DTS_WORLD, &mtxworld);
	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, Texture_GetTexture(g_TextureID));
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_ShadowVertexs, sizeof(Shadow3D));
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
