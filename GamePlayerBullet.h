#pragma once

#ifndef GAME_PLAYER_BULLET_H_
#define GAME_PLAYER_BULLET_H_

#include "d3dx9.h"
#include "Collision.h"



void GameBullet_Init();
void GameBullet_Update();
void GameBullet_Draw();
void GameBullet_Final();

void GameBulletSpawn(float x, float y, float z);
bool GameBulletIsEnable(int index);
void GameBulletDestroy(int index);
int GameBulletGetCountMax();
D3DXVECTOR3 GetGameBulletDir(int index);
CircleCollision GameBulletGetCollision(int index);

#endif


