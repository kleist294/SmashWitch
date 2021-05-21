
/*============================================================

　　　　　　　武器が弾の時の演出

============================================================*/


#include "Billboard.h"
#include "GamePlayerManager.h"
#include "TextureManager.h"


static int g_TextureBulletID = INVALID_TEXTURE_ID;
static float BulletY = 0.0f;
static float BulletX = 0.0f;
static float RadiusLength = 0.0f;
static float Pai = 0.0f;
static float BulletYOffset = 0.0f;


/*============================================================
　　　　　　　演出を初期化
============================================================*/
void GameBulletMode_Init() 
{
	g_TextureBulletID = Texture_SetTextureLoadFile("asset\\texture\\bullet002.png");
	RadiusLength = 0.5f;
	Pai = 0.0f;
}

/*============================================================
　　　　　　　演出のアニメーション
============================================================*/
void GameBulletMode_Update()
{
	if (GetPlayerAttackMode() == 0)
	{
		Pai += 0.02f;
		BulletYOffset += 0.04f;
	}

}

/*============================================================
　　　　　　　演出の描画
============================================================*/
void GameBulletMode_Draw()
{

	if (GetPlayerAttackMode() == 0)
	{
		Billboard_Draw(g_TextureBulletID, GetPlayerPos().x + RadiusLength * cosf(Pai), GetPlayerPos().y - 0.3f + cosf(BulletYOffset) * 0.15f, GetPlayerPos().z + RadiusLength * sinf(Pai), 0.1f, 0.1f,1.0f);
	}
}
void GameBulletMode_Final()
{

}