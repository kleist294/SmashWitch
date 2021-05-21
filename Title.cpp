
/*============================================================
　　
　　　　　　タイトル画面の描画

============================================================*/



#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "Keyboard.h"
#include "Keylogger.h"
#include "TextureManager.h"
#include "Mydirect3d.h"
#include "Sound.h"
#include "Scene.h"
#include "Fade.h"
#include "Comet.h"
#include "Mouse.h"

static int g_TextureID = INVALID_TEXTURE_ID;
static int g_TextureIDTitle = INVALID_TEXTURE_ID;
static int g_TextureIDPress = INVALID_TEXTURE_ID;
static int g_TextureIDMajo = INVALID_TEXTURE_ID;
static int g_TextureIDBoard = INVALID_TEXTURE_ID;
static int g_TextureIDWitch = INVALID_TEXTURE_ID;
static int g_TextureIDSmash = INVALID_TEXTURE_ID;

static int g_TitleAlphaMode = 0;
static float g_TitleAlpha = 0;
static int g_CometFrame = 0;
static int g_MajoFrame = 0;
static int g_TitleFrame = 0;
static float g_TitleFontPosX = 0;
static float g_TitleFontSpeed = 0;
static D3DXVECTOR2 g_MajoPos = { 0.0f,0.0f };
static float g_BoardPosY = 0.0f;
static int g_BoardSizeY = 0;
float g_TitleBGX = 0;
float g_FrameTitle;
static D3DXVECTOR2 g_ResultInSpeed = { 0.0f,0.0f };

typedef enum TitleMode_tag
{

	TITLEFADE_IN,
	TITLESHOW,
	TITLEFADE_OUT,
	
}TitleMode;


static TitleMode g_TitleMode = TITLEFADE_IN;

/*============================================================
　　　　　　タイトル画面の初期化
============================================================*/
void Title_Init()
{
	g_TitleMode = TITLEFADE_IN;
	PlaySound(SOUND_LABEL_BGM_TITLE);
	Comet_Init();
	g_CometFrame = 0;
	g_MajoFrame = 0;
	g_TitleFrame = 0;
	g_TitleAlpha = 0;
	g_MajoPos = { -600.0f,-600.0f };
	g_BoardPosY = 300.0f;
	g_TitleFontPosX = 0;
	g_ResultInSpeed = { 20.0f ,20.0f };
	g_TitleFontSpeed = 3;
	g_BoardSizeY = 0;
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\title1.png");
	g_TextureIDTitle = Texture_SetTextureLoadFile("asset\\texture\\TitleWord.png");
	g_TextureIDPress = Texture_SetTextureLoadFile("asset\\texture\\Spacekey.png");
	g_TextureIDMajo = Texture_SetTextureLoadFile("asset\\texture\\majotitle.png");
	g_TextureIDBoard = Texture_SetTextureLoadFile("asset\\texture\\Board.png");
	g_TextureIDWitch = Texture_SetTextureLoadFile("asset\\texture\\witch.png");
	g_TextureIDSmash = Texture_SetTextureLoadFile("asset\\texture\\smash.png");
	//g_TitleBGX = 0;
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3Dテクスチャの取得に失敗しました！！！", "エラー", MB_OK | MB_ICONHAND);
	}

	g_TitleAlphaMode = 0;
	int g_TitleAlpha = 0;

	Mouse_SetMode(MOUSE_POSITION_MODE_ABSOLUTE);

	Fade_Start(FADE_IN,0.0f, 0.0f, 0.0f, 60);
}

/*============================================================
　　　　　　タイトル画面のアップデート
============================================================*/
void Title_Update()
{
	int RandomX = rand() % 1280 + 1280;
	int RandomY = rand() % 720 - 720;

	

	Comet_Update();
	g_TitleBGX += 0.2f;
	
	switch (g_TitleMode)
	{
	case TITLEFADE_IN:
		if (!Fade_IsFade())
		{
			g_TitleMode = TITLESHOW;
		}
		break;
	case TITLESHOW:
		if (KeyloggerTrigger(KL_JUMP))
		{
	
			PlaySound(SOUND_LABEL_SE_DECISION);
			//Title_Key = 1;
			g_TitleMode = TITLEFADE_OUT;
			Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);
		}
		break;
	case TITLEFADE_OUT:
		if (!Fade_IsFade())
		{
			Scene_Change(SCENE_SOUSA);
		}
		break;
	}
	
	if (g_FrameTitle >= 10 && g_TitleFrame >= 350)
	{
		g_FrameTitle = 0;

		if (g_TitleAlphaMode == 0)
		{
			g_TitleAlpha += 0.1f;
			if (g_TitleAlpha >= 1.0f)
			{
				g_TitleAlphaMode = 1;
			}
		}
		if (g_TitleAlphaMode == 1)
		{
			g_TitleAlpha -= 0.1f;
			if (g_TitleAlpha <= 0.5f)
			{
				g_TitleAlphaMode = 0;
			}
		}

	}
	if (g_CometFrame >= 10 && g_TitleFrame >= 120) {
		g_CometFrame = 0;
		Comet_Spawn(RandomX, RandomY);
	}









	g_MajoPos += g_ResultInSpeed;

	g_ResultInSpeed.x *= 0.97f;
	g_ResultInSpeed.y *= 0.97f;
	if (g_MajoPos.x >= 50)
	{
		g_MajoPos.x = 50;
	}
	if (g_MajoPos.y >= 50)
	{
		g_MajoPos.y = 50;
	}

	if (g_TitleFrame >= 180)
	{
		g_BoardPosY -= 2;
		g_BoardSizeY+= 4;

		if (g_BoardPosY <= 100)
		{
			g_BoardPosY = 100;
		}

		if (g_BoardSizeY >= 400)
		{
			g_BoardSizeY = 400;
		}
	}

	if (g_TitleFrame >= 280)
	{
		g_TitleFontPosX += g_TitleFontSpeed;
		g_TitleFontSpeed *= 0.99;
		if (g_TitleFontPosX >= 255)
		{
			g_TitleFontPosX = 255;
		}
	}

	g_FrameTitle++;
	g_CometFrame++;
	g_MajoFrame++;
	g_TitleFrame++;
}

/*============================================================
　　　　　　タイトル画面の描画する
============================================================*/
void Title_Draw()
{
	Sprite_Draw(g_TextureID, 0.0f, 0.0f, 1280.0f, 720.0f, 0, 0, 1280, 720, 255);
	Comet_Draw();
	Sprite_Draw(g_TextureIDBoard, 280.0f, g_BoardPosY, 900.0f, g_BoardSizeY, 0.0f, 0.0f,1280, 536, 255);
	Sprite_Draw(g_TextureIDSmash, 450.0f + 255 - g_TitleFontPosX, 120, 331 * 1.5, 123 * 1.5, 0.0f, 0.0f, 331, 123, g_TitleFontPosX);
	Sprite_Draw(g_TextureIDWitch, 700.0f - 255 + g_TitleFontPosX, 300, 287 * 1.5, 128 * 1.5, 0.0f, 0.0f, 287, 128, g_TitleFontPosX);
	Sprite_Draw(g_TextureIDPress, 210.0f, 520.0f, 547*1.5, 121*1.5, 0.0f, 0.0f, 547, 121, (int)255.0f * g_TitleAlpha);

	Sprite_Draw(g_TextureIDMajo, g_MajoPos.x, g_MajoPos.y, 500, 500, 0.0f, 0.0f, 800, 800, 255);


	

}
void Title_Final(void)
{
	StopSound(SOUND_LABEL_BGM_TITLE);

}

