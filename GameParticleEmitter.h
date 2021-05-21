#pragma once

#ifndef GAME_PARTICLEEMITTER_H_
#define GAME_PARTICLEEMITTER_H_


#include "d3dx9.h"
#include "Collision.h"

#define MAX_PARTICLE 1024

void GameParticleEmitter_Init();
void GameParticleEmitter_Update();
void GameParticleEmitter_Draw();
void GameParticleEmitter_Final();
void GameParticleEmitter_Spawn(D3DXVECTOR3 Pos, int TextureID,float size,float speed);

int GetParticleModelID(int textureID);

#endif