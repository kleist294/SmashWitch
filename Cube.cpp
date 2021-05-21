
#include <d3dx9.h>
#include "Mydirect3d.h"
#include "Config.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Light.h"

//頂点構造体
typedef struct Vertex3D_tag
{
	D3DXVECTOR3 Position;
	//法線ベクトルの長さは絶対 1
	D3DXVECTOR3 Normal;
	D3DCOLOR    Color;
	D3DXVECTOR2 TexCoord;

}Vertex3D;

//順番
#define FVF_VERTEX3D (D3DFVF_XYZ| D3DFVF_NORMAL| D3DFVF_DIFFUSE|D3DFVF_TEX1)
/*---------------------
　　　グローバル変数
-----------------------*/


static int g_TextureID = INVALID_TEXTURE_ID;


//頂点データの配列(3Dキューブ)
static Vertex3D g_CubeVertexs[] =
{
	//front
	{{-0.5f, 0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.0f}  },
	{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f} },
	{{-0.5f,-0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f} },
//	{{ 0.5f, 0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f} },
	{{ 0.5f,-0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
//	{{-0.5f,-0.5f,-0.5f},{0.0f,0.0f,-1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f} },
	//right
	{{0.5f, 0.5f,-0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.0f} },
	{{0.5f, 0.5f, 0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f} },
	{{0.5f,-0.5f,-0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f} },
//	{{0.5f, 0.5f, 0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f} },
	{{0.5f,-0.5f, 0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
//	{{0.5f,-0.5f,-0.5f},{1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f} },
	//up
	{{-0.5f, 0.5f, 0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.0f}  },
	{{ 0.5f, 0.5f, 0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f} },
	{{-0.5f, 0.5f,-0.5f},{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f} },
//	{{0.5f, 0.5f, 0.5f },{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f} },
	{{0.5f, 0.5f,-0.5f },{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
//	{{-0.5f,0.5f,-0.5f },{0.0f,1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f} },
	//back
	{{0.5f, 0.5f,0.5f}  ,{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.0f }},
	{{-0.5f,0.5f ,0.5f} ,{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f}},
	{{ 0.5f,-0.5f,0.5f} ,{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f}},
//	{{-0.5f, 0.5f,0.5f} ,{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f}},
	{{-0.5f,-0.5f ,0.5f},{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
//	{{ 0.5f,-0.5f,0.5f} ,{0.0f,0.0f,1.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f}},
	//left
	{{-0.5f, 0.5f, 0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.0f}  },
	{{-0.5f, 0.5f,-0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f} },
	{{-0.5f,-0.5f, 0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f} },
//	{{-0.5f, 0.5f,-0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.0f} },
	{{-0.5f,-0.5f,-0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.25f,0.25f}},
//	{{-0.5f,-0.5f, 0.5f},{-1.0f,0.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),{0.0f,0.25f} },
	//down
	{{-0.5f,-0.5f,-0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)  },
	{{ 0.5f,-0.5f,-0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f) },
	{{-0.5f,-0.5f, 0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f) },
//	{{ 0.5f,-0.5f,-0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f) },
	{{ 0.5f,-0.5f, 0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f)},
//	{{-0.5f,-0.5f, 0.5f},{0.0f,-1.0f,0.0f},D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f) },

};

static float g_Angle = 0;

static float g_Value = 0.0f;

//頂点バッファインターフェース
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
//インデックスバッファインターフェース
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;


/*---------------------
　　　　関数定義
-----------------------*/







void Cube_Init()
{

	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\spice_and_wolf.png");

	const D3DXVECTOR2 UV_offset[] =
	{ D3DXVECTOR2(0.0f,0.0f) ,D3DXVECTOR2(0.25f,0.0f) ,D3DXVECTOR2(0.5f,0.0f) ,D3DXVECTOR2(0.75f,0.0f), D3DXVECTOR2(0.0f,0.25f) ,D3DXVECTOR2(0.25f,0.25f) };


	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g_CubeVertexs[i * 4 + j].TexCoord += UV_offset[i];
		}
	}

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	                             //頂点バッファーのbyte数 , 書くだけ , FVF , おまかせ復旧, 取得したインターフェースアドレスを記録するためのポインターアドレス
	pDevice->CreateVertexBuffer(sizeof(Vertex3D) * 24, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	                             //四つの頂点を６面
	
	                        //全頂点に戻すため参照点
	pDevice->CreateIndexBuffer(sizeof(WORD) * 36, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

	Vertex3D *pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, g_CubeVertexs,sizeof(g_CubeVertexs));
	g_pVertexBuffer->Unlock();

	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	for (int i = 0; i < 6; i++)
	{
		
			pIndex[i * 6]     = 4 * i;
			pIndex[i * 6 + 1] = 4 * i + 1;
			pIndex[i * 6 + 2] = 4 * i + 2;
			pIndex[i * 6 + 3] = 4 * i + 1;
			pIndex[i * 6 + 4] = 4 * i + 3;
			pIndex[i * 6 + 5] = 4 * i + 2;
		
	}
	g_pIndexBuffer->Unlock();

	Texture_Load();
}
void Cube_Final()
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
	Texture_Release(&g_TextureID, 1);
}


void Cube_Update()
{
	g_Angle += 0.01f;
	g_Value = sinf(g_Angle) * 5.0f;
	if (g_Value <= 1.0f)
	{
		g_Value = 1.0f;
	}

}
//           見るだけ
void Cube_Draw(const D3DXMATRIX* pmtxworld)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//ワールド座標変換行列の作成
	D3DXMATRIX  mtxS, mtxR,mtxR2, mtxT;
	
	//ライトをセット
	Light_Set();


	//アンビエントライトの設定
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(255, 255, 255, 255));
	
	//アンビエントマテリアルの設定
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);


	//デバイスにワールド変換行列を設定 
	pDevice->SetTransform(D3DTS_WORLD, pmtxworld);
	

	//デバイスのFVF設定

	pDevice->SetFVF(FVF_VERTEX3D);


	//デバイスにテクスチャの設定をする
	pDevice->SetTexture(0, Texture_GetTexture(g_TextureID));


	//ポリゴンを描画する
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &g_CubeVertexs, sizeof(Vertex3D));

	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->SetStreamSource(0, g_pVertexBuffer,0,sizeof(Vertex3D));
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}

