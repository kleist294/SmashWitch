#pragma once

#ifndef _GAME_GRASS_H_
#define _GAME_GRASS_H_

#include <d3dx9.h>
#include "Collision.h"

#define MAX_GRASS 34


void GameGrass_Init();
void GameGrass_Update();
void GameGrass_Draw();
void GameGrass_Final();

bool GetGrassIsEnable(int index);
D3DXVECTOR3* GetTreePos(int index);
LPD3DXMESH* GetTreeModelID(int index);



#endif