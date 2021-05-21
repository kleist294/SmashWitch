/*============================================================

　　　　　　　　　　　ビックリマークの制御（エネミー）

============================================================*/


#include "TextureManager.h"
#include <d3dx9.h>
#include "Collision.h"
#include "Sound.h"
#include "Billboard.h"
#include "GameJudgement.h"
#include "GameEnemyManager.h"

#define MAX_BIKURI 100

typedef struct {
	D3DXVECTOR3 Pos = { 0.0f, 0.0f,0.0f };
	bool IsEnable;
	int AnimeX;
	int AnimeY;
	int Frame;
	float Size;
	D3DXCOLOR Color;
}Bikuri;



static Bikuri g_Bikuri[MAX_BIKURI];

static unsigned int g_TextureBikuriID = INVALID_TEXTURE_ID;

static int AnimeTest = 0;

/*============================================================
　　　　　　　ビックリマーク制御の初期化
============================================================*/
void GameBikuri_Init()
{
	g_TextureBikuriID = Texture_SetTextureLoadFile("asset\\texture\\bikuri.png");
	for (int i = 0; i < MAX_BIKURI; i++) {
		g_Bikuri[i].Pos = { 0.0f, 0.0f,0.0f };
		g_Bikuri[i].IsEnable = false;
		g_Bikuri[i].AnimeX = 0;
		g_Bikuri[i].AnimeY = 0;
		g_Bikuri[i].Frame = 0;
		g_Bikuri[i].Size = 0.0f;
		g_Bikuri[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

}
/*============================================================
　　　　　　　ビックリマークのアニメーション
============================================================*/
void GameBikuri_Update()
{
	for (int i = 0; i < MAX_BIKURI; i++) {
		if (g_Bikuri[i].IsEnable == true)
		{

			if (g_Bikuri[i].Frame >= 40.0f)
			{
				g_Bikuri[i].Color.a -= 0.2f;
				if (g_Bikuri[i].Color.a <= 0.0f)
				{
					g_Bikuri[i].Frame = 0.0f;
					g_Bikuri[i].Color.a = 0.0f;
					g_Bikuri[i].IsEnable = false;
					EnemyIsBikuri(GetLockOnEnemyNum());
				}
			}

			g_Bikuri[i].Size += 0.05f;

			if (g_Bikuri[i].Size >= 0.25f)
			{
				g_Bikuri[i].Size = 0.25f;
			}
			g_Bikuri[i].Frame++;
		}
	}

}
/*============================================================
　　　　　　　ビックリマークの描画
============================================================*/
void GameBikuri_Draw(float x,float y,float z)
{
	for (int i = 0; i < MAX_BIKURI; i++) {
		if (g_Bikuri[i].IsEnable == true)
		{
			//有効だったら描画
			Billboard_SetColor(g_Bikuri[i].Color);
			Billboard_DrawAnimation(g_TextureBikuriID, x,y, z, 0.5f, 0.25f + g_Bikuri[i].Size, 0, 0, 500, 500);
			Billboard_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}

}
void GameBikuri_Final(void)
{

}

/*============================================================
　　　　　　　ビックリマークの生成
============================================================*/
void GameBikuri_Spawn()
{

	for (int i = 0; i < MAX_BIKURI; i++) {
		if (g_Bikuri[i].IsEnable)
			continue;
		
		g_Bikuri[i].IsEnable = true;
		g_Bikuri[i].Size = 0.0f;
		g_Bikuri[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}
}

