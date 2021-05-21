
/*============================================================

　　　ヒットエフェクト

============================================================*/

#include "TextureManager.h"
#include <d3dx9.h>
#include "Collision.h"
#include "Sound.h"
#include "Billboard.h"

#define MEGUMIN_SIZE_X 120
#define MEGUMIN_SIZE_Y 120
#define MAX_EXPLOSION 100

typedef struct {
	D3DXVECTOR3 Pos = { 0.0f, 0.0f,0.0f };
	bool IsEnable;
	int AnimeX;
	int AnimeY;
	int Frame;
	float Size;

}Explosion;



static Explosion g_Explosion[MAX_EXPLOSION];

static unsigned int g_TextureExplosionID = INVALID_TEXTURE_ID;

static int AnimeTest = 0;

/*============================================================
　　　ヒットエフェクトの初期化
============================================================*/
void GameHitEffect_Init()
{
	g_TextureExplosionID = Texture_SetTextureLoadFile("asset\\texture\\megumin.png");
	for (int i = 0; i < MAX_EXPLOSION; i++) {
		g_Explosion[i].Pos = { 0.0f, 0.0f,0.0f };
		g_Explosion[i].IsEnable = false;
		g_Explosion[i].AnimeX = 0;
		g_Explosion[i].AnimeY = 0;
		g_Explosion[i].Frame = 0;
	}

}

/*============================================================
　　　ヒットエフェクトの演出
============================================================*/
void GameHitEffect_Update()
{
	for (int i = 0; i < MAX_EXPLOSION; i++) {
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
　　　ヒットエフェクトの描画
============================================================*/
void GameHitEffect_Draw()
{
	for (int i = 0; i < MAX_EXPLOSION; i++) {
		if (g_Explosion[i].IsEnable == true)
		{
			//有効だったら描画
			Billboard_DrawAnimation(g_TextureExplosionID, g_Explosion[i].Pos.x, g_Explosion[i].Pos.y, g_Explosion[i].Pos.z,  1.0f, 1.0f, g_Explosion[i].AnimeX, g_Explosion[i].AnimeY, MEGUMIN_SIZE_X, MEGUMIN_SIZE_Y);
			
		}
	}

}
void GameHitEffect_Final(void)
{

}

/*============================================================
　　　ヒットエフェクトの生成
============================================================*/
void GameHitEffect_Spawn(float x, float y,float z)
{

	for (int i = 0; i < MAX_EXPLOSION; i++) {
		if (g_Explosion[i].IsEnable)
			continue;
		g_Explosion[i].IsEnable = true;
		g_Explosion[i].Pos = {x,y,z};
		g_Explosion[i].AnimeX = 0;
		g_Explosion[i].AnimeY = 0;
		g_Explosion[i].Size = 0.2f;
		break;
	}
}

