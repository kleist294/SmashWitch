#pragma once
#include "d3d9.h"

/*---------------------

     xz���ʃO���b�h�`��

-----------------------*/


#ifndef GRID_H_
#define GRID_H_

//�O���b�h�`�惂�W���[���̏�����
//
//size...�O���b�h�̃T�C�Y
//count   ��ӂ̃O���b�h��
//color    �O���b�h�J���[

void Grid_Init(float size,int count,D3DCOLOR color);
void Grid_Final();
void Grid_Draw();



#endif