#define _CRT_SECURE_NO_WARNINGS

/*============================================================　　

　　　　　　テクスチャの制御

============================================================*/


#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include "TextureManager.h"
#include "Mydirect3d.h"
#include "DebugPrintf.h"

#define TEXTURE_MAX 1024 //テクスチャ管理最大数


//テクスチャ管理テーブル構造体
typedef struct Texture_Tag
{

	LPDIRECT3DTEXTURE9 pTexture;
	unsigned long Width;
	unsigned long Height;
	char Filename[TEXTURE_FILENAME_MAX];

}Texture;

//テクスチャ管理テーブル
static Texture g_Textures[TEXTURE_MAX];

/*============================================================　　
　　　　　　テクスチャ管理の初期化
============================================================*/
void TextureInit()
{

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//動的メモリー使ってもいい
		g_Textures[i].pTexture = NULL;
		g_Textures[i].Width = 0;
		g_Textures[i].Height = 0;
		g_Textures[i].Filename[0] = 0;
	}

}

/*============================================================　　
　　　　　　テクスチャを設置する関数
============================================================*/
int Texture_SetTextureLoadFile(const char* pFilename)
{
	//ファイル名検索
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//空いていたら、スキップ
		if (g_Textures[i].Filename[0] == 0)
		{
			continue;
		}

		//すでに指定のファイルが予約されているか？
		if (strcmp(pFilename, g_Textures[i].Filename) == 0)
		{

			return i;
		}

	}

	//新規予約
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//テーブルが使用中だったら、スキップ
		if (g_Textures[i].Filename[0] != 0)
		{
			continue;
		}

		strcpy(g_Textures[i].Filename, pFilename);
		return i;

	}

	return INVALID_TEXTURE_ID;

}

/*============================================================　　
　　　　　　テクスチャをロードする関数
============================================================*/
int Texture_Load()
{


	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return -1;
	}
	


	int error_count = 0;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{



		if (g_Textures[i].Filename[0] == 0) 
		{
			//空いているテーブルだからスキップ
			continue;
		}
		//アロー演算子にならないように
		if (g_Textures[i].pTexture != NULL)
		{
			//すでに読み込まれている
			continue;
		}

		//テクスチャの読み込み
		//                            FromMemoryというものがあって、読み込みを一回にします
		HRESULT hr = D3DXCreateTextureFromFile(pDevice, g_Textures[i].Filename, &g_Textures[i].pTexture);
		if (FAILED(hr))
		{
			//デバイスの取得に失敗
			DebugPrintf("読み込めなかったテクスチャファイル : [%s]\n", g_Textures[i].Filename);
			error_count++;
			return false;
		}
		else
		{
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(g_Textures[i].Filename, &info);
			g_Textures[i].Width = info.Width;
			g_Textures[i].Height = info.Height;

		}

	}

	return error_count;
}


/*============================================================　　
　　　　　　テクスチャをリリースする
============================================================*/
void Texture_Release(int textureIDs[], int count)
{

	for (int i = 0; i < count; i++)
	{
		if (g_Textures[textureIDs[i]].pTexture)
		{
			g_Textures[textureIDs[i]].pTexture->Release();
			g_Textures[textureIDs[i]].pTexture = NULL;
		}
		g_Textures[textureIDs[i]].Filename[0] = 0;
		g_Textures[textureIDs[i]].Width = 0;
		g_Textures[textureIDs[i]].Height = 0;
	}

}

/*============================================================　　
　　　　　　テクスチャを全部リリースする
============================================================*/
void Texture_AllRelease()
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Textures[i].pTexture)
		{
			g_Textures[i].pTexture->Release();
			g_Textures[i].pTexture = NULL;
		}
	g_Textures[i].Filename[0] = 0;
	g_Textures[i].Width = 0;
	g_Textures[i].Height = 0;
	}
}

/*============================================================　　
　　　　　　テクスチャの幅を取得する
============================================================*/
unsigned long Texture_GetTextureWidth(int textureID)
{
	return g_Textures[textureID].Width;
}

/*============================================================　　
　　　　　　テクスチャの高さを取得する
============================================================*/
unsigned long Texture_GetTextureHeight(int textureID)
{
	return g_Textures[textureID].Height;
}

void TextureFinal()
{

}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureID)
{
	if (textureID == INVALID_TEXTURE_ID) {
		return NULL;
	};
	return g_Textures[textureID].pTexture;
	
}
