#pragma once

#ifndef _GAME_FLOOR_H_
#define _GAME_FLOOR_H_

#include <d3dx9.h>


void GameFloor_Init();
void GameFloor_Update();
void GameFloor_Draw();
void GameFloor_Final();


D3DXVECTOR3* GetFloorPos(int index);
LPD3DXMESH* GetFloorModelID(int index);



#endif