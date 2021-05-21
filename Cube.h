#pragma once
#ifndef CUBE_H_
#define CUBE_H_

#include <d3dx9.h>


void Cube_Init();
void Cube_Final();
void Cube_Update();
void Cube_Draw(const D3DXMATRIX* pmtxworld);



#endif