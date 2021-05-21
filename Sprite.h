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



//cx ‰ñ“]Šg‘å‚Ì’†SÀ•Wx
//cy ‰ñ“]Šg‘å‚Ì’†SÀ•Wy
void Sprite_Draw(int textureID, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch , float cx, float cy, float angle);

//ƒ|ƒŠƒSƒ“ƒJƒ‰[İ’è
void Sprite_SetColor(D3DCOLOR color);

void Sprite_Final();


#endif