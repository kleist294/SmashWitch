/*============================================================

　　　　　　　　タイトルのアニメーション（流れ星）

============================================================*/


#include "Sprite.h"
#include "TextureManager.h"
#include <d3dx9.h>
#include "Collision.h"


#define ENEMY_BULLET_MAX 2000

#define ENEMY_BULLET_SIZEX 75.0f
#define ENEMY_BULLET_SIZEY 75.0f

#define ENEMY_RYUSEI_SIZEX 192
#define ENEMY_RYUSEI_SIZEY 192

typedef struct Ryusei_tag
{
	D3DXVECTOR2 Pos;
	D3DXVECTOR2 Direction;
	float Speed;
	int Color;
	int RyuseiAnimeX;
	int RyuseiAnimeY;
	int Frame;

	bool Enable;
}Ryusei;

static unsigned int g_TextureIDRyusei1 = INVALID_TEXTURE_ID;
static unsigned int g_TextureIDRyusei2 = INVALID_TEXTURE_ID;
static unsigned int g_TextureIDRyusei3 = INVALID_TEXTURE_ID;
static unsigned int g_TextureIDRyusei4 = INVALID_TEXTURE_ID;
static unsigned int g_TextureIDRyusei5 = INVALID_TEXTURE_ID;


static Ryusei g_Ryusei[ENEMY_BULLET_MAX];

/*============================================================
　　　　　　　　流れ星の初期化
============================================================*/

void Comet_Init()
{
	g_TextureIDRyusei1 = Texture_SetTextureLoadFile("asset\\texture\\ryusei1.png");
	g_TextureIDRyusei2 = Texture_SetTextureLoadFile("asset\\texture\\ryusei2.png");
	g_TextureIDRyusei3 = Texture_SetTextureLoadFile("asset\\texture\\ryusei3.png");
	g_TextureIDRyusei4 = Texture_SetTextureLoadFile("asset\\texture\\ryusei4.png");
	g_TextureIDRyusei5 = Texture_SetTextureLoadFile("asset\\texture\\ryusei5.png");

	//g_BulletEnable = false;
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		g_Ryusei[i].Enable = false;
		g_Ryusei[i].Pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Ryusei[i].Speed = 1.0f;
		g_Ryusei[i].Color = 0;
		g_Ryusei[i].RyuseiAnimeX = 0;
		g_Ryusei[i].RyuseiAnimeY = 0;
	}
	

}

/*============================================================
　　　　　　　　流れ星のアップデート
============================================================*/
void Comet_Update()
{
	

	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (g_Ryusei[i].Pos.x < -100.0f || g_Ryusei[i].Pos.y > 820.0f)
		{
			g_Ryusei[i].Enable = false;
			g_Ryusei[i].Direction = D3DXVECTOR2(0.0f, 0.0f);
			g_Ryusei[i].Speed = 1.0f;
		}		
			if (!g_Ryusei[i].Enable)
				continue;
			D3DXVec2Normalize(&g_Ryusei[i].Direction, &g_Ryusei[i].Direction);
			g_Ryusei[i].Speed *= 1.01f;
			g_Ryusei[i].Pos += g_Ryusei[i].Direction * g_Ryusei[i].Speed;

			if (g_Ryusei[i].Frame >= 3) {

				g_Ryusei[i].Frame = 0;
				g_Ryusei[i].RyuseiAnimeX += ENEMY_RYUSEI_SIZEX;

				if (g_Ryusei[i].RyuseiAnimeY >= ENEMY_RYUSEI_SIZEY * 3 && g_Ryusei[i].RyuseiAnimeX >= ENEMY_RYUSEI_SIZEX * 5)
				{
					g_Ryusei[i].RyuseiAnimeX = 0.0f;
					g_Ryusei[i].RyuseiAnimeY = ENEMY_RYUSEI_SIZEY * 0;
				}
				if (g_Ryusei[i].RyuseiAnimeY >= ENEMY_RYUSEI_SIZEY * 2 && g_Ryusei[i].RyuseiAnimeX >= ENEMY_RYUSEI_SIZEX * 5)
				{
					g_Ryusei[i].RyuseiAnimeX = 0.0f;
					g_Ryusei[i].RyuseiAnimeY = ENEMY_RYUSEI_SIZEY * 3;
				}
				if (g_Ryusei[i].RyuseiAnimeY >= ENEMY_RYUSEI_SIZEY && g_Ryusei[i].RyuseiAnimeX >= ENEMY_RYUSEI_SIZEX * 5)
				{
					g_Ryusei[i].RyuseiAnimeX = 0.0f;
					g_Ryusei[i].RyuseiAnimeY = ENEMY_RYUSEI_SIZEY * 2;


				}
				if (g_Ryusei[i].RyuseiAnimeX >= ENEMY_RYUSEI_SIZEX * 5)
				{
					//g_ExplosionEnable = false;
					g_Ryusei[i].RyuseiAnimeX = 0.0f;
					g_Ryusei[i].RyuseiAnimeY = ENEMY_RYUSEI_SIZEY;

				}
			}
		g_Ryusei[i].Frame++;
	}



	
}


/*============================================================
　　　　　　　　流れ星の描画
============================================================*/
void Comet_Draw()
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		//弾が有効が調べる

		if (g_Ryusei[i].Enable == true)
		{
			//有効だったら描画
			if (g_Ryusei[i].Color == 0)
			{
				Sprite_Draw(g_TextureIDRyusei1, g_Ryusei[i].Pos.x, g_Ryusei[i].Pos.y, 100.0f, 100.0f, g_Ryusei[i].RyuseiAnimeX, g_Ryusei[i].RyuseiAnimeY, ENEMY_RYUSEI_SIZEX, ENEMY_RYUSEI_SIZEY, 255);
			}
			if (g_Ryusei[i].Color == 1)
			{
				Sprite_Draw(g_TextureIDRyusei2, g_Ryusei[i].Pos.x, g_Ryusei[i].Pos.y, 100.0f, 100.0f, g_Ryusei[i].RyuseiAnimeX, g_Ryusei[i].RyuseiAnimeY, ENEMY_RYUSEI_SIZEX, ENEMY_RYUSEI_SIZEY, 255);
			}
			if (g_Ryusei[i].Color == 2)
			{
				Sprite_Draw(g_TextureIDRyusei3, g_Ryusei[i].Pos.x, g_Ryusei[i].Pos.y, 100.0f, 100.0f, g_Ryusei[i].RyuseiAnimeX, g_Ryusei[i].RyuseiAnimeY, ENEMY_RYUSEI_SIZEX, ENEMY_RYUSEI_SIZEY, 255);
			}
			if (g_Ryusei[i].Color == 3)
			{
				Sprite_Draw(g_TextureIDRyusei4, g_Ryusei[i].Pos.x, g_Ryusei[i].Pos.y, 100.0f, 100.0f, g_Ryusei[i].RyuseiAnimeX, g_Ryusei[i].RyuseiAnimeY, ENEMY_RYUSEI_SIZEX, ENEMY_RYUSEI_SIZEY, 255);
			}
			if (g_Ryusei[i].Color == 4)
			{
				Sprite_Draw(g_TextureIDRyusei5, g_Ryusei[i].Pos.x, g_Ryusei[i].Pos.y, 100.0f, 100.0f, g_Ryusei[i].RyuseiAnimeX, g_Ryusei[i].RyuseiAnimeY, ENEMY_RYUSEI_SIZEX, ENEMY_RYUSEI_SIZEY, 255);
			}
		}

	}
}
void Comet_Final(void)
{

}

/*============================================================
　　　　　　　　流れ星の生成
============================================================*/
void Comet_Spawn(float x, float y)
{
	for (int i = 0; i < ENEMY_BULLET_MAX; i++)
	{
		if (g_Ryusei[i].Enable)
			continue;
		g_Ryusei[i].Enable = true;
		g_Ryusei[i].Pos = D3DXVECTOR2(x, y);
		g_Ryusei[i].Direction = D3DXVECTOR2(-1.8f, 1.0f);
		g_Ryusei[i].Color = rand() % 5;
		
		break; // <------------重要!!!!!!!!!!!!
	}



}