
/*==========================================================

　　　　　　　　　　　プレイヤーの動き

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
　　　　　　　プレイヤーのコンストラクター
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
　　　　　　　プレイヤーの行動
==========================================================*/
void CPlayer::PlayerMove()
{
	//マウス状態の取得
	Mouse_GetState(&m_Mouse);

	//どっちに回転しよう
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &m_Front, &m_TargetDir);
	float sign = Cross.y < 0.0f ? -1 : 1;

	float rotation = 0.2f * sign;

	//目的の方向と現在の方向との角度の差を算出する
	//角度差                             前方向と向いてる方向の内積
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

	//方向を正規化する
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


	//座標の更新
	m_PlayerPos += m_Front * m_Speed;

	//速度の減衰
	m_Speed *= 0.8f;

	




	

	//攻撃している状態(攻撃にクールダウン付加)
	if(m_IsAttacking == true) {

		//弾を撃ってば後ろに移動
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


	//ノックバックされた状態の時間
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
	//プレイヤーが場内且つジャンプしていない状態
	if (JudgementRay_PlayerGround_Check(1.5f, &FloorDistance))
	{
		m_KnockBackSpeed *= 0.8f;
	}
	//プレイヤーが場内且つジャンプしている状態
	else if (JudgementRay_PlayerGround_Check(5.0f, &FloorDistance))
	{
		m_KnockBackSpeed *= 0.9f;
	}
	//プレイヤーが場外の状態
	else 
	{
		m_KnockBackSpeed *= 0.98f;
	}
	m_Collision.Center = m_PlayerPos;
	m_SwordCollision.Center = m_PlayerPos + m_Front * 0.5f;



	//行動したら無敵状態が解除
	//マウスの操作　左クリックは攻撃　右は武器替え
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

	//無敵時間の計算
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

	

	//右クリックトリガー
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
　　　　　　　プレイヤーのジャンプ関数
==========================================================*/
void CPlayer::PlayerJump()
{
	float FloorDistance = 0.0f;

	//ジャンプしているかの判断
	if (KeyloggerTrigger(KL_JUMP) && m_IsJumping == false && m_CanJump == true)
	{
			m_IsJumping = true;		
	}

	//ジャンプしている状態
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
	//ジャンンプしていない状態
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
　　　　プレイヤーが復活する際、数値の計算とリセット
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
　　　　　　　プレイヤーが攻撃する状態の判定
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
　　　　　　　プレイヤー武器の切り替え
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
　　　　　プレイヤーが飛ばされる際の方向と攻撃されるタイプ
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
　　　　　プレイヤーが飛ばされる際の速度
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
　　　　　プレイヤーが攻撃している際の反動スピード（弾状態）
==========================================================*/
void CPlayer::PlayerAttackKnockBackAccelerate()
{

	if (m_AttackMode == 0) {
		m_AttackKnockBackSpeed += m_Acceleration * 2;

		m_AttackKnockBackSpeed = min(m_AttackKnockBackSpeed, SPEED_MAX * 2);
	}

}


/*==========================================================
　　　　　プレイヤーの描画
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
　　　　　プレイヤー最終の向き方を決める
==========================================================*/
void CPlayer::GamePlayerSetDir(const D3DXVECTOR3* pDir)
{
	if (D3DXVec3LengthSq(pDir) < INFINITESIMAL) {
		return;
	}

	m_TargetDir = *pDir;
}

/*==========================================================
　　　　　プレイヤーが動く際の速度
==========================================================*/
void CPlayer::GamePlayerAccelerate()
{
	//速度の更新
	m_Speed += m_Acceleration;

	m_Speed = min(m_Speed, SPEED_MAX);
}


/*==========================================================
　　　　　プレイヤーが飛ばされていたか？
==========================================================*/
void CPlayer::KnockBack()
{
	m_IsKnockBack = true;
}


/*==========================================================
　　　　　プレイヤーの向きを取得
==========================================================*/
D3DXVECTOR3 CPlayer::GetPlayerDir()
{
	return m_Front;
}

/*==========================================================
　　　　　プレイヤーの左方向を取得
==========================================================*/
D3DXVECTOR3 CPlayer::GetPlayerLeft()
{
	return m_Left;
}

/*==========================================================
　　　　　プレイヤー武器の向き
==========================================================*/
D3DXVECTOR3 CPlayer::GetSwordDir()
{
	return m_SwordDir;
}

/*==========================================================
　　　　　プレイヤーの位置情報を取得
==========================================================*/
D3DXVECTOR3 CPlayer::GetPlayerPos()
{
	return m_PlayerPos;
}



/*==========================================================
　　　　　プレイヤーの当たり判定を取得
==========================================================*/
CircleCollision CPlayer::GetCollision()
{
	return m_Collision;
}



/*==========================================================
　　　　　プレイヤー武器の当たり判定を取得
==========================================================*/
CircleCollision CPlayer::GetSwordCollision()
{
	return m_SwordCollision;
}







/*==========================================================
　　　　　プレイヤーが攻撃しているか？（ハンマー状態）
==========================================================*/
bool CPlayer::GetSwordAttacking()
{
	return m_IsSwordAttacking;
}




/*==========================================================
　　　　　プレイヤーがジャンプしているか？
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
　　　　　プレイヤーを持っている武器の情報を取得
==========================================================*/
int CPlayer::GetAttackMode()
{
	return m_AttackMode;
}




/*==========================================================
　　　　　プレイヤーは飛ばされているか？
==========================================================*/
bool CPlayer::GetIsKnockBack()
{
	return m_IsKnockBack;
}


/*==========================================================
　　　　　プレイヤーのライフ情報を取得
==========================================================*/
int CPlayer::GetHP()
{
	return m_HP;
}



/*==========================================================
　　　　　プレイヤーのライフが減る判定
==========================================================*/
void CPlayer::HPLost()
{
	m_HP -= 1;
}


/*==========================================================
　　　　　プレイヤーの攻撃停止
==========================================================*/
void CPlayer::SetIsAttackStop()
{
	m_IsAttacking = true;
}
