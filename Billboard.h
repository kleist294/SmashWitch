#pragma once
#ifndef BILLBOARD_H_
#define BILLBOARD_H_

#include"d3dx9.h"


void Billboard_Init();
void Billboard_Uninit();
void Billboard_SetViewMatrix(const D3DXMATRIX& mtxview);
void Billboard_Draw(int textureID ,float x,float y,float z, float sizex, float sizey, float size);
void Billboard_DrawNonZBuffer(int textureID, float x, float y, float z, float sizex, float sizey, float size);
void Billboard_DrawAnimation(int textureID, float x, float y, float z, float sizex, float sizey, int tcx, int tcy, int tcw, int tch);
void Billboard_DrawAnimationNonZBuffer(int textureID, float x, float y, float z, float sizex, float sizey, int tcx, int tcy, int tcw, int tch);

void Billboard_SetColor(D3DCOLOR color);


#endif