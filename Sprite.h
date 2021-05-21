#pragma once
#ifndef SPRITE_H_
#define SPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>

void Sprite_Init();


void Sprite_Draw(int textureID,float dx,float dy);

void Sprite_Draw(int textureID, float dx, float dy, int tcx, int tcy, int tcw, int tch);

void Sprite_Draw(int textureID, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);


void Sprite_Draw(int textureID, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch , int alpha);



//cx ��]�g��̒��S���Wx
//cy ��]�g��̒��S���Wy
void Sprite_Draw(int textureID, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch , float cx, float cy, float angle);

//�|���S���J���[�ݒ�
void Sprite_SetColor(D3DCOLOR color);

void Sprite_Final();


#endif