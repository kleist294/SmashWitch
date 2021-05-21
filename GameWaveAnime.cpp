
/*============================================================

　　　　　　　　　　　WAVEのアニメーション（星）

============================================================*/

#include "TextureManager.h"
#include <d3dx9.h>
#include "collision.h"
#include "sound.h"
#include "Billboard.h"
#include "Camera.h"

#define MEGUMIN_SIZE_X 120
#define MEGUMIN_SIZE_Y 120
#define MAX_EXPLOSION 100


static D3DXVECTOR3 Pos = { 0.0f, 0.0f,0.0f };
static bool  g_IsEnable;
static int   g_AnimeX;
static int   g_AnimeY;
static int   g_Frame;


static unsigned int g_TextureExplosionID = INVALID_TEXTURE_ID;


static float g_EffectRightOffSet = 0.0f;

/*============================================================
　　　　　　　　星の初期化
============================================================*/
void GameWaveAnime_Init()
{
	g_TextureExplosionID = Texture_SetTextureLoadFile("asset\\texture\\meguminp.png");	
	Pos = { 0.0f, 0.0f,0.0f };
	g_IsEnable = false;
	g_AnimeX = 0;
	g_AnimeY = 0;
	g_Frame = 0;	
	g_EffectRightOffSet = 0.0f;
}

/*============================================================
　　　　　　　　星の演出
============================================================*/
void GameWaveAnime_Update()
{
		if (g_IsEnable == true)
		{

			if (g_Frame >= 5.0f)
			{
				g_Frame = 0.0f;
				g_AnimeX += MEGUMIN_SIZE_X;

				if (g_AnimeY >= MEGUMIN_SIZE_Y * 2 && g_AnimeX >= MEGUMIN_SIZE_X * 5)
				{
					g_IsEnable = false;
					g_EffectRightOffSet = 0.0f;

				}
				if (g_AnimeY >= MEGUMIN_SIZE_Y && g_AnimeX >= MEGUMIN_SIZE_X * 5)
				{
					g_AnimeX = 0.0f;
					g_AnimeY = MEGUMIN_SIZE_Y * 2;


				}
				if (g_AnimeX >= MEGUMIN_SIZE_X * 5)
				{
					//g_ExplosionEnable = false;
					g_AnimeX = 0.0f;
					g_AnimeY = MEGUMIN_SIZE_Y;

				}


			}
			g_Frame++;
			g_EffectRightOffSet += 0.1f;
		}

	

}

/*============================================================
　　　　　　　　星の描画
============================================================*/
void GameWaveAnime_Draw()
{
		if (g_IsEnable == true)
		{
			//有効だったら描画
			Billboard_DrawAnimationNonZBuffer(g_TextureExplosionID,
				Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * -2.0f + Camera_GetUpVector()->x * 3.0f + Camera_GetRightVector()->x * g_EffectRightOffSet,
				Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * -2.0f + Camera_GetUpVector()->y * 3.0f + Camera_GetRightVector()->y * g_EffectRightOffSet,
				Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * -2.0f + Camera_GetUpVector()->z * 3.0f + Camera_GetRightVector()->z * g_EffectRightOffSet,
				3.0f, 3.0f, g_AnimeX, g_AnimeY, MEGUMIN_SIZE_X, MEGUMIN_SIZE_Y);

		}
	

}

void GameWaveAnime_Final(void)
{

}

/*============================================================
　　　　　　　　星の生成
============================================================*/
void GameWaveAnimeSpawn()
{
		g_IsEnable = true;
		g_AnimeX = 0;
		g_AnimeY = 0;	
}

