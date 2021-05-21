
/*============================================================

　　　　　　　　　　　レーダーの描画

============================================================*/




#include "TextureManager.h"
#include <d3dx9.h>
#include "Fade.h"
#include "sound.h"
#include "Camera.h"
#include "GamePlayerManager.h"
#include "Sprite.h"
#include "GameEnemyManager.h"
#include "GameRadar.h"



typedef struct
{
	D3DXVECTOR2 RadarEnemyPos;
	bool IsEnable;
	float RadarEnemyRange;
}RadarEnemy;




static int g_TextureIDRadar = INVALID_TEXTURE_ID;
static int g_TextureIDRadarEnemy = INVALID_TEXTURE_ID;
static int g_TextureIDRadarEffect = INVALID_TEXTURE_ID;
static float RadarEffectSize = 0.0f;

static D3DXVECTOR2 g_RadarPos = {950,450};
static RadarEnemy g_RadarEnemy[MAX_ENEMY];

/*============================================================
　　　　　　　　　　　レーダーの初期化
============================================================*/
void GameRadar_Init()
{
	g_TextureIDRadar = Texture_SetTextureLoadFile("asset\\texture\\radar.png");
	g_TextureIDRadarEffect = Texture_SetTextureLoadFile("asset\\texture\\EnemyDrop.png");
	g_TextureIDRadarEnemy = Texture_SetTextureLoadFile("asset\\texture\\radarenemy.png");

	RadarEffectSize = 0.0f;
	
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_RadarEnemy[i].IsEnable = false;
		g_RadarEnemy[i].RadarEnemyPos = { 0.0f ,0.0f};
		g_RadarEnemy[i].RadarEnemyRange = 0;
	}

}

/*============================================================
　　　　　　　　　　　レーダーのアップデート
============================================================*/
void GameRadar_Update()
{



	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (!GetEnemyNotNull(i)) continue;
		
		D3DXVECTOR2 front = { Camera_GetFrontVector()->x, Camera_GetFrontVector()->z };
		D3DXVECTOR2 pc = { GetPlayerPos().x,GetPlayerPos().z};
		D3DXVECTOR2 ec = {GetEnemyPos(i).x,GetEnemyPos(i).z};
		D3DXVECTOR2 EnemyVector = {ec - pc};
		D3DXVec2Normalize(&EnemyVector, &EnemyVector);
		//座標に対するcos計算
		float YVector = (front.x * EnemyVector.x + front.y * EnemyVector.y) /
			sqrt((front.x * front.x + front.y * front.y) * (EnemyVector.x * EnemyVector.x + EnemyVector.y * EnemyVector.y));
		//座標に対するsin計算
		float XVector = -front.y * EnemyVector.x + front.x * EnemyVector.y;
		g_RadarEnemy[i].RadarEnemyRange = sqrt(D3DXVec2LengthSq(&(pc - ec)));

		//敵がプレイヤーの索敵範囲に入るのか
		if (GetGameEnemyEnable(i) == true && g_RadarEnemy[i].RadarEnemyRange < RADAR_RANGE)
		{
			g_RadarEnemy[i].IsEnable = true;
		}
		else
		{
			g_RadarEnemy[i].IsEnable = false;
		}


		
		float RadarRange = (RADAR_SIZE / 2 - 20) * (g_RadarEnemy[i].RadarEnemyRange / RADAR_RANGE);
		D3DXVECTOR2 RadarCenter = { g_RadarPos.x + RADAR_SIZE / 2 - 10 ,g_RadarPos.y + RADAR_SIZE / 2 - 14 };



		g_RadarEnemy[i].RadarEnemyPos = { RadarCenter.x - RadarRange * XVector ,RadarCenter.y - RadarRange * YVector };
	}






	RadarEffectSize += 2.5f;
	if (RadarEffectSize >= 210)
	{
		RadarEffectSize = 0.0f;
	}
}

/*============================================================
　　　　　　　　　　　レーダーの描画
============================================================*/
void GameRadar_Draw()
{
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 125));
	Sprite_Draw(g_TextureIDRadarEffect, g_RadarPos.x + RADAR_SIZE / 2 - RadarEffectSize / 2, g_RadarPos.y + RADAR_SIZE / 2 - RadarEffectSize / 2, RadarEffectSize, RadarEffectSize, 0, 0, 400,400);
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	Sprite_Draw(g_TextureIDRadar, g_RadarPos.x, g_RadarPos.y, RADAR_SIZE, RADAR_SIZE, 0,0, 512,512);

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_RadarEnemy[i].IsEnable == true)
		{
			Sprite_Draw(g_TextureIDRadarEnemy, g_RadarEnemy[i].RadarEnemyPos.x, g_RadarEnemy[i].RadarEnemyPos.y,20, 20, 0, 0, 28, 28);

		}
	}


}
void GameRadar_Final()
{


}

