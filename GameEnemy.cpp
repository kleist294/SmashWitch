

/*============================================================

　　　　　　　敵の状態

============================================================*/




#include "Model_x.h"
#include "d3dx9.h"
#include "Keylogger.h"
#include "Shadow.h"
#include "GameEnemy.h"
#include "Sound.h"
#include "Cube.h"
#include "Camera.h"
#include "MeshField.h"
#include "Collision.h"
#include "DropEffect.h"
#include "GameEnemyManager.h"
#include "GameBikuri.h"
#include "TextureManager.h"
#include "Score.h"
#include "JudgementRay.h"



CEnemy::CEnemy()
{
	
}

CEnemy::~CEnemy()
{

}


CEnemy *CEnemy::Create()
{
	CEnemy *pEnemy = NULL;	
	pEnemy = new CEnemy;

	return pEnemy;

}

/*============================================================
　　　　　　　敵の生成
============================================================*/
void CEnemy::EnemySpawn(D3DXVECTOR3 Pos,int Enemym_Type)
{
	m_Type = Enemym_Type;

	switch (m_Type) 
	{
	case ENEMY_RUNNING:
	m_IsEnable = false;
	m_IsLockOn = false;
	m_IsTouch = false;
	m_IsAttacked = false;
	m_IsAttacking = false;
	m_IsCoolDown = false;
	m_IsDrop = false;
	m_IsKnockBack = false;
	m_IsBikuri = false;
	m_CanJump = false;
	m_Enemypos = Pos;
	m_MovementFrame = 0;
	m_AttackFrame = 0;
	m_AttackCoolDownFrame = 0;
	m_KnockBackFrame = 0;
	m_Gravity = 1.0f;
	m_RandomDirFrame = 0;
	m_EnemyRandomDir = { 0.0f,0.0f,0.0f };
	m_AttackedType = 0;
	m_Collision.Center = m_Enemypos;
	m_LockOnZone.Center = m_Enemypos;
	m_Collision.radius = 0.5f;
	m_LockOnZone.radius = 5.0f;
	m_ShadowSize = 0.5f;
	m_AttackCollision.Center = m_Enemypos + m_Front * 0.3f;
	m_AttackCollision.radius = 0.5f;
	m_XModelEnemy = GetModelGhost();
		break;
	case ENEMY_JUMPING:
		m_IsEnable = false;
		m_IsAttacked = false;
		m_IsAttacking = false;
		m_IsDrop = false;
		m_IsKnockBack = false;
		m_IsJumping = false;
		m_IsBikuri = false;
		m_Enemypos = Pos;
		m_MovementFrame = 0;
		m_AttackFrame = 0;
		m_DropAnimationFrame = 0;
		m_KnockBackFrame = 0;
		m_Gravity = 1.0f;
		m_DropEffectSize = 0.0f;
		m_RandomDirFrame = 0;
		m_EnemyRandomDir = { 0.0f,0.0f,0.0f };
		m_AttackedType = 0;
		m_Collision.Center = m_Enemypos;
		m_Collision.radius = 0.6f;
		m_ShadowSize = 0.5f;
		m_AttackCollision.Center = m_Enemypos;
		m_AttackCollision.radius = 2.5f;
		m_XModelEnemy = GetModelSlime();
		break;
	case ENEMY_BOSS1:
		break;
	}
}
void CEnemy::EnemyEnable()
{
	m_IsEnable = true;
}

/*============================================================
　　　　　　　敵の動き（向き）
============================================================*/
void CEnemy::EnemyMoveMent(D3DXVECTOR3 MoveDir)
{
	
	//移動を乱数で決める
	if (m_RandomDirFrame >= 240)
	{
		m_EnemyRandomDir = { (float)(rand() % 21 - 10),0.0f,(float)(rand() % 21 - 10) };
		m_RandomDirFrame = 0;
	}




	D3DXVECTOR3 EnemyDir = { 0.0f,0.0f,0.0f };

	EnemyDir = MoveDir;

	//攻撃していなければ移動
	if ((m_IsTouch == false || m_Type == 1) && m_IsAttacked == false) {
		GameEnemyAccelerate();
	}


	//敵の向きを決める
	GameEnemySetDir(D3DXVec3Normalize(&EnemyDir, &EnemyDir));



	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &m_Front, &m_TargetDir);
	float sign = cross.y < 0.0f ? -1 : 1;

	float rotation = 0.2f * sign;

	float rotate = D3DXVec3Dot(&m_Front, &m_TargetDir);

	if (rotate >= 1.0f)
	{
		rotate = 1.0f;
	}
	else if (rotate <= 0.0f)
	{
		rotate = 0.0f;
	}



	
	
		float direction_difference = acosf(rotate);

		if (rotation > direction_difference) {
			rotation = 0.0f;
			direction_difference = 0.0f;
		}
	


	D3DXMATRIX mtxR;
	D3DXMatrixRotationY(&mtxR, rotation);
	D3DXVec3TransformNormal(&m_Front, &m_Front, &mtxR);

	EnemyMove();
	GameEnemyJump();


	m_Collision.Center = m_Enemypos;
	m_LockOnZone.Center = m_Enemypos;

	if (m_Enemypos.y <= -15.0f)
	{
		m_IsEnable = false;
	}


	if (m_IsCoolDown == true)
	{
		if (m_AttackCoolDownFrame >= 60)
		{
			m_AttackCoolDownFrame = 0;
			m_IsCoolDown = false;
		}
		m_AttackCoolDownFrame++;
	}

	//落下攻撃
	if (m_IsDrop == true)
	{

		m_DropEffectSize += 0.1f;

		
		if (m_DropAnimationFrame >= 35) 
		{
			m_DropEffectSize = 0.0f;
			m_DropAnimationFrame = 0;
			m_IsDrop = false;
		}		
		m_DropAnimationFrame++;
	}

	//敵の攻撃にクールダウン付加
	if (m_IsAttacking == true)
	{
		
		switch (m_Type)
		{
		case ENEMY_RUNNING:
			if (m_AttackFrame >= 3) {
				m_IsAttacking = false;
				m_AttackFrame = 0;
				m_IsCoolDown = true;
			}
			break;
		case ENEMY_JUMPING:
			if (m_AttackFrame >= 3) {
				m_IsAttacking = false;
				m_AttackFrame = 0;
				
			}
			break;

		}


		m_AttackFrame++;
	}
	m_MovementFrame++;
	m_RandomDirFrame++;
}

/*============================================================
　　　　　　　敵の動き（行動）
============================================================*/
void CEnemy::EnemyMove()
{
	float FloorDistance = 0.0f;
	float Distance = 0.0f;
	//座標の更新
	if (m_IsLockOn == false) {

		if(!JudgementRay_ObjectAndObject_Check(m_Enemypos, m_Front, 0.8f, &Distance, ENEMY_SLIME)|| m_Type == ENEMY_RUNNING)
		m_Enemypos += m_Front * m_Speed * 1.0f;
	}
	if (m_IsLockOn == true)
	m_Enemypos += m_Front * m_Speed * 2.0f;
	//速度の減衰
	m_Speed *= 0.8f;

	if (m_IsKnockBack == true)
	{
		m_IsAttacked = true;
		GameEnemyKnockBackAccelerate();

		if (m_KnockBackFrame >= 30)
		{
			m_KnockBackFrame = 0;
			
				m_IsKnockBack = false;
				m_IsAttacked = false;
			
		}

		m_KnockBackFrame++;
	}
	m_KnockBackSpeed *= 0.825f;
	
	//飛ばされていない状態では崖を回避
	if (m_IsKnockBack == false)
	{
		switch (m_Type)
		{
		case ENEMY_RUNNING:

			if (!JudgementRay_ObjectGround_Check(m_Enemypos + (m_Front * 2.0f), 1.5f, &FloorDistance, ENEMY_GHOST))
			{
				m_EnemyRandomDir = - m_Front;
				m_RandomDirFrame = 0;
				m_MovementFrame = 0;
			}
			break;
		case ENEMY_JUMPING:

			if (!JudgementRay_ObjectGround_Check(m_Enemypos + (m_Front * 2.0f), 2.5f, &FloorDistance, ENEMY_SLIME))
			{
				m_EnemyRandomDir = - m_Front;
				m_RandomDirFrame = 0;
				m_MovementFrame = 0;
			}
			break;


		}
		
	}

	if (m_Enemypos.y <= -10.0f)
	{
		m_IsEnable = false;

		
		switch (m_Type)
		{
		case ENEMY_RUNNING:
			GameScore_AddScore(30);
			break;
		case ENEMY_JUMPING:
			GameScore_AddScore(50);
			break;

		}
		

		DeadAddEnemyCount();
	}

}

/*============================================================
　　　　　　　敵が飛ばされる際の方向と攻撃されたタイプ
============================================================*/
void CEnemy::GameEnemyKnockBack(D3DXVECTOR3 MoveDir,int AttackType)
{
	float Distance = 0.0f;
	MoveDir.y = 0.0f;
	D3DXVec3Normalize(&MoveDir, &MoveDir);
	if (m_IsEnable == true) {
		if (!JudgementRay_ObjectAndObject_Check(m_Enemypos, -MoveDir, 0.8f, &Distance, ENEMY_SLIME) || m_Type == ENEMY_RUNNING)
		{
			m_Enemypos -= MoveDir * m_KnockBackSpeed;
		}
	}
	m_AttackedType = AttackType;

}

/*============================================================
　　　　　　　敵が飛ばされる際の速度
============================================================*/
void CEnemy::GameEnemyKnockBackAccelerate()
{

	if (m_AttackedType == 1) {
		m_KnockBackSpeed += m_Acceleration * 5;

	}

	if (m_AttackedType == 2) {
		m_KnockBackSpeed += m_Acceleration * 10;

	}


	if (m_AttackedType == 3) {
		m_KnockBackSpeed += m_Acceleration * 0.5;

	}
}

/*============================================================
　　　　　　　敵の移動速度
============================================================*/
void CEnemy::GameEnemyAccelerate()
{
	m_Speed += m_Acceleration;

	m_Speed = min(m_Speed, SPEED_MAX);
}

/*============================================================
　　　　　　　敵最終の向き方向
============================================================*/
void CEnemy::GameEnemySetDir(const D3DXVECTOR3* pDir)
{
	if (D3DXVec3LengthSq(pDir) < INFINITESIMAL) {
		return;
	}

	m_TargetDir = *pDir;

}

/*============================================================
　　　　　　　敵のジャンプの状態
============================================================*/
void CEnemy::GameEnemyJump()
{
	float FloorDistance = 0.0f;

	if ( m_MovementFrame >= 180 && m_Type == 1 && m_CanJump == true)
	{

		if (m_IsJumping == false) {
			m_IsJumping = true;
		}
		m_MovementFrame = 0;
	}

	if (m_IsJumping == true) {

		m_Enemypos.y += 0.225f;

		m_Gravity *= 1.01f;

		if (m_Gravity <= 0.225f) {
			m_ShadowSize -= 0.01f;
			if (m_ShadowSize <= 0.1f)
			{
				m_ShadowSize = 0.1f;
			}
		
		}
		else if (m_Gravity > 0.225f)
		{
			m_ShadowSize += 0.01f;
			if (m_ShadowSize >= 0.5f)
			{
				m_ShadowSize = 0.5f;
			}
		}

		m_Enemypos.y = m_Enemypos.y - m_Gravity;



		if (JudgementRay_ObjectGround_Check(m_Enemypos, 1.05f, &FloorDistance, ENEMY_SLIME)) {
		//	PlaySound(SOUND_LABEL_SE_LANDING);
			EnemyAtack();
			m_Enemypos.y = 0.5f + (m_Enemypos.y + 0.5f - FloorDistance);
			m_IsDrop = true;
			m_IsJumping = false;
		}

	}
	else if (m_IsJumping == false) {

		m_Gravity = 0.15f;

		switch (m_Type)
		{
		case ENEMY_RUNNING:
			if (JudgementRay_ObjectGround_Check(m_Enemypos,1.5f, &FloorDistance, ENEMY_GHOST)) {
				//PlaySound(SOUND_LABEL_SE_LANDING);
				m_Enemypos.y = 0.5f +(m_Enemypos.y + 0.5f - FloorDistance);
			}
			else {
				m_Enemypos.y -= m_Gravity;
			}
			break;
		case ENEMY_JUMPING:
			if (JudgementRay_ObjectGround_Check(m_Enemypos, 1.5f, &FloorDistance, ENEMY_SLIME)) {
				//PlaySound(SOUND_LABEL_SE_LANDING);
				m_Enemypos.y = 0.5f +(m_Enemypos.y + 0.5f - FloorDistance);
				m_CanJump = true;
			}
			else {
				m_Enemypos.y -= m_Gravity;
				m_CanJump = false;
			}
			break;
		}
		
	}
}



/*============================================================
　　　　　　　敵が攻撃している状態
============================================================*/
void CEnemy::EnemyAtack()
{
	if(m_IsCoolDown == false)
	m_IsAttacking = true;
	
	switch (m_Type)
	{
	case 0:
		m_AttackCollision.Center = m_Enemypos + m_Front * 0.3f;
		m_AttackCollision.radius = 0.5f;
		break;
	case 1:
		m_AttackCollision.Center = m_Enemypos;
		m_AttackCollision.radius = 1.5f;
		break;

	}
}

/*============================================================
　　　　　　　敵がプレイヤーをロックオンしている
============================================================*/
void CEnemy::EnemyLockOn()
{
	if (m_IsLockOn == false)
	{
		PlaySound(SOUND_LABEL_SE_LOCKON);
		
		GameBikuri_Spawn();
	}
	m_IsLockOn = true;
}

/*============================================================
　　　　　　　敵がロックオンを解除する
============================================================*/
void CEnemy::EnemyNotLockOn()
{
	m_IsLockOn = false;
}

/*============================================================
　　　　　　　敵の描画
============================================================*/
void CEnemy::EnemyDraw()
{
	D3DXMATRIX mtxWorld, mtxW, mtxT, mtxS, mtxS1, mtxR, mtxRZ;
	float FloorDistance = 0.0f;
	D3DXMatrixScaling(&mtxS1, 0.8f, 0.8f, 0.8f);
	D3DXMatrixScaling(&mtxS, 1.75f, 1.75f, 1.75f);
	D3DXMatrixTranslation(&mtxT, m_Enemypos.x, m_Enemypos.y, m_Enemypos.z);
	D3DXMatrixRotationY(&mtxR, -atan2f(m_Front.z, m_Front.x) + D3DXToRadian(-90));
	

	mtxW = mtxS * mtxR * mtxT;
	mtxWorld = mtxS1 * mtxR * mtxT;

	if (JudgementRay_ObjectGround_Check(m_Enemypos,5.0f, &FloorDistance, ENEMY_GHOST))
	ShadowDraw(m_Enemypos.x, m_Enemypos.y + 0.5f - FloorDistance, m_Enemypos.z, m_ShadowSize);
	
	if(m_IsDrop == true && JudgementRay_ObjectGround_Check(m_Enemypos, 5.0f, &FloorDistance, ENEMY_SLIME))
	DropEffect_Draw(m_Enemypos.x, m_Enemypos.y + 0.5f - FloorDistance, m_Enemypos.z, m_DropEffectSize);

	

	switch (m_Type)
	{
	case ENEMY_RUNNING:
		Model_X_Draw(m_XModelEnemy, &mtxWorld);
		break;
	case ENEMY_JUMPING:
		Model_X_Draw(m_XModelEnemy, &mtxW);
		break;

	}
	if (m_IsLockOn == true && m_IsBikuri == false)
		GameBikuri_Draw(m_Enemypos.x, m_Enemypos.y + 1.0f, m_Enemypos.z);
	
	
}

/*============================================================
　　　　　　　敵の位置を取得
============================================================*/
D3DXVECTOR3 CEnemy::GetEnemyPos() 
{
	return m_Enemypos;
}


D3DXVECTOR3 CEnemy::GetEnemyRandomDir()
{
	return m_EnemyRandomDir;
}


/*============================================================
　　　　　　　敵の向き方向を取得
============================================================*/
D3DXVECTOR3 CEnemy::GetEnemyDir()
{
	return m_Front;
}

/*============================================================
　　　　　　　敵が存在しているか？
============================================================*/
bool CEnemy::GetEnemyEnable()
{
	return m_IsEnable;
}

/*============================================================
　　　　　　　敵が攻撃しているか？
============================================================*/
bool CEnemy::GetIsAttack()
{
	return m_IsAttacking;
}

/*============================================================
　　　　　　　敵がロックオンしているか？
============================================================*/
bool CEnemy::GetEnemyLockOn()
{
	return m_IsLockOn;
}

/*============================================================
　　　　　　　敵をノックバック状態にする
============================================================*/
void CEnemy::EnemyKnockBack()
{
	m_IsKnockBack = true;
}

/*============================================================
　　　　　　　敵がノックバックされているか？
============================================================*/
bool CEnemy::GetIsKnockBack()
{
	return m_IsKnockBack;
}

/*============================================================
　　　　　　　敵がプレイヤーを当たっているか？
============================================================*/
void CEnemy::PlayerIsTouch(int touch)
{
	if (touch == 0)
	{
		m_IsTouch = false;
	}
	else
	{
		m_IsTouch = true;
		if(m_Type == 0)
		EnemyAtack();
	}
}

void CEnemy::EnemyBikuri()
{
	//m_IsBikuri = true;
}

/*============================================================
　　　　　　　敵のタイプを取得する
============================================================*/
int CEnemy::GetEnemyType()
{
	return m_Type;
}

/*============================================================
　　　　　　　敵の当たり判定を取得する
============================================================*/
CircleCollision CEnemy::GetCollision()
{
	return m_Collision;
}

/*============================================================
　　　　　　　敵の索敵範囲を取得する
============================================================*/
CircleCollision CEnemy::GetLockOnZone()
{
	return m_LockOnZone;
}

/*============================================================
　　　　　　　敵の攻撃範囲を取得する
============================================================*/
CircleCollision CEnemy::GetAttackZone()
{
	return m_AttackCollision;
}