
/*=============================================================

　　　　　　　　　　操作方法画面の描画

=============================================================*/



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

static int g_TextureID = INVALID_TEXTURE_ID;
static int g_TextureIDSousa = INVALID_TEXTURE_ID;
static int g_TextureIDKeyBoard = INVALID_TEXTURE_ID;
static int g_TextureIDSPACE = INVALID_TEXTURE_ID;
static int g_TextureIDWSAD = INVALID_TEXTURE_ID;
static int g_TextureIDQ = INVALID_TEXTURE_ID;
static int g_TextureIDE = INVALID_TEXTURE_ID;
static int g_TextureIDX = INVALID_TEXTURE_ID;

static int g_TextureIDPlusMinus = INVALID_TEXTURE_ID;
static int g_TextureIDArrow = INVALID_TEXTURE_ID;
static int g_TextureIDBoard = INVALID_TEXTURE_ID;
static int g_TextureIDGameStart = INVALID_TEXTURE_ID;
static int g_TextureIDGameStartArrow = INVALID_TEXTURE_ID;

static int g_ArrowMode = 0;
static int g_ArrowFrame = 0;


typedef enum SousaMode_tag
{

	SOUSAFADE_IN,
	SOUSASHOW,
	SOUSAFADE_OUT,
	SOUSA_MAX
}SousaMode;


static SousaMode g_SousaMode = SOUSAFADE_IN;


/*=============================================================
　　　　　　　　　　操作方法画面の初期化
=============================================================*/
void Sousa_Init()
{
	g_SousaMode = SOUSAFADE_IN;
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\SousaBG.png");
	g_TextureIDSousa = Texture_SetTextureLoadFile("asset\\texture\\Sousa.png");
	g_TextureIDKeyBoard = Texture_SetTextureLoadFile("asset\\texture\\SousaKey.png");
	g_TextureIDSPACE = Texture_SetTextureLoadFile("asset\\texture\\space.png");
	g_TextureIDWSAD = Texture_SetTextureLoadFile("asset\\texture\\WSAD.png");
	g_TextureIDQ = Texture_SetTextureLoadFile("asset\\texture\\Qkey.png");
	g_TextureIDE = Texture_SetTextureLoadFile("asset\\texture\\Ekey.png");
	g_TextureIDX = Texture_SetTextureLoadFile("asset\\texture\\Xkey.png");
	g_TextureIDPlusMinus = Texture_SetTextureLoadFile("asset\\texture\\plusminuskey.png");
	g_TextureIDArrow = Texture_SetTextureLoadFile("asset\\texture\\arrowkey.png");
	g_TextureIDBoard = Texture_SetTextureLoadFile("asset\\texture\\board.png");
	g_TextureIDGameStart = Texture_SetTextureLoadFile("asset\\texture\\GameStart.png");
	g_TextureIDGameStartArrow = Texture_SetTextureLoadFile("asset\\texture\\Arrow.png");

	g_ArrowMode = 0;
	g_ArrowFrame = 0;

	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3Dテクスチャの取得に失敗しました！！！", "エラー", MB_OK | MB_ICONHAND);
	}
	Fade_Start(FADE_IN, 0.0f, 0.0f, 0.0f, 60);
}

/*=============================================================
　　　　　　　　　　操作方法画面のアップデート
=============================================================*/
void Sousa_Update()
{

	if (g_ArrowFrame >= 20)
	{
		g_ArrowFrame = 0;
		if (g_ArrowMode >= 6)
		{
			g_ArrowMode = 0;
		}

		g_ArrowMode++;
	}

	switch (g_SousaMode)
	{
	case SOUSAFADE_IN:
		if (!Fade_IsFade())
		{
			g_SousaMode = SOUSASHOW;
		}
		break;
	case SOUSASHOW:
		if (KeyloggerTrigger(KL_JUMP))
		{

			PlaySound(SOUND_LABEL_SE_DECISION);
			//Title_Key = 1;
			g_SousaMode = SOUSAFADE_OUT;
			Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);
		}
		break;
	case SOUSAFADE_OUT:
		if (!Fade_IsFade())
		{
			Scene_Change(SCENE_GAME);
		}
		break;
	}

	g_ArrowFrame++;

}

/*=============================================================
　　　　　　　　　　操作方法画面の描画
=============================================================*/
void Sousa_Draw() 
{
	Sprite_Draw(g_TextureID, 0, 0, 1280, 720, 150.0f, 0.0f, 1600, 900, 255);

	Sprite_Draw(g_TextureIDKeyBoard, 190, 120, 900, 250, 0.0f, 0.0f, 2442, 679, 255);

	Sprite_Draw(g_TextureIDBoard, 140, 400, 1000, 280, 0.0f, 0.0f, 1280, 536, 128);
	Sprite_Draw(g_TextureIDGameStart, 570, 580, 386, 90, 0.0f, 0.0f, 262, 61, 128);
	if (g_ArrowMode >= 1 && g_ArrowMode <= 3)
	Sprite_Draw(g_TextureIDGameStartArrow, 930, 585, 79, 85, 0.0f, 0.0f, 61, 65, 128);
	if (g_ArrowMode >= 2 && g_ArrowMode <= 4)
	Sprite_Draw(g_TextureIDGameStartArrow, 980, 585, 79, 85, 0.0f, 0.0f, 61, 65, 128);
	if (g_ArrowMode >= 3 && g_ArrowMode <= 5)
	Sprite_Draw(g_TextureIDGameStartArrow, 1030, 585,79, 85, 0.0f, 0.0f, 61, 65, 128);

	Sprite_Draw(g_TextureIDSPACE   , 160, 420, 432, 75, 0.0f, 0.0f, 791, 137, 255);
	Sprite_Draw(g_TextureIDWSAD    , 160, 480, 270, 75, 0.0f, 0.0f, 455, 126, 255);
	Sprite_Draw(    g_TextureIDQ   , 160, 540, 340, 75, 0.0f, 0.0f, 590, 130, 255);
	Sprite_Draw(    g_TextureIDE   , 160, 600, 162, 75, 0.0f, 0.0f, 278, 128, 255);
	Sprite_Draw(g_TextureIDArrow   , 600, 420, 417, 75, 0.0f, 0.0f, 691, 124, 255);
	Sprite_Draw(g_TextureIDPlusMinus,610, 480, 440, 75, 0.0f, 0.0f, 922, 124, 255);
	Sprite_Draw(g_TextureIDX       , 610, 540, 213, 75, 0.0f, 0.0f, 356, 125, 255);

	Sprite_Draw(g_TextureIDSousa, 408, 10, 463,127, 0.0f, 0.0f, 463, 127, 255);


}
void Sousa_Final(void)
{

}

