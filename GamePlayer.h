#pragma once
#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "d3dx9.h"
#include "Collision.h"
#include "TextureManager.h"
#include "Mouse.h"
#include "Model_x.h"


//      限りなく0に近い
#define INFINITESIMAL 0.001f

#define ROTATION_SPEED (0.01f)
#define ACCELERATION_BY_FRAME 0.01f
#define SPEED_MAX 1.0f / 15

class CPlayer {

public:

	CPlayer();
	~CPlayer();

	void PlayerInit();
	void PlayerMove();
	void PlayerAtack();
	void PlayerDraw();
	void PlayerJump();
	void PlayerRespawn();
	void PlayerKnockBack(D3DXVECTOR3 MoveDir, int AttackType);
	void PlayerKnockBackAccelerate();
	void PlayerAttackKnockBackAccelerate();
	void GamePlayerSetDir(const D3DXVECTOR3* pDir);
	void GamePlayerAccelerate();
	void KnockBack();
	void WeaponChange();
	void HPLost();
	void SetIsAttackStop();
	bool GetSwordAttacking();
	bool GetIsKnockBack();
	bool GetIsJumping();
	bool GetIsChangingWeapon();
	bool GetIsAttacking();
	bool GetIsMuteki();
	int GetAttackMode();
	int GetHP();
	D3DXVECTOR3 GetPlayerDir();
	D3DXVECTOR3 GetPlayerLeft();
	D3DXVECTOR3 GetPlayerPos();
	D3DXVECTOR3 GetSwordDir();
	CircleCollision GetCollision();
	CircleCollision GetSwordCollision();


private:

	Mouse_State m_Mouse;

	D3DXVECTOR3 m_Front = { 0.0f,0.0f,-1.0f };//プレイヤの前方向
	D3DXVECTOR3 m_Left = { -1.0f,0.0f,0.0f };//プレイヤの左方向

	D3DXVECTOR3 m_TargetDir = m_Front; //行きたい方向
	float m_Acceleration = ACCELERATION_BY_FRAME;//加速度
	float m_Speed = 0.0f;//現在の速度
	float m_Shadowsize = 0.0f;//影のサイズ
	float m_KnockBackSpeed = 0;//飛ばされる速度
	bool m_IsChangingWeapon = false;//武器を切り替えている
	bool m_IsAttacking = false;//攻撃している
	bool m_IsMuteki = false;//無敵状態
	int m_MutekiFrame = 0;//無敵時間



	int m_HP;//プレイヤーのHP
	D3DXVECTOR3 m_PlayerPos;//プレイヤーの座標
	D3DXVECTOR3 m_SwordDir;
	float m_KnockBackFrame;//飛ばされたフレーム数
	float m_AttackKnockBackSpeed;//弾状態で攻撃している時の後退スピード

	int m_XModelPlayer = INVALID_MODEL_X_ID;

	bool m_IsJumping;
	bool m_CanJump;
	float m_Gravity;
	bool m_IsKnockBack;
	bool m_IsSwordAttacking;
	int m_AttackedType;
	int m_AttackFrame;
	int m_AttackMode;

	CircleCollision m_Collision;
	CircleCollision m_SwordCollision;
};





#endif