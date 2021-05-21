/*============================================================　　
　　　　　　　
　　　　　　リザルト画面（勝ち）

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
#include "GameExplosion.h"
#include "Mouse.h"

static int g_TextureID = INVALID_TEXTURE_ID;
static int g_TextureIDCon = INVALID_TEXTURE_ID;
static int g_TextureIDPress = INVALID_TEXTURE_ID;
static int g_TextureIDMajo = INVALID_TEXTURE_ID;
static int g_TextureIDWin = INVALID_TEXTURE_ID;
static int g_TextureIDBoard = INVALID_TEXTURE_ID;


static int g_ResultFrame = 0;
static float g_ResultInSpeed = 0;
static D3DXVECTOR2 g_ResultPos = { 0.0f,0.0f };
static int g_FontAlpha = 0;
static int g_ReExplosionFrame = 0;

typedef enum ResultMode_tag
{

	RESULTFADE_IN,
	RESULTSHOW,
	RESULTFADE_OUT,
	RESULT_MAX
}ResultMode;


static ResultMode g_ResultMode = RESULTFADE_IN;




/*============================================================　　
　　　　　　リザルト画面の初期化
============================================================*/
void Result_Init() 
{
	PlaySound(SOUND_LABEL_BGM_WIN);
	GameExplosion_Init();
	g_ResultMode = RESULTFADE_IN;
	g_ResultPos = { -858.0f,0.0f };
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\WinBG.png");
	g_TextureIDCon = Texture_SetTextureLoadFile("asset\\texture\\Congradulation.png");
	g_TextureIDPress = Texture_SetTextureLoadFile("asset\\texture\\SpaceKeyBack.png");
	g_TextureIDMajo = Texture_SetTextureLoadFile("asset\\texture\\Majowin.png");
	g_TextureIDWin = Texture_SetTextureLoadFile("asset\\texture\\win.png");
	g_TextureIDBoard = Texture_SetTextureLoadFile("asset\\texture\\Board.png");

	g_ResultFrame = 0;
	g_ResultInSpeed = 25;
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
void Result_Update()
{
	int RandomX = rand() % 500 + 658;
	int RandomY = rand() % 400 + 100;



	GameExplosion_Update();
	
	switch (g_ResultMode)
	{
	case RESULTFADE_IN:
		if (!Fade_IsFade())
		{
			g_ResultMode = RESULTSHOW;
		}
		break;
	case RESULTSHOW:
		if (KeyloggerTrigger(KL_JUMP) && g_ResultFrame >= 360)
		{

			PlaySound(SOUND_LABEL_SE_DECISION);
			//Title_Key = 1;
			g_ResultMode = RESULTFADE_OUT;
			Fade_Start(FADE_OUT, 0.0f, 0.0f, 0.0f, 60);
		}
		break;
	case RESULTFADE_OUT:
		if (!Fade_IsFade())
		{
			Scene_Change(SCENE_TITLE);
		}
		break;
	}

	if (g_ResultFrame >= 60) {
		g_ResultPos.x += g_ResultInSpeed;
		g_ResultInSpeed *= 0.97f;
		if (g_ResultPos.x >= 0)
		{
			g_ResultPos.x = 0;
		}
	}

	if (g_ResultFrame >= 240)
	{
		g_FontAlpha += 2;
			if(g_FontAlpha >= 255)
			{
				g_FontAlpha = 255;
			}
	}


	if (g_ReExplosionFrame >= 30)
	{
		GameExplosion_Spawn(RandomX, RandomY);
		g_ReExplosionFrame = 0;
	}

	g_ResultFrame++;
	g_ReExplosionFrame++;
}

/*============================================================　　
　　　　　　リザルト画面の描画
============================================================*/
void Result_Draw()
{
	Sprite_Draw(g_TextureID, 0, 0, 1280, 720, 0.0f, 0.0f, 1150, 864, 255);


	

	Sprite_Draw(g_TextureIDMajo, g_ResultPos.x, 0, 858, 720, 0.0f, 0.0f, 1486, 1250, 255);
	Sprite_Draw(g_TextureIDBoard, -100, 5, 1400, 120, 0.0f, 0.0f, 1280, 536, g_FontAlpha / 4);
	Sprite_Draw(g_TextureIDBoard, -100, 560, 1400, 120, 0.0f, 0.0f, 1280, 536, g_FontAlpha / 4);

	GameExplosion_Draw();
	Sprite_Draw(g_TextureIDWin, 700.0f, 200.0f, 480.0f, 200.0f, 0.0f, 0.0f,720, 300, 255);
	Sprite_Draw(g_TextureIDCon, 10.0f, 10.0f, 640.0f, 100.0f, 0.0f, 0.0f, 640, 100, g_FontAlpha);
	Sprite_Draw(g_TextureIDPress, 620.0f, 575.0f, 640.0f, 100.0f, 0.0f, 0.0f, 640, 100, g_FontAlpha);
}
void Result_Final(void)
{
	StopSound(SOUND_LABEL_BGM_WIN);
}
