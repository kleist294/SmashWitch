
/*===========================================================

　　　　　　　　カーソル（ポーズ状態）

===========================================================*/


#include "TextureManager.h"
#include <d3dx9.h>
#include "Fade.h"
#include "Sound.h"
#include "Camera.h"
#include "Sprite.h"
#include "GameCursor.h"
#include "Game.h"

static D3DXVECTOR2 g_CursorPos = { 0.0f,0.0f };
static int g_TextureIDCursor = INVALID_TEXTURE_ID;


/*===========================================================
　　　　　　　　カーソルの初期化
===========================================================*/
void GameCursor_Init()
{
	g_TextureIDCursor = Texture_SetTextureLoadFile("asset\\texture\\Cursor.png");

	g_CursorPos = { GetCursorX(),GetCursorY() };
}

/*===========================================================
　　　　　　　　カーソルのアップデート
===========================================================*/
void GameCursor_Update()
{
	g_CursorPos = { GetCursorX(),GetCursorY() };

}

/*===========================================================
　　　　　　　　カーソルの描画
===========================================================*/
void GameCursor_Draw()
{
	Sprite_Draw(g_TextureIDCursor, g_CursorPos.x, g_CursorPos.y, 40, 40, 0, 0, 560, 560);

}
void GameCursor_Final()
{

}
