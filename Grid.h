#pragma once
#include "d3d9.h"

/*---------------------

     xz平面グリッド描画

-----------------------*/


#ifndef GRID_H_
#define GRID_H_

//グリッド描画モジュールの初期化
//
//size...グリッドのサイズ
//count   一辺のグリッド数
//color    グリッドカラー

void Grid_Init(float size,int count,D3DCOLOR color);
void Grid_Final();
void Grid_Draw();



#endif