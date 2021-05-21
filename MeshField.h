#pragma once
#ifndef MESHFIELD_H_
#define MESHFIELD_H_

#include <d3dx9.h>

#define MESH_X 5
#define MESH_Z 5
#define MESHSIZE 5


void MeshField_Init(int HorinzontalCount,int VerticalCount,int HorinzontalSize,int VerticalSize);
void MeshField_Final();
void MeshField_Draw(int mode, int HorinzontalCount, int VerticalCount, float height, int rotate);



#endif 
