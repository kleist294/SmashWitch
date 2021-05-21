/*============================================================

�@�@�@�@�@�@�@���e�̏��

============================================================*/

#include "Model_x.h"
#include "d3dx9.h"
#include "Collision.h"
#include "GameBomb.h"
#include "Shadow.h"
#include "DropEffect.h"
#include "GameParticleEmitter.h"
#include "Sound.h"
#include "JudgementRay.h"

/*============================================================
�@�@�@�@�@�@�@���e�̃R���X�g���N�^�[
============================================================*/
Bomb::Bomb()
{
	m_BombPos = {0.0f,0.0f,0.0f};
	m_IsEnable = false;
	m_IsKnockBack = false;
	m_IsAttacked = false;
	m_IsExplode = false;
	m_IsDrop = false;
	m_AttackedType = 0;
	m_BombCountFrame = 0;
	m_KnockBackFrame = 0;
	m_KnockBackSpeed = 0;
	m_Acceleration = ACCELERATION_BY_FRAME;

	m_Collision.Center = m_BombPos;
	m_Collision.radius = 0.6f;
	m_AttackCollision.Center = m_BombPos;
	m_AttackCollision.radius = 6.25f;

}
Bomb::~Bomb()
{


}



/*============================================================
�@�@�@�@�@�@�@���e�̕`��
============================================================*/
void Bomb::BombDraw()
{
	D3DXMATRIX mtxW, mtxT, mtxS;

	D3DXMatrixScaling(&mtxS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&mtxT, m_BombPos.x, m_BombPos.y, m_BombPos.z);




	mtxW = mtxT;

	if (m_IsEnable == true) {
		Model_X_Draw(m_BombModelID, &mtxW);
	}
	if (m_IsExplode == true) {
		DropEffect_SetColor(D3DCOLOR_RGBA(255,140,105, 255));
		DropEffect_Draw(m_BombPos.x, m_BombPos.y - 0.2f, m_BombPos.z, m_ExplodeEffectSize);
		DropEffect_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

/*============================================================
�@�@�@�@�@�@�@���e�̐���
============================================================*/
void Bomb::BombSpawn(D3DXVECTOR3 Pos)
{

	m_BombPos = Pos;
	m_IsEnable = true;
	m_IsKnockBack = false;
	m_IsAttacked = false;
	m_IsExplode = false;
	m_IsDrop = false;
	m_AttackedType = 0;
	m_BombCountFrame = 0;
	m_KnockBackFrame = 0;
	m_KnockBackSpeed = 0;


	m_Collision.Center = m_BombPos;
	m_Collision.radius = 0.6f;
	m_AttackCollision.Center = m_BombPos;
	m_AttackCollision.radius = 6.25f;
	BombCounting(1);

}

/*============================================================
�@�@�@�@�@�@�@���e�̏��
============================================================*/
void Bomb::BombStatus()
{

	float FloorDistance = 0.0f;

	if (m_IsKnockBack == true) {
		m_IsAttacked = true;
		BombKnockBackAccelerate();

		if (m_KnockBackFrame >= 30)
		{
			m_KnockBackFrame = 0;
			m_IsKnockBack = false;
			m_IsAttacked = false;
		}

		m_KnockBackFrame++;
	}

	m_KnockBackSpeed *= 0.825f;

	if (m_IsExplode == true) {
		if (m_ExplodeEffectSize <= 12.0f)
			m_ExplodeEffectSize += 0.5f;
		else
		{
			m_ExplodeEffectSize += 0.05f;
		}

		if (m_ExplodeEffectSize >= 12.5f)
		{

			//m_IsEnable = false;
			m_BombCountFrame = 0;
			m_ExplodeEffectSize = 0;
			m_IsExplode = false;
		}

	}
	if (JudgementRay_ObjectGround_Check(m_BombPos, 1.5f, &FloorDistance, BOMB))
	{
		m_BombCountFrame++;
		if (m_IsDrop == false) {
			PlaySound(SOUND_LABEL_SE_BOMBDROP);
			m_IsDrop = true;
		}
	}

	
	if (m_BombPos.y <= -10.0f)
	{
		BombExplode();
	}


	if (m_IsEnable == true)
	{
		float gravity = 0.15f;

		if (JudgementRay_ObjectGround_Check(m_BombPos, 1.5f, &FloorDistance, BOMB)) {
			//PlaySound(SOUND_LABEL_SE_LANDING);
			m_BombPos.y = 0.5f + (m_BombPos.y + 0.5f - FloorDistance);
		}
		else {
			m_BombPos.y -= gravity;
		}



	}
	else
	{
		m_KnockBackSpeed = 0.0f;
	}

	m_Collision.Center = m_BombPos;
	m_AttackCollision.Center = m_BombPos;

}

/*============================================================
�@�@�@�@�@�@�@���e�𔚔�������s��
============================================================*/
void Bomb::BombExplode()
{
	if (m_IsEnable == true) {
		m_IsEnable = false;
		BombCounting(0);
		m_IsExplode = true;
		m_IsDrop = false;
		for (int i = 0; i < 20; i++) {
			float RandomSize = (float)(rand() % 50 + 100) / 1000;
			float RandomSpeed = (float)(rand() % 10 + 25) / 100;
			GameParticleEmitter_Spawn({ m_BombPos.x, m_BombPos.y,m_BombPos.z }, 1, RandomSize, RandomSpeed);
		}
		PlaySound(SOUND_LABEL_SE_BOMBEXPLODE);
	}
}

/*============================================================
�@�@�@�@�@�@�@���e����΂��������ƍU�����ꂽ�^�C�v
============================================================*/
void Bomb::BombKnockBack(D3DXVECTOR3 MoveDir, int AttackType)
{
	float Distance = 0.0f;
	MoveDir.y = 0.0f;
	D3DXVec3Normalize(&MoveDir, &MoveDir);
	if (!JudgementRay_ObjectAndObject_Check(m_BombPos, -MoveDir, 0.6, &Distance, BOMB)) {
	m_BombPos -= MoveDir * m_KnockBackSpeed;
	}
	m_AttackedType = AttackType;
}

/*============================================================
�@�@�@�@�@�@�@���e����΂����ۂ̑��x
============================================================*/
void Bomb::BombKnockBackAccelerate()
{
	if (m_AttackedType == 1) {
		m_KnockBackSpeed += m_Acceleration * 8;

	}
	if (m_AttackedType == 2) {
		m_KnockBackSpeed += m_Acceleration * 25;
	}
}

/*============================================================
�@�@�@�@�@�@�@���e���΂�
============================================================*/
void Bomb::BombKnockBackEnable()
{
	m_IsKnockBack = true;
}

/*============================================================
�@�@�@�@�@�@�@���e����΂���Ă��邩�H
============================================================*/
bool Bomb::GetIsKnockBack()
{
	return m_IsKnockBack;
}

/*============================================================
�@�@�@�@�@�@�@���e�����݂��Ă��邩�H
============================================================*/
bool Bomb::GetBombIsEnable()
{
	return m_IsEnable;
}
/*============================================================
�@�@�@�@�@�@�@���e���������Ă��邩�H
============================================================*/
bool Bomb::GetBombIsExplode()
{
	return m_IsExplode;
}

/*============================================================
�@�@�@�@�@�@�@���e�̓����蔻��̎擾
============================================================*/
CircleCollision Bomb::GetCollision()
{
	return m_Collision;
}

/*============================================================
�@�@�@�@�@�@�@���e�̔����͈�
============================================================*/
CircleCollision Bomb::GetAttackZone()
{
	return m_AttackCollision;
}
