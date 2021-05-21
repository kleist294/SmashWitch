#pragma once
#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

#include "d3dx9.h"
#include "Collision.h"
#include "TextureManager.h"
#include "Mouse.h"
#include "Model_x.h"


//      ����Ȃ�0�ɋ߂�
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

	D3DXVECTOR3 m_Front = { 0.0f,0.0f,-1.0f };//�v���C���̑O����
	D3DXVECTOR3 m_Left = { -1.0f,0.0f,0.0f };//�v���C���̍�����

	D3DXVECTOR3 m_TargetDir = m_Front; //�s����������
	float m_Acceleration = ACCELERATION_BY_FRAME;//�����x
	float m_Speed = 0.0f;//���݂̑��x
	float m_Shadowsize = 0.0f;//�e�̃T�C�Y
	float m_KnockBackSpeed = 0;//��΂���鑬�x
	bool m_IsChangingWeapon = false;//�����؂�ւ��Ă���
	bool m_IsAttacking = false;//�U�����Ă���
	bool m_IsMuteki = false;//���G���
	int m_MutekiFrame = 0;//���G����



	int m_HP;//�v���C���[��HP
	D3DXVECTOR3 m_PlayerPos;//�v���C���[�̍��W
	D3DXVECTOR3 m_SwordDir;
	float m_KnockBackFrame;//��΂��ꂽ�t���[����
	float m_AttackKnockBackSpeed;//�e��ԂōU�����Ă��鎞�̌�ރX�s�[�h

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