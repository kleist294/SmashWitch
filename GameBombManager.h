#pragma once

#ifndef GAME_BOMBMANAGER_H_
#define GAME_BOMBMANAGER_H_


#include "d3dx9.h"
#include "Collision.h"

#define MAX_BOMB 10

void GameBombManager_Init();
void GameBombManager_Update();
void GameBombManager_Draw();
void GameBombManager_Final();
void GameBombManager_Spawn();

int GetBombModelID();
void BombKnockBackDir(int index, int AttackType, D3DXVECTOR3 Dir);
CircleCollision GetBombCollision(int index);
CircleCollision GetBombAttackZone(int index);
bool GetBombEnable(int index);
void BombExplode(int index);
void BombKnockBack(int index);
bool GetBombKnockBackEnable(int index);
bool GetBombExplode(int index);
void BombCounting(bool count);

LPD3DXMESH* GetBombModelMeshID();

#endif