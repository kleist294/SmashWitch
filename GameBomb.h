#pragma once

#ifndef GAME_BOMB_H_
#define GAME_BOMB_H_





#include "d3dx9.h"
#include "Collision.h"
#include "MeshField.h"
#include "Model_x.h"
#include "GameBombManager.h"


#define ACCELERATION_BY_FRAME 0.01f
#define EDGE_X ((float)(MESH_X * MESHSIZE / 2) + 0.5f)
#define EDGE_Z ((float)(MESH_Z * MESHSIZE / 2) + 0.5f)



class Bomb
{
public:

	Bomb();
	~Bomb();


	void BombDraw();
	void BombSpawn(D3DXVECTOR3 Pos);
	void BombExplode();
	void BombStatus();
	void BombKnockBack(D3DXVECTOR3 MoveDir, int AttackType);
	void BombKnockBackAccelerate();
	void BombKnockBackEnable();
	bool GetBombIsEnable();
	bool GetIsKnockBack();
	bool GetBombIsExplode();

	CircleCollision GetCollision();
	CircleCollision GetAttackZone();


private:


	int m_BombModelID = GetBombModelID();

	D3DXVECTOR3 m_BombPos;
	bool m_IsEnable = false;
	bool m_IsKnockBack = false;
	bool m_IsAttacked = false;
	bool m_IsExplode = false;
	bool m_IsDrop = false;
	int m_AttackedType = 0;
	int m_BombCountFrame = 0;
	int m_KnockBackFrame = 0;
	float m_KnockBackSpeed = 0;
	float m_ExplodeEffectSize = 0.0f;
	float m_Acceleration = ACCELERATION_BY_FRAME;

	CircleCollision m_Collision;
	CircleCollision m_AttackCollision;

};



#endif