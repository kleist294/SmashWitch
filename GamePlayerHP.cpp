
/*============================================================

　　　　　　　プレイヤーのライフの描画

============================================================*/




#include "TextureManager.h"
#include <d3dx9.h>
#include "Fade.h"
#include "sound.h"
#include "Billboard.h"
#include "Camera.h"
#include "GamePlayerManager.h"
#include "Sprite.h"

#define HEART_SIZE_X 120
#define HEART_SIZE_Y 120
#define MAX_LIFE 3

typedef struct Life_tag
{
	D3DXVECTOR2 Pos;
	int HeartAnimeX = 0;
	int HeartAnimeY = 0;

	bool Broke;
	bool Enable;
}Life;

static unsigned int g_TextureIDLife = INVALID_TEXTURE_ID;
static int g_HeartFrame = 0;
static Life g_Heart[MAX_LIFE];

/*============================================================
　　　　　　　　　ライフの初期化
============================================================*/
void GamePlayerHP_Init()
{
	g_TextureIDLife = Texture_SetTextureLoadFile("asset\\texture\\heart.png");

	g_HeartFrame = 0;

	for (int i = 0; i < MAX_LIFE; i++)
	{
		g_Heart[i].Enable = true;
		g_Heart[i].Broke = false;
		g_Heart[i].HeartAnimeX = 0;
		g_Heart[i].HeartAnimeY = 0;
		g_Heart[i].Pos = g_Heart[i].Pos = D3DXVECTOR2(50.0f + i * HEART_SIZE_X, 40.0f);
	}


}

/*============================================================
　　　　　　　　　ライフのアップデート
============================================================*/
void GamePlayerHP_Update()
{

	if (g_HeartFrame >= 5)
	{
		g_HeartFrame = 0;

		for (int i = 0; i < MAX_LIFE; i++)
		{
			if (g_Heart[i].Enable == true)
			{
				g_Heart[i].HeartAnimeX += HEART_SIZE_X;

				if (g_Heart[i].HeartAnimeY >= HEART_SIZE_Y && g_Heart[i].HeartAnimeX >= HEART_SIZE_X * 5)
				{
					g_Heart[i].HeartAnimeY = HEART_SIZE_Y;
					g_Heart[i].HeartAnimeX = HEART_SIZE_X * 5;
				}
				if (g_Heart[i].HeartAnimeY == 0 && g_Heart[i].HeartAnimeX >= HEART_SIZE_X * 5)
				{
					//g_ExplosionEnable = false;
					g_Heart[i].HeartAnimeX = 0.0f;
					g_Heart[i].HeartAnimeY = HEART_SIZE_Y;
				}
			}

			if (g_Heart[i].Enable == false && g_Heart[i].Broke == true)
			{

				g_Heart[i].HeartAnimeX += HEART_SIZE_X;

				if (g_Heart[i].HeartAnimeY >= HEART_SIZE_Y * 3 && g_Heart[i].HeartAnimeX >= HEART_SIZE_X * 5)
				{
					g_Heart[i].Broke = false;
				}
				if (g_Heart[i].HeartAnimeY == HEART_SIZE_Y * 2 && g_Heart[i].HeartAnimeX >= HEART_SIZE_X * 5)
				{
					g_Heart[i].HeartAnimeX = 0.0f;
					g_Heart[i].HeartAnimeY = HEART_SIZE_Y * 3;
				}
				if (g_Heart[i].HeartAnimeY == HEART_SIZE_Y && g_Heart[i].HeartAnimeX >= HEART_SIZE_X * 5)
				{
					g_Heart[i].HeartAnimeX = 0.0f;
					g_Heart[i].HeartAnimeY = HEART_SIZE_Y * 2;
				}

			}


		}

	}


	


	g_HeartFrame++;
}
/*============================================================
　　　　　　　　　ライフの描画
============================================================*/
void GamePlayerHP_Draw()
{
	if (GetPlayerHP() >= 3)
	{
		Sprite_Draw(g_TextureIDLife, g_Heart[0].Pos.x, g_Heart[0].Pos.y, 100.0f, 100.0f, g_Heart[0].HeartAnimeX, g_Heart[0].HeartAnimeY, 120, 120);

	}
	if (GetPlayerHP() >= 2)
	{
		if (g_Heart[0].Broke == true)
		{
			Sprite_Draw(g_TextureIDLife, g_Heart[0].Pos.x, g_Heart[0].Pos.y, 100.0f, 100.0f, g_Heart[0].HeartAnimeX, g_Heart[0].HeartAnimeY, 120, 120);

		}
		Sprite_Draw(g_TextureIDLife, g_Heart[1].Pos.x, g_Heart[1].Pos.y, 100.0f, 100.0f, g_Heart[1].HeartAnimeX, g_Heart[1].HeartAnimeY, 120, 120);

	}
	if (GetPlayerHP() >= 1)
	{
		if (g_Heart[1].Broke == true)
		{
			Sprite_Draw(g_TextureIDLife, g_Heart[1].Pos.x, g_Heart[1].Pos.y, 100.0f, 100.0f, g_Heart[1].HeartAnimeX, g_Heart[1].HeartAnimeY, 120, 120);

		}
		Sprite_Draw(g_TextureIDLife, g_Heart[2].Pos.x, g_Heart[2].Pos.y, 100.0f, 100.0f, g_Heart[2].HeartAnimeX, g_Heart[2].HeartAnimeY, 120, 120);

	}
	if (g_Heart[2].Broke == true)
	{
		Sprite_Draw(g_TextureIDLife, g_Heart[2].Pos.x, g_Heart[2].Pos.y, 100.0f, 100.0f, g_Heart[2].HeartAnimeX, g_Heart[2].HeartAnimeY, 120, 120);

	}
}
void GamePlayerHP_Final()
{

}

/*============================================================
　　　　　　　　　ライフが減る
============================================================*/
void GamePlayerHP_HeartBroke()
{
	
	if (GetPlayerHP() >= 0)
	{
		g_Heart[2 - GetPlayerHP()].Enable = false;
		g_Heart[2 - GetPlayerHP()].Broke = true;
		
	}

}