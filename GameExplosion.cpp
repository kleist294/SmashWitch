

/*============================================================

　　　　爆発の２Dアニメーション

============================================================*/

#include "Sprite.h"
#include "TextureManager.h"
#include <d3dx9.h>
#include "Collision.h"
#include "Sound.h"

#define MEGUMIN_SIZE_X 120
#define MEGUMIN_SIZE_Y 120
#define MAX_EXPLODE 100

typedef struct {
	D3DXVECTOR2 Pos = {0.0f, 0.0f};
	bool IsEnable;
	int AnimeX;
	int AnimeY;
	int Frame;
	float Size;

}Explosion;



static Explosion g_Explosion[MAX_EXPLODE];

static unsigned int g_TextureExplosionID = INVALID_TEXTURE_ID;


/*============================================================
　　　　アニメーションの初期化
============================================================*/
void GameExplosion_Init()
{
	g_TextureExplosionID = Texture_SetTextureLoadFile("asset\\texture\\megumin.png");

	for (int i = 0; i < MAX_EXPLODE; i++) {
		g_Explosion[i].Pos = { 0.0f, 0.0f};
		g_Explosion[i].IsEnable = false;
		g_Explosion[i].AnimeX = 0;
		g_Explosion[i].AnimeY = 0;
		g_Explosion[i].Frame = 0;
	}
}

/*============================================================
　　　　アニメーションの演出
============================================================*/
void GameExplosion_Update()
{
	

	for (int i = 0; i < MAX_EXPLODE; i++) {
		if (g_Explosion[i].IsEnable == true)
		{

			if (g_Explosion[i].Frame >= 5.0f)
			{
				g_Explosion[i].Frame = 0.0f;
				g_Explosion[i].AnimeX += MEGUMIN_SIZE_X;

				if (g_Explosion[i].AnimeY >= MEGUMIN_SIZE_Y * 2 && g_Explosion[i].AnimeX >= MEGUMIN_SIZE_X * 5)
				{
					g_Explosion[i].IsEnable = false;
				}
				if (g_Explosion[i].AnimeY >= MEGUMIN_SIZE_Y && g_Explosion[i].AnimeX >= MEGUMIN_SIZE_X * 5)
				{
					g_Explosion[i].AnimeX = 0.0f;
					g_Explosion[i].AnimeY = MEGUMIN_SIZE_Y * 2;


				}
				if (g_Explosion[i].AnimeX >= MEGUMIN_SIZE_X * 5)
				{
					//g_ExplosionEnable = false;
					g_Explosion[i].AnimeX = 0.0f;
					g_Explosion[i].AnimeY = MEGUMIN_SIZE_Y;

				}


			}



			g_Explosion[i].Frame++;
		}
	}

}

/*============================================================
　　　　アニメーションの描画
============================================================*/
void GameExplosion_Draw()
{
	for (int i = 0; i < MAX_EXPLODE; i++) {
		if (g_Explosion[i].IsEnable == true)
		{
			//有効だったら描画
			Sprite_Draw(g_TextureExplosionID, g_Explosion[i].Pos.x, g_Explosion[i].Pos.y, 80, 80, g_Explosion[i].AnimeX, g_Explosion[i].AnimeY, MEGUMIN_SIZE_X, MEGUMIN_SIZE_Y, 255);

		}
	}

}
void GameExplosion_Final(void)
{

}

/*============================================================
　　　　アニメーションの生成
============================================================*/
void GameExplosion_Spawn(float x, float y)
{

	for (int i = 0; i < MAX_EXPLODE; i++) {
		if (g_Explosion[i].IsEnable)
			continue;
		g_Explosion[i].IsEnable = true;
		g_Explosion[i].Pos = {x,y};
		g_Explosion[i].AnimeX = 0;
		g_Explosion[i].AnimeY = 0;
		break;
	}
}

