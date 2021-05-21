#pragma once

#include "d3dx9.h"
#include "Collision.h"
#include "TextureManager.h"




void GamePlayer_Init();
void GamePlayer_Update();
void GamePlayer_Draw();
void GamePlayer_Final();


void PlayerKnockBack(int AttackType, D3DXVECTOR3 MoveDir);
void GamePlayerKnockBack();

bool GetPlayerSwordAttacking();
int GetPlayerAttackMode();
int GetPlayerHP();

bool GetPlayerIsKnockBack();
bool GetPlayerIsJumping();
bool GetPlayerIsMuteki();
void GamePlayerSetDir(const D3DXVECTOR3* pDir);
void GamePlayerAccelerate();
void playerStopAttack();
int GetModelMajo();


D3DXVECTOR3 GetPlayerDir();
D3DXVECTOR3 GetPlayerLeft();
D3DXVECTOR3 GetPlayerPos();
D3DXVECTOR3 GetPlayerSwordDir();

CircleCollision GetPlayerCollision();
CircleCollision GetPlayerSwordCollision();
