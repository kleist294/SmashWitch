#pragma once
#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <d3dx9.h>


void SkyBox_Init();
void SkyBox_Final();
void SkyBox_Draw(const D3DXMATRIX* pmtxworld);



#endif