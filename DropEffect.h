#pragma once
#ifndef DROPEFFECT_H_
#define DROPEFFECT_H_

#include <d3dx9.h>

void DropEffect_Init();
void DropEffect_Draw(float x, float y, float z, float size);
void DropEffect_SetColor(D3DCOLOR color);


#endif