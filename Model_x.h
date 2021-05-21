#pragma once
#ifndef MODEL_X_H_
#define MODEL_X_H_

#include <d3dx9.h>


//������X���f���Ǘ��ԍ�
#define INVALID_MODEL_X_ID -1

void Model_X_Init();

void Model_X_Final();
//X�t�@�C���̓ǂݍ���
//
//�߂�l�F�����ԍ�
//
int Model_X_Load(const char *pFileName);

//���f���̉��
//
//�����FpIDs...������������f�������ԍ����������������[�̈�̐擪
//      count...������������f�������ԍ��̌�
void Model_x_Release(const int *pIDs,int count);
void Model_x_ReleaseAll();

//���f���̕`��
void Model_X_Draw(int ID, D3DXMATRIX *mtxmodel);
LPD3DXMESH* Model_X_GetMesh(int index);

#endif