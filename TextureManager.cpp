#define _CRT_SECURE_NO_WARNINGS

/*============================================================�@�@

�@�@�@�@�@�@�e�N�X�`���̐���

============================================================*/


#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include "TextureManager.h"
#include "Mydirect3d.h"
#include "DebugPrintf.h"

#define TEXTURE_MAX 1024 //�e�N�X�`���Ǘ��ő吔


//�e�N�X�`���Ǘ��e�[�u���\����
typedef struct Texture_Tag
{

	LPDIRECT3DTEXTURE9 pTexture;
	unsigned long Width;
	unsigned long Height;
	char Filename[TEXTURE_FILENAME_MAX];

}Texture;

//�e�N�X�`���Ǘ��e�[�u��
static Texture g_Textures[TEXTURE_MAX];

/*============================================================�@�@
�@�@�@�@�@�@�e�N�X�`���Ǘ��̏�����
============================================================*/
void TextureInit()
{

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//���I�������[�g���Ă�����
		g_Textures[i].pTexture = NULL;
		g_Textures[i].Width = 0;
		g_Textures[i].Height = 0;
		g_Textures[i].Filename[0] = 0;
	}

}

/*============================================================�@�@
�@�@�@�@�@�@�e�N�X�`����ݒu����֐�
============================================================*/
int Texture_SetTextureLoadFile(const char* pFilename)
{
	//�t�@�C��������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//�󂢂Ă�����A�X�L�b�v
		if (g_Textures[i].Filename[0] == 0)
		{
			continue;
		}

		//���łɎw��̃t�@�C�����\�񂳂�Ă��邩�H
		if (strcmp(pFilename, g_Textures[i].Filename) == 0)
		{

			return i;
		}

	}

	//�V�K�\��
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		//�e�[�u�����g�p����������A�X�L�b�v
		if (g_Textures[i].Filename[0] != 0)
		{
			continue;
		}

		strcpy(g_Textures[i].Filename, pFilename);
		return i;

	}

	return INVALID_TEXTURE_ID;

}

/*============================================================�@�@
�@�@�@�@�@�@�e�N�X�`�������[�h����֐�
============================================================*/
int Texture_Load()
{


	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return -1;
	}
	


	int error_count = 0;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{



		if (g_Textures[i].Filename[0] == 0) 
		{
			//�󂢂Ă���e�[�u��������X�L�b�v
			continue;
		}
		//�A���[���Z�q�ɂȂ�Ȃ��悤��
		if (g_Textures[i].pTexture != NULL)
		{
			//���łɓǂݍ��܂�Ă���
			continue;
		}

		//�e�N�X�`���̓ǂݍ���
		//                            FromMemory�Ƃ������̂������āA�ǂݍ��݂����ɂ��܂�
		HRESULT hr = D3DXCreateTextureFromFile(pDevice, g_Textures[i].Filename, &g_Textures[i].pTexture);
		if (FAILED(hr))
		{
			//�f�o�C�X�̎擾�Ɏ��s
			DebugPrintf("�ǂݍ��߂Ȃ������e�N�X�`���t�@�C�� : [%s]\n", g_Textures[i].Filename);
			error_count++;
			return false;
		}
		else
		{
			D3DXIMAGE_INFO info;
			D3DXGetImageInfoFromFile(g_Textures[i].Filename, &info);
			g_Textures[i].Width = info.Width;
			g_Textures[i].Height = info.Height;

		}

	}

	return error_count;
}


/*============================================================�@�@
�@�@�@�@�@�@�e�N�X�`���������[�X����
============================================================*/
void Texture_Release(int textureIDs[], int count)
{

	for (int i = 0; i < count; i++)
	{
		if (g_Textures[textureIDs[i]].pTexture)
		{
			g_Textures[textureIDs[i]].pTexture->Release();
			g_Textures[textureIDs[i]].pTexture = NULL;
		}
		g_Textures[textureIDs[i]].Filename[0] = 0;
		g_Textures[textureIDs[i]].Width = 0;
		g_Textures[textureIDs[i]].Height = 0;
	}

}

/*============================================================�@�@
�@�@�@�@�@�@�e�N�X�`����S�������[�X����
============================================================*/
void Texture_AllRelease()
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Textures[i].pTexture)
		{
			g_Textures[i].pTexture->Release();
			g_Textures[i].pTexture = NULL;
		}
	g_Textures[i].Filename[0] = 0;
	g_Textures[i].Width = 0;
	g_Textures[i].Height = 0;
	}
}

/*============================================================�@�@
�@�@�@�@�@�@�e�N�X�`���̕����擾����
============================================================*/
unsigned long Texture_GetTextureWidth(int textureID)
{
	return g_Textures[textureID].Width;
}

/*============================================================�@�@
�@�@�@�@�@�@�e�N�X�`���̍������擾����
============================================================*/
unsigned long Texture_GetTextureHeight(int textureID)
{
	return g_Textures[textureID].Height;
}

void TextureFinal()
{

}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureID)
{
	if (textureID == INVALID_TEXTURE_ID) {
		return NULL;
	};
	return g_Textures[textureID].pTexture;
	
}
