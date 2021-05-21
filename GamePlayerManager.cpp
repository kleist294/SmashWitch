/*==========================================================

�@�@�@�@�@�@�@�@�@�@�@�v���C���[�̐���

==========================================================*/


#include"model_x.h"
#include "d3dx9.h"
#include "keylogger.h"
#include "shadow.h"
#include "GamePlayerBullet.h"
#include "GamePlayer.h"
#include "GamePlayerManager.h"
#include "sound.h"
#include "MeshField.h"
#include "collision.h"
#include "GameEnemyManager.h"
#include "GameHammer.h"
#include "GameBulletMode.h"
#include "GamePlayerHP.h"
#include "GameJudgement.h"
#include "mouse.h"
#include "JudgementRay.h"
#include "GameFloor.h"



/*==========================================================
�@�@�@�@�@�@�@�O���[�o���ϐ�
==========================================================*/

static int g_PlayerModelMajoID = INVALID_MODEL_X_ID;
static CPlayer g_Player;



/*==========================================================
�@�@�@�@�@�@�@�v���C���[�̏�����
==========================================================*/
void GamePlayer_Init()
{
	g_PlayerModelMajoID = Model_X_Load("asset\\texture\\model\\majo.x");
	g_Player.PlayerInit();
	
}

/*==========================================================
�@�@�@�@�@���f���������[�X
==========================================================*/
void GamePlayer_Final()
{
	Model_x_Release(&g_PlayerModelMajoID, 1);
}

/*==========================================================
�@�@�@�@�@�@�@�v���C���[�̃A�b�v�f�[�g
==========================================================*/
void GamePlayer_Update()
{


	g_Player.PlayerMove();
	g_Player.PlayerJump();

	


	//�v���C���[���������̍��W����
	if (g_Player.GetPlayerPos().y <= -15.0f)
	{
		EnemyEndLockOn();
		g_Player.HPLost();
		GamePlayerHP_HeartBroke();
		if (GetPlayerHP() >= 0)
			g_Player.PlayerRespawn();
	}


	GameHammer_Update();
	GameBulletMode_Update();
}

void GamePlayer_Draw()
{
	g_Player.PlayerDraw();
}

/*==========================================================
�@�@�@�@�@�v���C���[����΂���Ă������H
==========================================================*/

void GamePlayerKnockBack()
{
	g_Player.KnockBack();
}



/*==========================================================
�@�@�@�@�@�v���C���[����̌���
==========================================================*/

D3DXVECTOR3 GetPlayerSwordDir()
{
	return g_Player.GetSwordDir();
}

/*==========================================================
�@�@�@�@�@�v���C���[�̈ʒu�����擾
==========================================================*/

D3DXVECTOR3 GetPlayerPos()
{
	return g_Player.GetPlayerPos();
}

/*==========================================================
�@�@�@�@�@�v���C���[����΂��������擾
==========================================================*/
void PlayerKnockBack(int AttackType, D3DXVECTOR3 MoveDir)
{
	g_Player.PlayerKnockBack(MoveDir, AttackType);
}

/*==========================================================
�@�@�@�@�@�v���C���[�̓����蔻����擾
==========================================================*/

CircleCollision GetPlayerCollision()
{
	return g_Player.GetCollision();
}


/*==========================================================
�@�@�@�@�@�v���C���[����̓����蔻����擾
==========================================================*/


CircleCollision GetPlayerSwordCollision()
{
	return g_Player.GetSwordCollision();
}





/*==========================================================
�@�@�@�@�@�v���C���[���U�����Ă��邩�H�i�n���}�[��ԁj
==========================================================*/


bool GetPlayerSwordAttacking()
{
	return g_Player.GetSwordAttacking();
}


/*==========================================================
�@�@�@�@�@�v���C���[���W�����v���Ă��邩�H
==========================================================*/


bool GetPlayerIsJumping()
{
	return g_Player.GetIsJumping();
}



/*==========================================================
�@�@�@�@�@�v���C���[�������Ă��镐��̏����擾
==========================================================*/

int GetPlayerAttackMode()
{
	return g_Player.GetAttackMode();

}
/*==========================================================
�@�@�@�@�@�v���C���[�ŏI�̌����������߂�
==========================================================*/
void GamePlayerSetDir(const D3DXVECTOR3* pDir)
{
	g_Player.GamePlayerSetDir(pDir);
}
/*==========================================================
�@�@�@�@�@�v���C���[�������ۂ̑��x
==========================================================*/
void GamePlayerAccelerate()
{
	g_Player.GamePlayerAccelerate();
}

/*==========================================================
�@�@�@�@�@�v���C���[�͔�΂���Ă��邩�H
==========================================================*/

bool GetPlayerIsKnockBack()
{
	return g_Player.GetIsKnockBack();
}
/*==========================================================
�@�@�@�@�@�v���C���[�̌������擾
==========================================================*/
D3DXVECTOR3 GetPlayerDir()
{
	return g_Player.GetPlayerDir();
}

/*==========================================================
�@�@�@�@�@�v���C���[�̍��������擾
==========================================================*/
D3DXVECTOR3 GetPlayerLeft()
{
	return g_Player.GetPlayerLeft();
}


/*==========================================================
�@�@�@�@�@�v���C���[�̃��C�t�����擾
==========================================================*/

int GetPlayerHP()
{
	return g_Player.GetHP();
}




/*==========================================================
�@�@�@�@�@�v���C���[�͖��G��ԂȂ̂��H
==========================================================*/
bool GetPlayerIsMuteki()
{
	return g_Player.GetIsMuteki();
}


/*==========================================================
�@�@�@�@�@�v���C���[���U�����Ă����ԂɂȂ�i�|�[�Y�@�\�Ή��j
==========================================================*/
void playerStopAttack()
{
	g_Player.SetIsAttackStop();
}

/*==========================================================
�@�@�@�@�@�v���C���[�̃��f��ID���擾 
==========================================================*/
int GetModelMajo()
{
	return g_PlayerModelMajoID;
}