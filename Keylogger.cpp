
/*============================================================

�@�@�@�@�@�@�@�@�@�L�[�{�[�h�̓o�^

============================================================*/


#include "keylogger.h"
#include "keyboard.h"

typedef unsigned long KeyloggerType;
 static KeyloggerType g_CurrentData = 0;
 static KeyloggerType g_PrevData = 0;
 static KeyloggerType g_TriggerData = 0;
 static KeyloggerType g_ReleaseData = 0;


static int g_KeyLoggerMode = 0; //�O�̓m�[�}���@�P�͋L�^�@�Q�͍Đ�
static KeyloggerType* g_pRecordCurrentData = NULL;
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;
static Keyboard_Keys g_KKs[KL_MAX] = 
{
	KK_W,
	KK_S,
	KK_A,
	KK_D,
	KK_SPACE,
	KK_X,
	KK_Q,
	KK_E,
	KK_LEFT,
	KK_RIGHT,
	KK_UP,
	KK_DOWN,
	KK_ESCAPE,
	KK_ADD,
	KK_SUBTRACT,
	KK_L

};


void KeyLogger_Init()
{
	g_CurrentData = g_PrevData = 0;
	g_TriggerData = 0;
	g_ReleaseData = 0;
	g_KeyLoggerMode = 0;
	g_pRecordCurrentData = NULL;
	g_RecordFrame = 0;
	g_RecordPlayFrame = 0;
	g_RecordFrameMax = 10000;
}
void KeyLogger_Update()
{
	//�O�t���[���̃L�[��ۑ�
	g_PrevData = g_CurrentData;

	if (g_KeyLoggerMode <= 1)
	{
		g_CurrentData = 0;
		for (int i = 0; i < KL_MAX; i++)
		{
			if (Keyboard_IsKeyDown(g_KKs[i]))
			{
				g_CurrentData |= 1u << i;
			}
		}
		//�L�[�L�^���[�h
		if (g_KeyLoggerMode == 1)
		{
			//if (g_RecordPlayFrame > g_RecordFrame)
			if (g_RecordFrame < g_RecordFrameMax) {
				g_pRecordCurrentData[g_RecordFrame++] = g_CurrentData;
			}
		}
	}
	else
	{
		//�Đ����[�h


		//���S���u�i�L�^�t���[�������������Đ����悤�Ƃ�����j
		if (g_RecordPlayFrame < g_RecordFrame)
		{
			g_CurrentData = g_pRecordCurrentData[g_RecordFrame++];
		}
		else
		{
			g_CurrentData = 0;
			g_KeyLoggerMode = 0; //0...���ʃ��[�h
		}

		/*
		if (g_RecordPlayFrame >= g_RecordFrame)
		{
			g_RecordPlayFrame = g_RecordFrame - 1;
		}
		*/
		//g_CurrentData = g_pRecordCurrentData[g_RecordPlayFrame++];
	}

	//�������u�ԂƗ������u�Ԃ̃L�[���擾
	g_TriggerData = (g_PrevData ^ g_CurrentData) & g_CurrentData;
	g_ReleaseData = (g_PrevData ^ g_CurrentData) & g_PrevData;

}

void KeyLogger_Final(void)
{
	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}

bool KeyloggerPress(KeyKind kl)
{
	return g_CurrentData & (1u << (int)kl);
}
bool KeyloggerTrigger(KeyKind kl)
{
	return g_TriggerData & (1u << (int)kl);
}
bool KeyloggerRelease(KeyKind kl)
{
	return g_ReleaseData & (1u << (int)kl);
}

void Keylogger_RecordStart(int frame_max)
{
	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
	}

	g_pRecordCurrentData = (KeyloggerType*)malloc(sizeof(KeyloggerType) * frame_max);
	g_KeyLoggerMode = 1;
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;
}
void Keylogger_RecordEnd(void)
{
	if (!g_pRecordCurrentData)
	{
		return;
	}
	FILE* fp = fopen("keylogger.dat", "wb");
	//�o�C�i���[�̐擪�Ƀf�[�^�ʂ��L�^
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1,fp);
	//�t�@�C���փf�[�^��ۑ�
	fwrite(g_pRecordCurrentData, sizeof(unsigned char), g_RecordFrame, fp);
	fclose(fp);

	//���ʃ��[�h
	g_KeyLoggerMode = 0;

}

void Keylogger_RecordLoad(void)
{
	FILE* fp = fopen("keylogger.dat", "rb");
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);

	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
	}

	g_pRecordCurrentData = (KeyloggerType*)malloc(sizeof(KeyloggerType) * g_RecordFrame);
	fread(g_pRecordCurrentData, sizeof(KeyloggerType), g_RecordFrame, fp);
	fclose(fp);
}

void Keylogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_KeyLoggerMode = 2;// 2...�Đ����[�h

}
bool Keylogger_IsRecordPlay(void)
{
	if (g_KeyLoggerMode == 2)
	{
		return true;
	}

	return false;
}