#pragma once
#ifndef MYDIRECT3D_H_
#define MYDIRECT3D_H_

//Direct3D9�̏�����

//�߂�l ���s������false
bool MyDirect3D_Init(HWND hWnd);



//Direct3D9�̏I������
void MyDirect3D_Final(void);


//Direct3D�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);
//�A�N�Z�T�[



#endif