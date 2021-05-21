
/*============================================================

�@�@�@�@�@�@��ʑJ�ڂ̐���

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
�@�@�@�@�@�@��ʑJ�ڂ̏�����
============================================================*/

void Fade_Init()
{
	//g_textureID = Texture_SetTextureLoadFile("asset\\texture\\fade.png");
	//if (Texture_Load() > 0)
	//{
	//	MessageBox(NULL, "Direct3D�e�N�X�`���̎擾�Ɏ��s���܂����I�I�I", "�G���[", MB_OK | MB_ICONHAND);
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
�@�@�@�@�@�@��ʑJ�ڂ̃A�b�v�f�[�g
============================================================*/
void Fade_Update() 
{
	g_FrameCount++;

	if (g_FadeMode == FADE_NONE)return;

	//���݂̐i�s�t���[�������Z�o
	int frame = g_FrameCount - g_FadeStartFrame;


	//�ŏI�t�F�[�h�t���[��������0�`1�̐i�s�������Z�o
	g_prop = (float)frame / g_FadeFrame;
	if (g_prop > 1.0f)
	{
 		g_FadeMode = FADE_NONE;
		g_prop = 1.0f;
	}


}

/*============================================================
�@�@�@�@�@�@��ʑJ�ڂ̕`��
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
�@�@�@�@�@�@��ʑJ�ڂ̃����[�X
============================================================*/
void Fade_Final(void)
{

	Texture_Release(&g_textureID,1);

}


/*============================================================
�@�@�@�@�@�@��ʑJ�ڂ��n�܂�
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
�@�@�@�@�@�@��ʑJ�ڂ̏��
============================================================*/
bool Fade_IsFade(void)
{
	return g_FadeMode != FADE_NONE;
}