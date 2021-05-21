
/*============================================================

　　　　　　　　弾のエフェクト

============================================================*/



#include "Sprite.h"
#include "TextureManager.h"
#include <d3dx9.h>
#include "Collision.h"
#include "Mydirect3d.h"
#include "Billboard.h"


typedef struct Effect_tag
{
	D3DXVECTOR3 Pos;

	
	//透明度
	int Alpha;
	//種類

	int BirthFrame;
	bool Enable;
}Effect;

#define EFFECT_MAX 2048

static int g_TextureID = INVALID_TEXTURE_ID;

static Effect g_BulletEffects[EFFECT_MAX];
static int g_FrameCountEffect = 0;


/*============================================================
　　　　　　　　エフェクトの初期化
============================================================*/
void Effect_Init()
{
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\effect000.jpg");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3Dテクスチャの取得に失敗しました！！！", "エラー", MB_OK | MB_ICONHAND);
	}
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		//g_BulletEffects[i].Pos = D3DXVECTOR2(0.0f, 0.0f);
		g_BulletEffects[i].Enable = false;
		g_BulletEffects[i].BirthFrame = 0;
	}
	g_FrameCountEffect = 0;
}

/*============================================================
　　　　　　　　エフェクトのアップデート
============================================================*/
void Effect_Update()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_BulletEffects[i].Enable)
			continue;
		int age = g_FrameCountEffect - g_BulletEffects[i].BirthFrame;

		if (age >= 60)
		{
			g_BulletEffects[i].Enable = false;
		}

	}

	g_FrameCountEffect++;

}

/*============================================================
　　　　　　　　エフェクトの描画
============================================================*/
void Effect_Draw()
{
	//加算合成の設定
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //ブレンディング処理
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!g_BulletEffects[i].Enable) continue;

		int age = g_FrameCountEffect - g_BulletEffects[i].BirthFrame;

		float a = 1.0f - ((1.0f / 60.0f) * age);

		D3DXCOLOR color(0.5f, 0.3f, 0.2f, a);
		Billboard_SetColor(color);

		//Sprite_Draw(g_TextureID, g_BulletEffects[i].Pos.x, g_BulletEffects[i].Pos.y, 0.0f, 0.0f, 80.0f, 80.0f);
		Billboard_DrawAnimation(g_TextureID, g_BulletEffects[i].Pos.x, g_BulletEffects[i].Pos.y, g_BulletEffects[i].Pos.z, 0.05f,0.05f, 0.0f, 0.0f, 80.0f, 80.0f);

	}

	Billboard_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	//元のαブレンドに戻す
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //ブレンディング処理
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}
void Effect_Final(void)
{
	Texture_Release(&g_TextureID, 1);
}

/*============================================================
　　　　　　　　エフェクトの生成
============================================================*/
void Effect_Spawn(float x, float y,float z)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_BulletEffects[i].Enable)
			continue;

		g_BulletEffects[i].Enable = true;
		g_BulletEffects[i].Pos = D3DXVECTOR3(x, y,z);
		g_BulletEffects[i].BirthFrame = g_FrameCountEffect;
		break;
	}
}
