
/*============================================================�@�@
�@�@�@�@�@�@
	  �@�@�@�@�@�@�X�R�A

============================================================*/



#include "TextureManager.h"
#include "Sprite.h"
#include "Score.h"
#include <stdio.h>


#define NUMBER_WIDTH 92
#define NUMBER_HEIGHT 144


static int g_TextureID = INVALID_TEXTURE_ID;

static int g_TScore = 0;
static int g_DrawScore = 0;
static int g_Digits = 0;
static bool g_ZeroFill = false;
static bool g_Left = false;

void DrawNumber(int n, float x, float y);


/*============================================================�@�@
�@�@�@�@�@�@�X�R�A�̏�����
============================================================*/
void GameScore_Init(int dig, bool zerofill, bool left)
{
	g_TScore = 0;
	g_DrawScore = 0;
	g_Digits = dig;
	g_ZeroFill = zerofill;
	g_Left = left;

	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\ScoreNumber1.png");
	if (Texture_Load() > 0)
	{
		MessageBox(NULL, "Direct3D�e�N�X�`���̎擾�Ɏ��s���܂����I�I�I", "�G���[", MB_OK | MB_ICONHAND);
	}
}

/*============================================================�@�@
�@�@�@�@�@�@�X�R�A�̃A�b�v�f�[�g
============================================================*/
void GameScore_Update()
{
	//g_DrawScore���J�E���g�A�b�v���Ă���
	if (g_DrawScore < g_TScore)
	{
		g_DrawScore++;
	}
	else if (g_DrawScore > g_TScore)
	{
		g_DrawScore--;
	}

	if (g_DrawScore < 0)
	{
		g_DrawScore = 0;
	}
	//g_DrawScore = std::max(g_DrawScore,0)


	int MaxDrawScore = 1;
	for (int i = 0; i < g_Digits; i++)
	{
		MaxDrawScore *= 10;
	}
	MaxDrawScore--;

	if (g_DrawScore > MaxDrawScore)
	{
		g_DrawScore = MaxDrawScore;
	}
	//g_DrawScore = std::min(g_DrawScore, MaxDrawScore);








}

/*============================================================�@�@
�@�@�@�@�@�@�X�R�A�̕`��
============================================================*/
void GameScore_Draw(float x, float y)
{
	//���l�߂̏ꍇ�A���݂�g_DrawScore�̌��������߂�
	//���̌�����g_Digits�̂����Ƃ���
	char buf[256];
	int digits = sprintf(buf, "%d", g_DrawScore);

	//g_DrawScore��\������
	int Score = g_DrawScore;

	//��ԉE���̐���
	int drawX = x + ((g_Digits - 1) * 24);

	for (int i = 0; i < g_Digits; i++)
	{
		int n = Score % 10;
		DrawNumber(n, drawX, y);
		drawX -= 24 * 2.5f;
		Score /= 10;

		//�[���t�B�����Ȃ��ꍇ
		if (!g_ZeroFill)
		{
			if (Score == 0)
			{
				break;
			}
		}

	}
}

/*============================================================�@�@
�@�@�@�@�@�@�X�R�A�̌v�Z
============================================================*/
void GameScore_AddScore(int score)
{
	GameScore_ConfirmScore();
	g_TScore += score;
}

/*============================================================�@�@
�@�@�@�@�@�@�X�R�A�̎擾
============================================================*/
int GameScore_GetScore(int score)
{
	return g_TScore;
}


void GameScore_ConfirmScore()
{
	g_DrawScore = g_TScore;

}


void DrawNumber(int n, float x, float y)
{
	if (n < 0 || n > 9)return;


	//���Wx, y��n�Ƃ���������\������
	Sprite_Draw(g_TextureID, x, y, 48, 64, n * NUMBER_WIDTH, 0, NUMBER_WIDTH, NUMBER_HEIGHT);

}