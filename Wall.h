#pragma once
#ifndef WALL_H_
#define WALL_H_

#include <d3dx9.h>

#define WALL_X 25
#define WALL_Z 1
#define WALLSIZE 1


void Wall_Init(int HorinzontalCount, int VerticalCount, int HorinzontalSize, int VerticalSize);
void Wall_Final();
void Wall_Draw(int mode, int HorinzontalCount, int VerticalCount, const D3DXMATRIX* pmtxworld);



#endif 
