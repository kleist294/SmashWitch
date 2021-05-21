
/*==========================================================

�@�@�@�@�@�@�@�@�@�@�@�v���C���[�̓���

==========================================================*/


#include"Model_x.h"
#include "d3dx9.h"
#include "keylogger.h"
#include "GamePlayerBullet.h"
#include "shadow.h"
#include "GamePlayer.h"
#include "GamePlayerManager.h"
#include "Sound.h"
#include "MeshField.h"
#include "Collision.h"
#include "GameEnemyManager.h"
#include "GameHammer.h"
#include "GameBulletMode.h"
#include "GamePlayerHP.h"
#include "GameJudgement.h"
#include "Mouse.h"
#include "JudgementRay.h"
#include "GameFloor.h"









/*==========================================================
�@�@�@�@�@�@�@�v���C���[�̃R���X�g���N�^�[
==========================================================*/
CPlayer::CPlayer() 
{
	m_PlayerPos = { 0.0f,0.5f,0.0f };
	m_IsJumping = false;
	m_IsKnockBack = false;
	m_CanJump = false;
	m_KnockBackFrame = 0.0f;
	m_Gravity = 0.15f;
	m_AttackedType = 0;
	m_Collision.Center = m_PlayerPos;
	m_Collision.radius = 0.5f;
	m_SwordCollision.Center = m_PlayerPos;
	m_SwordCollision.radius = 1.0f;
	m_AttackFrame = 0;
}

CPlayer::~CPlayer()
{

}


void CPlayer::PlayerInit()
{
	m_PlayerPos = { 0.0f,0.775f,-8.0f };
	m_SwordDir = { 0.0f,0.0f,0.0f };
	m_Shadowsize = 0.4f;
	m_TargetDir = m_Front;
	m_IsJumping = false;
	m_IsKnockBack = false;
	m_IsSwordAttacking = false;
	m_IsChangingWeapon = false;
	m_IsAttacking = false;
	m_IsMuteki = false;
	m_MutekiFrame = 0;
	m_KnockBackFrame = 0.0f;
	m_Gravity = 0.15f;
	m_AttackedType = 0;
	m_Collision.Center = m_PlayerPos;
	m_Collision.radius = 0.5f;
	m_SwordCollision.Center = m_PlayerPos;
	m_SwordCollision.radius = 1.0f;
	m_AttackFrame = 0;
	m_AttackMode = 0;
	m_AttackKnockBackSpeed = 0.0f;
	m_HP = 3;

	m_XModelPlayer = GetModelMajo();
}





/*==========================================================
�@�@�@�@�@�@�@�v���C���[�̍s��
==========================================================*/
void CPlayer::PlayerMove()
{
	//�}�E�X��Ԃ̎擾
	Mouse_GetState(&m_Mouse);

	//�ǂ����ɉ�]���悤
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &m_Front, &m_TargetDir);
	float sign = Cross.y < 0.0f ? -1 : 1;

	float rotation = 0.2f * sign;

	//�ړI�̕����ƌ��݂̕����Ƃ̊p�x�̍����Z�o����
	//�p�x��                             �O�����ƌ����Ă�����̓���
	if (rotation >= 0.0f) {
		float direction_difference = acosf(min(D3DXVec3Dot(&m_Front, &m_TargetDir), 1.0f));
		if (rotation > direction_difference) {
			rotation = direction_difference;
		}
	}
	else if (rotation < 0.0f)
	{
		float direction_differenceR = -1 * acosf(min(D3DXVec3Dot(&m_Front, &m_TargetDir), 1.0f));
		if (rotation < direction_differenceR) {
			rotation = direction_differenceR;
		}
	}

	//�����𐳋K������
	D3DXMATRIX mtxR;
	D3DXMatrixRotationY(&mtxR, rotation);
	D3DXVec3TransformNormal(&m_Front, &m_Front, &mtxR);

	D3DXMatrixRotationY(&mtxR, D3DXToRadian(90));

	D3DXVec3TransformNormal(&m_Left, &m_Front, &mtxR);


	float Distance = 0.0f;

	if (JudgementRay_PlayerObject_Check(m_Front, 0.3f, &Distance))
	{
		m_Speed = 0.0f;
	}
	else if (JudgementRay_PlayerObject_Check(m_Left, 0.3f, &Distance))
	{
		m_Speed = 0.0f;
	}
	else if (JudgementRay_PlayerObject_Check(-m_Left, 0.3f, &Distance))
	{
		m_Speed = 0.0f;
	}


	//���W�̍X�V
	m_PlayerPos += m_Front * m_Speed;

	//���x�̌���
	m_Speed *= 0.8f;

	




	

	//�U�����Ă�����(�U���ɃN�[���_�E���t��)
	if(m_IsAttacking == true) {

		//�e�������ĂΌ��Ɉړ�
		if (m_AttackMode == 0)
		{
			PlayerAttackKnockBackAccelerate();
			
				if (!JudgementRay_PlayerObject_Check(-m_Front, 0.3f, &Distance))
				{
					m_PlayerPos -= m_Front * m_AttackKnockBackSpeed;
				}
		}


		if (m_AttackFrame >= 30)
		{
			m_AttackFrame = 0;
			m_IsAttacking = false;
		}
		if (m_AttackFrame >= 10)
		{
			
			m_IsSwordAttacking = false;
		}
		m_AttackFrame++;
		
		
	}
	
	m_AttackKnockBackSpeed * 0.9f;


	//�m�b�N�o�b�N���ꂽ��Ԃ̎���
	if (m_IsKnockBack == true)
	{
		PlayerKnockBackAccelerate();
		if (m_KnockBackFrame >= 30)
		{
			m_KnockBackFrame = 0;
			m_IsKnockBack = false;
			EndAttack();
		}

		m_KnockBackFrame++;
	}

	float FloorDistance = 0.0f;
	//�v���C���[��������W�����v���Ă��Ȃ����
	if (JudgementRay_PlayerGround_Check(1.5f, &FloorDistance))
	{
		m_KnockBackSpeed *= 0.8f;
	}
	//�v���C���[��������W�����v���Ă�����
	else if (JudgementRay_PlayerGround_Check(5.0f, &FloorDistance))
	{
		m_KnockBackSpeed *= 0.9f;
	}
	//�v���C���[����O�̏��
	else 
	{
		m_KnockBackSpeed *= 0.98f;
	}
	m_Collision.Center = m_PlayerPos;
	m_SwordCollision.Center = m_PlayerPos + m_Front * 0.5f;



	//�s�������疳�G��Ԃ�����
	//�}�E�X�̑���@���N���b�N�͍U���@�E�͕���ւ�
	if (KeyloggerTrigger(KL_ATTACK) || (m_Mouse.leftButton == true && m_IsAttacking == false))
	{
		PlayerAtack();
		m_IsMuteki = false;
	}

	if (KeyloggerTrigger(KL_WEAPONCHANGE) || (m_Mouse.rightButton == true && m_IsChangingWeapon == false))
	{
		WeaponChange();
		m_IsMuteki = false;
	}

	//���G���Ԃ̌v�Z
	if (m_IsMuteki == false)
	{
		m_MutekiFrame = 0;
	}
	else if (m_IsMuteki == true)
	{
		if (m_MutekiFrame >= 300)
		{
			m_IsMuteki = false;
		}
		m_MutekiFrame++;
	}

	

	//�E�N���b�N�g���K�[
	switch (m_Mouse.rightButton)
	{
	case true:
		m_IsChangingWeapon = true;
		break;
	case false:
		m_IsChangingWeapon = false;
		break;
	}


}



/*==========================================================
�@�@�@�@�@�@�@�v���C���[�̃W�����v�֐�
==========================================================*/
void CPlayer::PlayerJump()
{
	float FloorDistance = 0.0f;

	//�W�����v���Ă��邩�̔��f
	if (KeyloggerTrigger(KL_JUMP) && m_IsJumping == false && m_CanJump == true)
	{
			m_IsJumping = true;		
	}

	//�W�����v���Ă�����
	if (m_IsJumping == true) {
		
		m_PlayerPos.y += 0.225f;
		m_Gravity *= 1.01f;

		if (m_Gravity <= 0.225f){
			m_Shadowsize -= 0.01f;
			if (m_Shadowsize <= 0.1f)
			{
				m_Shadowsize = 0.1f;
			}
			
		}
		else if(m_Gravity > 0.225f)
		{
			m_Shadowsize += 0.01f;
			if (m_Shadowsize >= 0.4f)
			{
				m_Shadowsize = 0.4f;
			}
		}

		m_PlayerPos.y = m_PlayerPos.y - m_Gravity;



		if (JudgementRay_PlayerGround_Check(1.5f, &FloorDistance)) {
			PlaySound(SOUND_LABEL_SE_LANDING);
			m_PlayerPos.y = 0.725f + (m_PlayerPos.y + 0.725f - FloorDistance);
			m_IsJumping = false;
		}

	}
	//�W�������v���Ă��Ȃ����
	else if (m_IsJumping == false) {
	
			m_Gravity = 0.15f;
		
		if (JudgementRay_PlayerGround_Check(1.5f, &FloorDistance)) {
			m_PlayerPos.y = 0.725f + (m_PlayerPos.y + 0.725f - FloorDistance);
			m_CanJump = true;
		}
		else{
			m_PlayerPos.y -= m_Gravity;
			m_CanJump = false;
		}

		
	}

}
/*==========================================================
�@�@�@�@�v���C���[����������ہA���l�̌v�Z�ƃ��Z�b�g
==========================================================*/
void CPlayer::PlayerRespawn()
{
	m_PlayerPos = { 0.0f,2.5f,-8.0f };
	m_IsJumping = false;
	m_IsMuteki = true;
	m_Gravity = 0.15f;
	m_KnockBackSpeed = 0.0f;
}

/*==========================================================
�@�@�@�@�@�@�@�v���C���[���U�������Ԃ̔���
==========================================================*/
void CPlayer::PlayerAtack()
{
	if (m_IsAttacking == false) {
		switch (m_AttackMode) {
			case 0:
			GameBulletSpawn(m_PlayerPos.x + m_Front.x * 0.4f, m_PlayerPos.y - 0.245f, m_PlayerPos.z + m_Front.z * 0.4f);
			m_IsAttacking = true;
			break;

			case 1:
			m_IsSwordAttacking = true;
			m_IsAttacking = true;
			m_SwordDir = m_Front;
			break;
		}
	}
}

/*==========================================================
�@�@�@�@�@�@�@�v���C���[����̐؂�ւ�
==========================================================*/
void CPlayer::WeaponChange()
{
	if (m_AttackMode == 0 && m_IsAttacking == false)
	{
		m_AttackMode = 1;
		PlaySound(SOUND_LABEL_SE_CHANGEWEAPON);
	}
	else if (m_AttackMode == 1 && m_IsAttacking == false)
	{
		m_AttackMode = 0;
		PlaySound(SOUND_LABEL_SE_CHANGEWEAPON);
	}
}

/*==========================================================
�@�@�@�@�@�v���C���[����΂����ۂ̕����ƍU�������^�C�v
==========================================================*/
void CPlayer::PlayerKnockBack(D3DXVECTOR3 MoveDir,int AttackType)
{
	float Distance = 0.0f;
	MoveDir.y = 0.0f;
	D3DXVec3Normalize(&MoveDir, &MoveDir);
	if (!JudgementRay_PlayerObject_Check(-MoveDir, 0.5f, &Distance)) {
		m_PlayerPos -= MoveDir * m_KnockBackSpeed;
	}
	m_AttackedType = AttackType;
}

/*==========================================================
�@�@�@�@�@�v���C���[����΂����ۂ̑��x
==========================================================*/
void CPlayer::PlayerKnockBackAccelerate()
{
	if (m_AttackedType == 1) {
		m_KnockBackSpeed += m_Acceleration * 4;

		m_KnockBackSpeed = min(m_KnockBackSpeed, SPEED_MAX * 6);
	}
	if (m_AttackedType == 2) {
		m_KnockBackSpeed += m_Acceleration * 25;

	}
	if (m_AttackedType == 3) {
		m_KnockBackSpeed += m_Acceleration * 8;

		m_KnockBackSpeed = min(m_KnockBackSpeed, SPEED_MAX * 24);
	}
	if (m_AttackedType == 4) {
		m_KnockBackSpeed += m_Acceleration * 12;

	}


}

/*==========================================================
�@�@�@�@�@�v���C���[���U�����Ă���ۂ̔����X�s�[�h�i�e��ԁj
==========================================================*/
void CPlayer::PlayerAttackKnockBackAccelerate()
{

	if (m_AttackMode == 0) {
		m_AttackKnockBackSpeed += m_Acceleration * 2;

		m_AttackKnockBackSpeed = min(m_AttackKnockBackSpeed, SPEED_MAX * 2);
	}

}


/*==========================================================
�@�@�@�@�@�v���C���[�̕`��
==========================================================*/
void CPlayer::PlayerDraw()
{
	D3DXMATRIX mtxWorld, mtxW, mtxT, mtxS, mtxS1, mtxR, mtxRZ;
	float FloorDistance = 0.0f;
	D3DXMatrixScaling(&mtxS1, 1.0f, 1.0f, 1.0f);
	D3DXMatrixScaling(&mtxS, 0.0002f, 0.0002f, 0.0002f);
	D3DXMatrixTranslation(&mtxT, m_PlayerPos.x, m_PlayerPos.y - 0.25f, m_PlayerPos.z);
	D3DXMatrixRotationY(&mtxR, -atan2f(m_Front.z, m_Front.x) + D3DXToRadian(-90));




	mtxW = mtxS * mtxR * mtxT;
	mtxWorld = mtxS1 * mtxR * mtxT;
	if (JudgementRay_PlayerGround_Check(5.0f, &FloorDistance)) {
		ShadowDraw(m_PlayerPos.x, m_PlayerPos.y + 0.755f - FloorDistance, m_PlayerPos.z, m_Shadowsize);
	}
	Model_X_Draw(m_XModelPlayer, &mtxWorld);

	GameHammer_Draw();
	GameBulletMode_Draw();
}






/*==========================================================
�@�@�@�@�@�v���C���[�ŏI�̌����������߂�
==========================================================*/
void CPlayer::GamePlayerSetDir(const D3DXVECTOR3* pDir)
{
	if (D3DXVec3LengthSq(pDir) < INFINITESIMAL) {
		return;
	}

	m_TargetDir = *pDir;
}

/*==========================================================
�@�@�@�@�@�v���C���[�������ۂ̑��x
==========================================================*/
void CPlayer::GamePlayerAccelerate()
{
	//���x�̍X�V
	m_Speed += m_Acceleration;

	m_Speed = min(m_Speed, SPEED_MAX);
}


/*==========================================================
�@�@�@�@�@�v���C���[����΂���Ă������H
==========================================================*/
void CPlayer::KnockBack()
{
	m_IsKnockBack = true;
}


/*==========================================================
�@�@�@�@�@�v���C���[�̌������擾
==========================================================*/
D3DXVECTOR3 CPlayer::GetPlayerDir()
{
	return m_Front;
}

/*==========================================================
�@�@�@�@�@�v���C���[�̍��������擾
==========================================================*/
D3DXVECTOR3 CPlayer::GetPlayerLeft()
{
	return m_Left;
}

/*==========================================================
�@�@�@�@�@�v���C���[����̌���
==========================================================*/
D3DXVECTOR3 CPlayer::GetSwordDir()
{
	return m_SwordDir;
}

/*==========================================================
�@�@�@�@�@�v���C���[�̈ʒu�����擾
==========================================================*/
D3DXVECTOR3 CPlayer::GetPlayerPos()
{
	return m_PlayerPos;
}



/*==========================================================
�@�@�@�@�@�v���C���[�̓����蔻����擾
==========================================================*/
CircleCollision CPlayer::GetCollision()
{
	return m_Collision;
}



/*==========================================================
�@�@�@�@�@�v���C���[����̓����蔻����擾
==========================================================*/
CircleCollision CPlayer::GetSwordCollision()
{
	return m_SwordCollision;
}







/*==========================================================
�@�@�@�@�@�v���C���[���U�����Ă��邩�H�i�n���}�[��ԁj
==========================================================*/
bool CPlayer::GetSwordAttacking()
{
	return m_IsSwordAttacking;
}




/*==========================================================
�@�@�@�@�@�v���C���[���W�����v���Ă��邩�H
==========================================================*/
bool CPlayer::GetIsJumping()
{
	return m_IsJumping;
}


bool CPlayer::GetIsChangingWeapon()
{
	return m_IsChangingWeapon;
}
bool CPlayer::GetIsAttacking()
{
	return m_IsAttacking;
}
bool CPlayer::GetIsMuteki()
{
	return m_IsMuteki;
}


/*==========================================================
�@�@�@�@�@�v���C���[�������Ă��镐��̏����擾
==========================================================*/
int CPlayer::GetAttackMode()
{
	return m_AttackMode;
}




/*==========================================================
�@�@�@�@�@�v���C���[�͔�΂���Ă��邩�H
==========================================================*/
bool CPlayer::GetIsKnockBack()
{
	return m_IsKnockBack;
}


/*==========================================================
�@�@�@�@�@�v���C���[�̃��C�t�����擾
==========================================================*/
int CPlayer::GetHP()
{
	return m_HP;
}



/*==========================================================
�@�@�@�@�@�v���C���[�̃��C�t�����锻��
==========================================================*/
void CPlayer::HPLost()
{
	m_HP -= 1;
}


/*==========================================================
�@�@�@�@�@�v���C���[�̍U����~
==========================================================*/
void CPlayer::SetIsAttackStop()
{
	m_IsAttacking = true;
}
