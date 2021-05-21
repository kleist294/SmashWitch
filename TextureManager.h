
#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_
#include<d3d9.h>

//�����ȊǗ��ԍ�
#define INVALID_TEXTURE_ID -1
//�ő�e�N�X�`���t�@�C����������
#define TEXTURE_FILENAME_MAX 64 


void TextureInit();

void TextureFinal();



//�e�N�`���t�@�C���̓ǂݍ��ݗ\��
//����pFileName ...  �t�@�C���l�[��
//�߂�l�F�e�N�X�`���Ǘ��ԍ�
//�ő�Ǘ����𒴂��Ă����ꍇ�� INVALID_TEXTURE_ID
int Texture_SetTextureLoadFile(const char* pFileName);


//�e�N�X�`���̓ǂݍ���
//�\�񂳂�Ă���t�@�C����ǂݍ��݂܂�
//�߂�l�F�ǂݍ��߂Ȃ������t�@�C����
//        �܂��͑��̕s������������ꍇ -1
int Texture_Load();


//�e�N�X�`���̕������
//
//�����FtextureIDs[] ... ���������textureID��������int�^�z��̐擪�A�h���X
//
//count : �������e�N�X�`���̐�
//
//int textureIDs[] => int* ptextureIDs 
void Texture_Release(int textureIDs[], int count);

//�e�N�X�`���S���
void Texture_AllRelease();

//�e�N�X�`�����ƍ����̎擾
//�߂�l�F�e�N�X�`���̕��ƍ���
unsigned long Texture_GetTextureWidth(int textureID);
unsigned long Texture_GetTextureHeight(int textureID);

//�e�N�X�`���C���^�t�F�[�X�|�C���^�[�̎擾
//
//�����F�e�N�X�`���Ǘ��ԍ�
//
//�߂�l�F�e�N�X�`���C���^�t�F�[�X�|�C���^�[
LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureID);

#endif