#define _CRT_SECURE_NO_WARNINGS

/*===========================================================

　　　　　　　　２D画像の描画

===========================================================*/


#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "TextureManager.h"
#include "Mydirect3d.h"

typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 Textcoord;
}Vertex2D;

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//グローバル変数

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL; //頂点バッファーインターフェイス
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL; //インデックスバッファーインターフェイス
static D3DCOLOR g_Color = 0xffffffff;//ポリゴンカラー


void Sprite_Init()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	                         //頂点バッファーのbyte数 , 書くだけ , FVF , おまかせ復旧, 取得したインターフェースアドレスを記録するためのポインターアドレス
	pDevice->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED , &g_pVertexBuffer, NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

}

void Sprite_Draw(int textureID, float dx, float dy)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}


	//デバイスのFVF設定

	pDevice->SetFVF(FVF_VERTEX2D);


	//デバイスにテクスチャの設定をする
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//テクスチャのサイズ取得
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	Vertex2D testhaikei[] = {
		//頂点データを用意する
		//ポリゴンは表裏があります 右回りしないと出てこない 手順が重要
		//左上が 0,0


		//                                                                                     (xのデータ,yのデータ)(1.0fは一個のテクスチャ分)
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(0.0f, 0.0f)},
		{D3DXVECTOR4(dx + w - 0.5f   ,dy + 0.0f - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(1.0f, 0.0f)},
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy +    h - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(0.0f, 1.0f)},
		{D3DXVECTOR4(dx + h - 0.5f   ,dy +    h - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(1.0f, 1.0f)},

		//     WRAPの場合    0.5左上にずらして、枠線を消す
	};
	//ポリゴンを描く(簡易版)
	//引数: 1.形(点か線か面か) 2.図形の数 3.頂点データの先頭アドレス 4.大きさ

	//頂点ブロックの書き込み

	//インデックスバッファのロックを書き込み
	WORD* pI; //LPWORDも OK
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, 0);
	pI[0] = 0;
	pI[1] = 1;
	pI[2] = 3;
	pI[3] = 0;
	pI[4] = 3;
	pI[5] = 2;
	g_pIndexBuffer->Unlock();


	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	pDevice->SetIndices(g_pIndexBuffer);

	
	
	//デバイスに頂点バッファを設定
	//インデックスデータ
	//WORD indexも同じ
	//WORD index[] = {0,1,3,0,3,2};

	//デバイスにインデックスバッファを設定

	//頂点バッファとインデックスバッファを利用したプリミティブ描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0 , 0, 4 , 0, 2);





}

void Sprite_Draw(int textureID, float dx, float dy, int tcx, int tcy, int tcw, int tch)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}


	//デバイスのFVF設定

	pDevice->SetFVF(FVF_VERTEX2D);


	//デバイスにテクスチャの設定をする
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//テクスチャのサイズ取得
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;



	
	Vertex2D testhaikei[] = {
		//頂点データを用意する
		//ポリゴンは表裏があります 右回りしないと出てこない 手順が重要
		//左上が 0,0


		//                                                                                     (xのデータ,yのデータ)(1.0fは一個のテクスチャ分)
		{D3DXVECTOR4(dx - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f),       g_Color,D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + tcw - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx - 0.5f,dy + tch - 0.5f , 1.0f , 1.0f),       g_Color,D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + tcw - 0.5f,dy + tch - 0.5f , 1.0f , 1.0f), g_Color,D3DXVECTOR2(u1, v1)},

		//     WRAPの場合    0.5左上にずらして、枠線を消す
	};
	
	Vertex2D* pV;
	//頂点バッファーのロックとデータの書き込み
	//CPUをロックする        0は全部をロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, testhaikei, sizeof(testhaikei));
	g_pVertexBuffer->Unlock();


	//頂点バッファーの指定
	       //SetStreamSourceは重要
	pDevice->SetStreamSource(0, g_pVertexBuffer , 0 , sizeof(Vertex2D));

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//MAGFILTER : 拡大したときどのフィルターを使う
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//MINFILTER : 縮小したときどのフィルターを使う
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); //MIPFILTER : 

	//アルファブレンドの設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//半透明描画色＝今から描画するＲＧＢ * 今から描画するα + 画面ＲＧＢ * (1 - 今から描画するα )
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	

	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//1. LINEAR 線 2.ANISOTROPIC 異方性(重たい)
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);




	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
	//D3DPT_POINTLIST : 点
	//D3DPT_LINELIST : 線
	//D3DPT_LINESTRIP : 繋がる線
	//D3DPT_TRIANGLELIST : 面
	//D3DPT_TRIANGLESTRIP : 


}


void Sprite_Draw(int textureID, float dx, float dy,float dw,float dh, int tcx ,int tcy , int tcw ,int tch , int alpha)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}

	
	//デバイスのFVF設定

	pDevice->SetFVF(FVF_VERTEX2D);


	//デバイスにテクスチャの設定をする
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//テクスチャのサイズ取得
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;




	Vertex2D testhaikei[] = {
		//頂点データを用意する
		//ポリゴンは表裏があります 右回りしないと出てこない 手順が重要
		//左上が 0,0


		//                                                                                     (xのデータ,yのデータ)(1.0fは一個のテクスチャ分)
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f),D3DCOLOR_RGBA(255,255,225,alpha),D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + dw - 0.5f ,dy + 0.0f - 0.5f, 1.0f , 1.0f), D3DCOLOR_RGBA(255,255,225,alpha),D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + dh - 0.5f , 1.0f , 1.0f), D3DCOLOR_RGBA(255,255,225,alpha),D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + dw - 0.5f ,dy + dh - 0.5f , 1.0f , 1.0f),  D3DCOLOR_RGBA(255,255,225,alpha),D3DXVECTOR2(u1, v1)},

		//     WRAPの場合    0.5左上にずらして、枠線を消す
	};
		
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//MAGFILTER : 拡大したときどのフィルターを使う
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//MINFILTER : 縮小したときどのフィルターを使う
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); //MIPFILTER : 

	//アルファブレンドの設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//半透明描画色＝今から描画するＲＧＢ * 今から描画するα + 画面ＲＧＢ * (1 - 今から描画するα )
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ポリゴンを描く(簡易版)
	//引数: 1.形(点か線か面か) 2.図形の数 3.頂点データの先頭アドレス 4.大きさ

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, testhaikei, sizeof(Vertex2D));

	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//1. LINEAR 線 2.ANISOTROPIC 異方性(重たい)
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);




	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
	//D3DPT_POINTLIST : 点
	//D3DPT_LINELIST : 線
	//D3DPT_LINESTRIP : 繋がる線
	//D3DPT_TRIANGLELIST : 面
	//D3DPT_TRIANGLESTRIP : 


}

void Sprite_Draw(int textureID, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}


	//デバイスのFVF設定

	pDevice->SetFVF(FVF_VERTEX2D);


	//デバイスにテクスチャの設定をする
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//テクスチャのサイズ取得
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;




	Vertex2D testhaikei[] = {
		//頂点データを用意する
		//ポリゴンは表裏があります 右回りしないと出てこない 手順が重要
		//左上が 0,0


		//                                                                                     (xのデータ,yのデータ)(1.0fは一個のテクスチャ分)
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f),g_Color,D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + dw - 0.5f ,dy + 0.0f - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + dh - 0.5f , 1.0f , 1.0f), g_Color,D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + dw - 0.5f ,dy + dh - 0.5f , 1.0f , 1.0f),  g_Color,D3DXVECTOR2(u1, v1)},

		//     WRAPの場合    0.5左上にずらして、枠線を消す
	};

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//MAGFILTER : 拡大したときどのフィルターを使う
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//MINFILTER : 縮小したときどのフィルターを使う
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); //MIPFILTER : 

	//アルファブレンドの設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//半透明描画色＝今から描画するＲＧＢ * 今から描画するα + 画面ＲＧＢ * (1 - 今から描画するα )
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ポリゴンを描く(簡易版)
	//引数: 1.形(点か線か面か) 2.図形の数 3.頂点データの先頭アドレス 4.大きさ
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, testhaikei, sizeof(Vertex2D));
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//1. LINEAR 線 2.ANISOTROPIC 異方性(重たい)
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);




	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
	//D3DPT_POINTLIST : 点
	//D3DPT_LINELIST : 線
	//D3DPT_LINESTRIP : 繋がる線
	//D3DPT_TRIANGLELIST : 面
	//D3DPT_TRIANGLESTRIP : 


}


//                                                                                                          cx 回転拡大の中心座標x
//                                                                                                          cy 回転拡大の中心座標y
void Sprite_Draw(int textureID, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, float cx, float cy , float angle)
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}

	//デバイスのFVF設定

	pDevice->SetFVF(FVF_VERTEX2D);


	//デバイスにテクスチャの設定をする
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//テクスチャのサイズ取得
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;




	Vertex2D testhaikei[] = {
		//頂点データを用意する
		//ポリゴンは表裏があります 右回りしないと出てこない 手順が重要
		//左上が 0,0


		//                                                                                     (xのデータ,yのデータ)(1.0fは一個のテクスチャ分)
		{D3DXVECTOR4(0.0f - 0.5f ,  0.0f  - 0.5f, 1.0f , 1.0f),  g_Color,D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dw   -  0.5f,  0.0f  - 0.5f, 1.0f , 1.0f),  g_Color,D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(0.0f - 0.5f ,  dh    - 0.5f , 1.0f , 1.0f), g_Color,D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dw   - 0.5f ,  dh    - 0.5f , 1.0f , 1.0f), g_Color,D3DXVECTOR2(u1, v1)},

		//     WRAPの場合    0.5左上にずらして、枠線を消す
	};


	//平行移動行列
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -cx, -cy, 0.0f);

	D3DXMATRIX mtxTranslationI;
	D3DXMatrixTranslation(&mtxTranslationI, cx + dx, cy + dy, 0.0f);

	//回転行列を作成する
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	//拡大行列
	D3DXMATRIX mtxscale;        //1.0は1倍の意味
	D3DXMatrixScaling(&mtxscale, 1.0, 1.0, 1.0);
	//行列の合成
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxscale * mtxRotation * mtxTranslationI;


	//座標変換
	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&testhaikei[i].Position, &testhaikei[i].Position, &mtxWorld);
	}





	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//MAGFILTER : 拡大したときどのフィルターを使う
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//MINFILTER : 縮小したときどのフィルターを使う
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); //MIPFILTER : 

	//アルファブレンドの設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//半透明描画色＝今から描画するＲＧＢ * 今から描画するα + 画面ＲＧＢ * (1 - 今から描画するα )
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ポリゴンを描く(簡易版)
	//引数: 1.形(点か線か面か) 2.図形の数 3.頂点データの先頭アドレス 4.大きさ

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, testhaikei, sizeof(Vertex2D));

	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//1. LINEAR 線 2.ANISOTROPIC 異方性(重たい)
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);



	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
	//D3DPT_POINTLIST : 点
	//D3DPT_LINELIST : 線
	//D3DPT_LINESTRIP : 繋がる線
	//D3DPT_TRIANGLELIST : 面
	//D3DPT_TRIANGLESTRIP : 











}


void Sprite_SetColor(D3DCOLOR color)
{
	g_Color = color;
}

void Sprite_Final()
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

}