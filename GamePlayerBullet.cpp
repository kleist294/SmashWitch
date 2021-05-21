
/*============================================================

　　　　　　　　　　　弾の制御

============================================================*/



#include "TextureManager.h"
#include <d3dx9.h>
#include "Collision.h"
#include "GamePlayerManager.h"
#include "Billboard.h"
#include "shadow.h"
#include "GamePlayerBullet.h"
#include "sound.h"
#include "GameEffect.h"
#include "JudgementRay.h"
#include "GameHitEffect.h"

#define BULLET_MAX 100



typedef struct Bullet_tag
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Direction;
	int Type;
	int Power;
	float Speed;

	CircleCollision Collision;
	bool Enable;
}Bullet;

static int g_TextureBulletID = INVALID_TEXTURE_ID;

static Bullet g_Bullets[BULLET_MAX];



/*============================================================
　　　　　　　　　　　弾の初期化
============================================================*/
void GameBullet_Init()
{
	g_TextureBulletID = Texture_SetTextureLoadFile("asset\\texture\\bullet002.png");

	//g_BulletEnable = false;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullets[i].Enable = false;
		g_Bullets[i].Pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_Bullets[i].Speed = 0.3f;
		g_Bullets[i].Type = 0;
		g_Bullets[i].Power = 0;
		g_Bullets[i].Collision.Center = g_Bullets[i].Pos;
		g_Bullets[i].Collision.radius = 0.2f;
	}
}

/*============================================================
　　　　　　　　　　　弾のアップデート
============================================================*/
void GameBullet_Update()
{
	float Distance = 0.0f;
	//弾が有効が調べる
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullets[i].Enable) {
			if (g_Bullets[i].Pos.x > 40.0f || g_Bullets[i].Pos.x < -40.0f || g_Bullets[i].Pos.z < -40.0f || g_Bullets[i].Pos.z > 40.0f)
			{
				GameBulletDestroy(i);
			}
			if (JudgementRay_ObjectAndObject_Check(g_Bullets[i].Pos, g_Bullets[i].Direction, 0.2f, &Distance, BULLET))
			{
				GameHitEffect_Spawn(g_Bullets[i].Pos.x, g_Bullets[i].Pos.y, g_Bullets[i].Pos.z);
				GameBulletDestroy(i);
			}
		}

		if (!g_Bullets[i].Enable)
			continue;
		D3DXVec3Normalize(&g_Bullets[i].Direction, &g_Bullets[i].Direction);
		//g_Bullets[i].Speed *= 1.1f;
		g_Bullets[i].Pos += g_Bullets[i].Direction * g_Bullets[i].Speed;
		g_Bullets[i].Collision.Center = g_Bullets[i].Pos;
	}
	

}

/*============================================================
　　　　　　　　　　　弾の描画
============================================================*/
void GameBullet_Draw()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//弾が有効が調べる
		if (g_Bullets[i].Enable == true)
		{
			//有効だったら描画
			Billboard_Draw(g_TextureBulletID, g_Bullets[i].Pos.x, g_Bullets[i].Pos.y, g_Bullets[i].Pos.z,0.1f,0.1f,1.0f);
			if (g_Bullets[i].Pos.x > 40.0f || g_Bullets[i].Pos.x < -40.0f || g_Bullets[i].Pos.z < -40.0f || g_Bullets[i].Pos.z > 40.0f)
			ShadowDraw(g_Bullets[i].Pos.x, 0.01f, g_Bullets[i].Pos.z, 0.2f);
			Effect_Spawn(g_Bullets[i].Pos.x, g_Bullets[i].Pos.y, g_Bullets[i].Pos.z);
		}

	}
}

void GameBullet_Final()
{

}

/*============================================================
　　　　　　　　　　　弾の生成
============================================================*/
void GameBulletSpawn(float x, float y, float z)
{
	//弾を有効にする
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullets[i].Enable)
			continue;
		PlaySound(SOUND_LABEL_SE_BULLET);
		g_Bullets[i].Enable = true;
		g_Bullets[i].Pos = D3DXVECTOR3(x, y, z);
		g_Bullets[i].Direction = GetPlayerDir();

		break; // <------------重要!!!!!!!!!!!!
	}
}

/*============================================================
　　　　　　　　　　　弾の当たり判定
============================================================*/
CircleCollision GameBulletGetCollision(int index)
{
	
	return g_Bullets[index].Collision;
}

/*============================================================
　　　　　　　　　　　弾が存在しているか？
============================================================*/
bool GameBulletIsEnable(int index)
{
	return g_Bullets[index].Enable;
}

/*============================================================
　　　　　　　　　　　弾を消す
============================================================*/
void GameBulletDestroy(int index)
{
	g_Bullets[index].Enable = false;
	g_Bullets[index].Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Bullets[index].Speed = 0.3f;
}

/*============================================================
　　　　　　　　　　　弾の向きを取得する
============================================================*/
D3DXVECTOR3 GetGameBulletDir(int index)
{
	return g_Bullets[index].Direction;
}

/*============================================================
　　　　　　　　　　　弾の総数を取得
============================================================*/
int GameBulletGetCountMax()
{
	return BULLET_MAX;
}