
/*============================================================　
　
　　　　　　リザルト画面（負け）

============================================================*/



#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "Keyboard.h"
#include "Keylogger.h"
#include "TextureManager.h"
#include "Mydirect3d.h"
#include "Game.h"
#include "Title.h"
#include "Sousa.h"
#include "Scene.h"
#include "Sound.h"
#include "Fade.h"
#include "Mouse.h"

static int g_TextureID = INVALID_TEXTURE_ID;
static int g_TextureIDPress = INVALID_TEXTURE_ID;
static int g_TextureIDMajo = INVALID_TEXTURE_ID;
static int g_TextureIDLose = INVALID_TEXTURE_ID;
static int g_TextureIDBoard = INVALID_TEXTURE_ID;


static int g_ResultFrame = 0;
static float g_ResultInSpeed = 0;
static D3DXVECTOR2 g_ResultPos = { 0.0f,0.0f };
static int g_FontAlpha = 0;

typedef enum ResultMode_tag
{

	RESULTLOSEFADE_IN,
	RESULTLOSESHOW,
	RESULTLOSEFADE_OUT,
	RESULTLOSE_MAX
}ResultMode;


static ResultMode g_ResultLoseMode = RESULTLOSEFADE_IN;




/*============================================================　　
　　　　　　リザルト画面の初期化
============================================================*/
void ResultLose_Init()
{
	PlaySound(SOUND_LABEL_BGM_LOSE);
	g_ResultLoseMode = RESULTLOSEFADE_IN;
	g_ResultPos = { 75.0f,-600.0f };
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\LoseBG.png");
	g_TextureIDPress = Texture_SetTextureLoadFile("asset\\texture\\LoseBackTitle.png");
	g_TextureIDMajo = Texture_SetTextureLoadFile("asset\\texture\\Majolose.png");
	g_TextureIDLose = Texture_SetTextureLoadFile("asset\\texture\\Lose.png");
	g_TextureIDBoard = Texture_SetTextureLoadFile("asset\\texture\\Board.png");

	g_ResultFrame = 0;
	g_ResultInSpeed = 28;
	g_FontAlpha = 0;
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3Dテクスチャの取得に失敗しました！！！", "エラー", MB_OK | MB_ICONHAND);
	}
	//Result_Key = 3;
	Mouse_SetMode(MOUSE_POSITION_MODE_ABSOLUTE);
	Fade_Start(FADE_IN, 0.0f, 0.0f, 0.0f, 60);

}

/*============================================================　　
　　　　　　リザルト画面のアップデート
============================================================*/
void ResultLose_Update()
{

	
	switch (g_ResultLoseMode)
	{
	case RESULTLOSEFADE_IN:
		if (!Fade_IsFade())
		{
			g_ResultLoseMode = RESULTLOSESHOW;
		}
		break;
	case RESULTLOSESHOW:
		if (KeyloggerTrigger(KL_JUMP) && g_ResultFrame >= 360)
		{

			PlaySound(SOUND_LABEL_SE_DECISION);
			//Title_Key = 1;
			g_ResultLoseMode = RESULTLOSEFADE_OUT;
			Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);
		}
		break;
	case RESULTLOSEFADE_OUT:
		if (!Fade_IsFade())
		{
			Scene_Change(SCENE_TITLE);
		}
		break;
	}

	if (g_ResultFrame >= 60) {
		g_ResultPos.y += g_ResultInSpeed;
		g_ResultInSpeed *= 0.96f;
		if (g_ResultPos.y >= 100)
		{
			g_ResultPos.y = 100;
		}
	}

	if (g_ResultFrame >= 240)
	{
		g_FontAlpha += 2;
		if (g_FontAlpha >= 255)
		{
			g_FontAlpha = 255;
		}
	}




	g_ResultFrame++;
}

/*============================================================　　
　　　　　　リザルト画面の描画
============================================================*/
void ResultLose_Draw()
{
	Sprite_Draw(g_TextureID, 0, 0, 1280, 720, 0.0f, 0.0f, 560, 426, 255);




	Sprite_Draw(g_TextureIDMajo, g_ResultPos.x, g_ResultPos.y, 600, 412, 0.0f, 0.0f, 800, 550, 255);
	//Sprite_Draw(g_TextureIDBoard, -100, 560, 1400, 120, 0.0f, 0.0f, 1280, 536, g_FontAlpha / 4);
	Sprite_Draw(g_TextureIDLose, 700.0f, 200.0f, 480.0f, 200.0f, 0.0f, 0.0f, 720, 300, 255);
	Sprite_Draw(g_TextureIDPress, 200.0f, 575.0f, 978, 124, 0.0f, 0.0f, 978, 124, g_FontAlpha);
}
void ResultLose_Final(void)
{
	StopSound(SOUND_LABEL_BGM_LOSE);

}

