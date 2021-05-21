

/*--------------------------------------------


    デバッグフォーム


---------------------------------------------*/
#include <string.h>
#include "DebugFont.h"
#include "Sprite.h"
#include "TextureManager.h"

#define DEBUG_FONT_WIDTH 32
#define DEBUG_FONT_HEIGHT 64
#define DEBUG_FONT_START_CHAR_CODE 32
#define DEBUG_FONT_ONELINE_CHAR_CODE 16


static int g_textureID = INVALID_TEXTURE_ID;

void DebugFont_Init()
{

	g_textureID = Texture_SetTextureLoadFile("asset\\texture\\debug_font_32x64.png");


	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3Dテクスチャの取得に失敗しました！！！", "エラー", MB_OK | MB_ICONHAND);
	}

}
void DebugFont_Final()
{
	Texture_Release(&g_textureID, 1);

}

//
//
void DebugFont_Draw(float dx,float dy , const char* pstring)
{
	
	for (int i = 0; i < strlen(pstring); i++)
	{
		//空白の文字コードは32
		int offset = pstring[i] - ' ';
		int tcx = offset % DEBUG_FONT_ONELINE_CHAR_CODE * DEBUG_FONT_WIDTH;
		int tcy = offset / DEBUG_FONT_ONELINE_CHAR_CODE * DEBUG_FONT_HEIGHT;

		Sprite_Draw(g_textureID, dx + i * DEBUG_FONT_WIDTH, dy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT, tcx, tcy, DEBUG_FONT_WIDTH, DEBUG_FONT_HEIGHT);
	}
	
	

}