#pragma once

#ifndef _GAME_TREE_H_
#define _GAME_TREE_H_

#include <d3dx9.h>
#include "Collision.h"

#define MAX_TREE 24


void GameTree_Init();
void GameTree_Update();
void GameTree_Draw();
void GameTree_Final();

bool GetTreeIsEnable(int index);
D3DXVECTOR3* GetTreePos(int index);
LPD3DXMESH* GetTreeModelID(int index);



#endif