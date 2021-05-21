#pragma once

#ifndef _GAME_STONE_H_
#define _GAME_STONE_H_

#include <d3dx9.h>
#include "Collision.h"

#define MAX_STONE 4


void GameStone_Init();
void GameStone_Update();
void GameStone_Draw();
void GameStone_Final();

bool GetStoneIsEnable(int index);
D3DXVECTOR3* GetStonePos(int index);
LPD3DXMESH* GetStoneModelID(int index);



#endif