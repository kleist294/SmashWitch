
/*============================================================

　　　　　　　　WAVEのフォント

============================================================*/

#include "TextureManager.h"
#include <d3dx9.h>
#include "collision.h"
#include "sound.h"
#include "Billboard.h"
#include "Camera.h"
#include "GameEnemyManager.h"

static D3DXCOLOR g_Alpha[7];

static int g_TextureIDWAVE = INVALID_TEXTURE_ID;
static int g_TextureID1 = INVALID_TEXTURE_ID;
static int g_TextureID2 = INVALID_TEXTURE_ID;
static int g_TextureID3 = INVALID_TEXTURE_ID;
static int g_TextureID4 = INVALID_TEXTURE_ID;
static int g_TextureID5 = INVALID_TEXTURE_ID;
static int g_TextureIDLastWave = INVALID_TEXTURE_ID;

static bool g_LastWave = false;
static bool g_TextChange = false;
static int g_NumberFrame = 0;
static int g_LastWaveFrame = 0;

/*============================================================
　　　　　　　　WAVEの初期化
============================================================*/
void GameWaveFont_Init()
{
	g_TextureIDWAVE = Texture_SetTextureLoadFile("asset\\texture\\wave.png");
	g_TextureID1 = Texture_SetTextureLoadFile("asset\\texture\\one.png");
	g_TextureID2 = Texture_SetTextureLoadFile("asset\\texture\\two.png");
	g_TextureID3 = Texture_SetTextureLoadFile("asset\\texture\\three.png");
	g_TextureID4 = Texture_SetTextureLoadFile("asset\\texture\\four.png");
	g_TextureID5 = Texture_SetTextureLoadFile("asset\\texture\\five.png");
	g_TextureIDLastWave = Texture_SetTextureLoadFile("asset\\texture\\lastwave.png");

	g_TextChange = false; 
	g_LastWave = false;
	g_NumberFrame = 0;
	for(int i = 0; i < 7; i++)
	{
		g_Alpha[i].r = 1.0f;
		g_Alpha[i].g = 1.0f;
		g_Alpha[i].b = 1.0f;
		g_Alpha[i].a = 0.0f;
	}
}

/*============================================================
　　　　　　　　WAVEのアップデート
============================================================*/
void GameWaveFont_Update()
{

	if (g_TextChange == true) 
	{
	
		int NowWave = GetEnemyWave() + 1;
		if (g_NumberFrame >= 42 && g_NumberFrame <= 180)
		{
			g_Alpha[NowWave].a += 0.1f;
			if (g_Alpha[NowWave].a >= 1.0f)
			{
				g_Alpha[NowWave].a = 1.0f;
			}
			if (GetEnemyWave() >= 1)
			{
				g_Alpha[NowWave - 1].a -= 0.1f;
				if (g_Alpha[NowWave - 1].a <= 0.0f)
				{
					g_Alpha[NowWave - 1].a = 0.0f;
				}
			}

		}
		else if (g_NumberFrame <= 42)
		{
			if (GetEnemyWave() >= 1)
			{
				g_Alpha[NowWave - 1].a += 0.2f;
				if (g_Alpha[NowWave - 1].a >= 1.0f)
				{
					g_Alpha[NowWave - 1].a = 1.0f;
				}
			}

		}

		if (g_NumberFrame >= 180)
		{
				g_Alpha[0].a -= 0.1f;
				if (g_Alpha[0].a <= 0.0f)
				{
					g_Alpha[0].a = 0.0f;
				}
				g_Alpha[NowWave].a -= 0.1f;
				if (g_Alpha[NowWave].a <= 0.0f)
				{
					g_Alpha[NowWave].a = 0.0f;
					g_TextChange = false;
					g_NumberFrame = 0;
					if (NowWave == 5)
					{
						g_LastWave = true;
					}

				}		
		}
		else
		{
			g_Alpha[0].a += 0.1f;
			if (g_Alpha[0].a >= 1.0f)
			{
				g_Alpha[0].a = 1.0f;
			}
			
		}



		g_NumberFrame++;
	}
	if (g_LastWave == true)
	{
		if (g_LastWaveFrame >= 10 && g_LastWaveFrame <= 190)
		{
			g_Alpha[6].a += 0.1f;
			if (g_Alpha[6].a >= 1.0f)
			{
				g_Alpha[6].a = 1.0f;
			}
		}

		if (g_LastWaveFrame >= 190)
		{
			g_Alpha[6].a -= 0.1f;
			if (g_Alpha[6].a <= 0.0f)
			{
				g_Alpha[6].a = 0.0f;
				g_LastWave = false;
				g_LastWaveFrame = 0;
			}
		}
		g_LastWaveFrame++;
	}


}

/*============================================================
　　　　　　　　WAVEフォントの描画
============================================================*/
void GameWaveFont_Draw()
{
	Billboard_SetColor(g_Alpha[0]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDWAVE,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (-1.5f) + Camera_GetUpVector()->x * 3.0f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (-1.5f) + Camera_GetUpVector()->y * 3.0f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (-1.5f) + Camera_GetUpVector()->z * 3.0f,
		3.52f, 1.53f, 0, 0, 352, 153);

	Billboard_SetColor(g_Alpha[1]);
	Billboard_DrawAnimationNonZBuffer(g_TextureID1,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (2.1f) + Camera_GetUpVector()->x * 3.0f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (2.1f) + Camera_GetUpVector()->y * 3.0f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (2.1f) + Camera_GetUpVector()->z * 3.0f,
		1.14f, 1.37f, 0, 0, 114, 137);
	Billboard_SetColor(g_Alpha[2]);
	Billboard_DrawAnimationNonZBuffer(g_TextureID2,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (2.1f) + Camera_GetUpVector()->x * 3.0f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (2.1f) + Camera_GetUpVector()->y * 3.0f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (2.1f) + Camera_GetUpVector()->z * 3.0f,
		1.19f, 1.36f, 0, 0, 119, 136);
	Billboard_SetColor(g_Alpha[3]);
	Billboard_DrawAnimationNonZBuffer(g_TextureID3,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (2.1f) + Camera_GetUpVector()->x * 3.0f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (2.1f) + Camera_GetUpVector()->y * 3.0f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (2.1f) + Camera_GetUpVector()->z * 3.0f,
		1.16f, 1.39f, 0, 0, 116, 139);
	Billboard_SetColor(g_Alpha[4]);
	Billboard_DrawAnimationNonZBuffer(g_TextureID4,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (2.1f) + Camera_GetUpVector()->x * 3.0f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (2.1f) + Camera_GetUpVector()->y * 3.0f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (2.1f) + Camera_GetUpVector()->z * 3.0f,
		1.18f, 1.37f, 0, 0, 118, 137);
	Billboard_SetColor(g_Alpha[5]);
	Billboard_DrawAnimationNonZBuffer(g_TextureID5,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * (2.2f) + Camera_GetUpVector()->x * 3.0f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * (2.2f) + Camera_GetUpVector()->y * 3.0f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * (2.2f) + Camera_GetUpVector()->z * 3.0f,
		1.41f, 1.4f, 0, 0, 141, 140);
	Billboard_SetColor(g_Alpha[6]);
	Billboard_DrawAnimationNonZBuffer(g_TextureIDLastWave,
		Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * 0.0f + Camera_GetUpVector()->x * 2.9f,
		Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * 0.0f + Camera_GetUpVector()->y * 2.9f,
		Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * 0.0f + Camera_GetUpVector()->z * 2.9f,
		5.36f, 1.64f, 0, 0, 629, 164);
	Billboard_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}
void GameWaveFont_Final()
{

}

void GameWaveFontChange()
{
	g_TextChange = true;
}