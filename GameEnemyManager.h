#pragma once

#ifndef GAME_ENEMYMANAGER_H_
#define GAME_ENEMYMANAGER_H_

#include "d3dx9.h"
#include "Collision.h"



#define MAX_ENEMY 30

void GameEnemy_Init();
void GameEnemy_Update();
void GameEnemy_Draw();
void GameEnemy_Final();


void GameEnemyKnockBackDir(int index, int AttackType, D3DXVECTOR3 Dir);
void GameEnemyKnockBack(int index);
void EnemyLockOn(int index);
void PlayerIsTouched(int index, int touch);
void EnemyIsBikuri(int index);

bool GetGameEnemyEnable(int index);
bool GetGameEnemyIsAttacking(int index);

D3DXVECTOR3 GetEnemyPos(int index);
D3DXVECTOR3 GetEnemyDir(int index);

CircleCollision GetEnemyCollision(int index);
CircleCollision GetEnemyLockOnZone(int index);
CircleCollision GetEnemyAttackZone(int index);

int GetEnemyType(int index);
void EnemyEndLockOn();
bool GetEnemyIsKnockBack(int index);
bool GetEnemyNotNull(int index);

void DeadAddEnemyCount();
int GetDeadEnemyCount();
int GetEnemyWave();
int GetModelGhost();
int GetModelSlime();


#endif