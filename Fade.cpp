
/*============================================================

　　　　　　画面遷移の制御

============================================================*/


#include <d3dx9.h>
#include "Sprite.h"
#include "TextureManager.h"
#include "Fade.h"
#include "Config.h"
#include "Billboard.h"
#include "Camera.h"
#include "Scene.h"

static FadeMode g_FadeMode = FADE_NONE;
static D3DXCOLOR g_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
static float g_prop = 0.0f;
static int g_FadeFrame = 0;
static int g_FrameCount = 0;
static int g_FadeStartFrame = 0;
static int g_textureID = INVALID_TEXTURE_ID;

/*============================================================
　　　　　　画面遷移の初期化
============================================================*/

void Fade_Init()
{
	//g_textureID = Texture_SetTextureLoadFile("asset\\texture\\fade.png");
	//if (Texture_Load() > 0)
	//{
	//	MessageBox(NULL, "Direct3Dテクスチャの取得に失敗しました！！！", "エラー", MB_OK | MB_ICONHAND);
	//}
	g_FadeMode = FADE_NONE;
	g_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_prop = 0.0f;
	g_FadeFrame = 0;
	g_FrameCount = 0;
	g_FadeStartFrame = 0;
	g_textureID = INVALID_TEXTURE_ID;

	g_textureID = Texture_SetTextureLoadFile("asset\\texture\\fade.png");
	
}

/*============================================================
　　　　　　画面遷移のアップデート
============================================================*/
void Fade_Update() 
{
	g_FrameCount++;

	if (g_FadeMode == FADE_NONE)return;

	//現在の進行フレーム数を算出
	int frame = g_FrameCount - g_FadeStartFrame;


	//最終フェードフレーム数から0～1の進行割合を算出
	g_prop = (float)frame / g_FadeFrame;
	if (g_prop > 1.0f)
	{
 		g_FadeMode = FADE_NONE;
		g_prop = 1.0f;
	}


}

/*============================================================
　　　　　　画面遷移の描画
============================================================*/
void Fade_Draw() 
{

	if (g_FadeMode != FADE_NONE) {
		g_color.a = g_FadeMode == FADE_IN ? 1.0f - g_prop : g_prop;
	}

	if (g_color.a <= 0.001f) return;

	
		Sprite_SetColor(g_color);
	
		Sprite_Draw(g_textureID, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 8, 8);

		Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	
}

/*============================================================
　　　　　　画面遷移のリリース
============================================================*/
void Fade_Final(void)
{

	Texture_Release(&g_textureID,1);

}


/*============================================================
　　　　　　画面遷移が始まる
============================================================*/
void Fade_Start(FadeMode mode, float r, float g, float b, int frame)
{
	g_FadeMode = mode;
	g_color = D3DXCOLOR(r, g, b, 0.0f);
	g_prop = 0.0f;
	g_FadeFrame = frame;
	g_FadeStartFrame = g_FrameCount;

}

/*============================================================
　　　　　　画面遷移の状態
============================================================*/
bool Fade_IsFade(void)
{
	return g_FadeMode != FADE_NONE;
}