#pragma once

#ifndef GAME_ENEMY_H_
#define GAME_ENEMY_H_

#include "d3dx9.h"
#include "Collision.h"
#include "TextureManager.h"
#include "Model_x.h"
#include "MeshField.h"

#define INFINITESIMAL 0.001f
#define ACCELERATION_BY_FRAME 0.01f
#define SPEED_MAX 1.0f / 30
#define EDGE_X ((float)(MESH_X * MESHSIZE / 2) + 0.5f)
#define EDGE_Z ((float)(MESH_Z * MESHSIZE / 2) + 0.5f)

typedef enum
{
	ENEMY_RUNNING,
	ENEMY_JUMPING,
	ENEMY_BOSS1,
	ENEMY_MAX

}EnemyType;

class CEnemy {

public:

	CEnemy();
	~CEnemy();
	

	static CEnemy *Create();



	void EnemyMoveMent(D3DXVECTOR3 MoveDir);
	void EnemyMove();
	void EnemyAtack();
	void EnemyDraw();
	void EnemyLockOn();
	void EnemyNotLockOn();
	void EnemySpawn(D3DXVECTOR3 Pos, int EnemyType);
	void EnemyEnable();
	void GameEnemySetDir(const D3DXVECTOR3* pDir);
	void GameEnemyAccelerate();
	void GameEnemyKnockBack(D3DXVECTOR3 MoveDir, int AttackType);
	void GameEnemyKnockBackAccelerate();
	void GameEnemyJump();
	void EnemyKnockBack();


	D3DXVECTOR3 GetEnemyPos();
	D3DXVECTOR3 GetEnemyRandomDir();
	D3DXVECTOR3 GetEnemyDir();
	bool GetEnemyEnable();
	bool GetEnemyLockOn();
	bool GetIsAttack();
	bool GetIsKnockBack();
	int GetEnemyType();
	CircleCollision GetCollision();
	CircleCollision GetLockOnZone();
	CircleCollision GetAttackZone();

	void PlayerIsTouch(int touch);
	void EnemyBikuri();
	
private:

	

	int m_XModelEnemy = INVALID_MODEL_X_ID;
	
	


	D3DXVECTOR3 m_Enemypos;
	bool m_IsEnable = false;    
	bool m_IsLockOn = false;  
	bool m_IsTouch = false;     
	bool m_IsAttacked = false;
	bool m_IsAttacking = false;
	bool m_IsCoolDown = false;
	bool m_IsDrop = false;
	bool m_IsKnockBack = false;
	bool m_IsJumping = false;
	bool m_IsBikuri = false;
	bool m_CanJump = false;
	float m_Acceleration = ACCELERATION_BY_FRAME;
	float m_KnockBackSpeed = 0.0f;
	float m_KnockBackFrame;
	float m_Speed = 0.0f;
	D3DXVECTOR3 m_Front = { 0.0f,0.0f,-1.0f };
	D3DXVECTOR3 m_EnemyRandomDir = { 0.0f,0.0f,0.0f };;
	D3DXVECTOR3 m_TargetDir = m_Front;
	int m_MovementFrame = 0;
	int m_RandomDirFrame = 0;
	int m_AttackFrame = 0;
	int m_AttackCoolDownFrame = 0;
	int m_DropAnimationFrame = 0;
	int m_Type = 0;
	int m_AttackedType = 0;
	float m_Gravity = 1.0f;
	float m_DropEffectSize = 0.0f;
	float m_ShadowSize = 0.0f;
	

	CircleCollision m_Collision;
	CircleCollision m_LockOnZone;
	CircleCollision m_AttackCollision;
};

#endif