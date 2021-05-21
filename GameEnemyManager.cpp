
/*============================================================

�@�@�@�@�@�@�@�G�̐���

============================================================*/




#include"model_x.h"
#include "d3dx9.h"
#include "keylogger.h"
#include "GameEnemy.h"
#include "GameEnemyManager.h"
#include "sound.h"
#include "GamePlayer.h"
#include "GamePlayerManager.h"
#include "collision.h"
#include "GameWaveAnime.h"
#include "GameWaveFont.h"
#include "Camera.h"

static CEnemy* g_Enemy[MAX_ENEMY];

static int g_XModelIDGhost = INVALID_MODEL_X_ID;
static int g_XModelIDSlime = INVALID_MODEL_X_ID;




static bool g_EnemySpawn = true;
static int g_Wave = -1;
static int g_DeadEnemyCount = 0;
static int g_SpawnCount = 0;
static bool g_EnemyBossMode = false;
static bool g_BossIsDead = false;


/*============================================================
�@�@�@�@�@�@�@�G�̏�����
============================================================*/
void GameEnemy_Init() 
{

	g_XModelIDGhost = Model_X_Load("asset\\texture\\model\\ghost.x");
	g_XModelIDSlime = Model_X_Load("asset\\texture\\model\\slime.x");

	g_EnemySpawn = true;
	g_Wave = -1;
	g_DeadEnemyCount = 0;
	g_SpawnCount = 0;
	g_EnemyBossMode = false;
	g_BossIsDead = false;



	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemy[i] = NULL;
	}

	for (int i = 0; i < 27; i++)
	{
		g_Enemy[i] = CEnemy::Create();
	}
	
	//�G�����炩���ߔz�u
	g_Enemy[0]->EnemySpawn({  9.0f,3.0f + 15.0f, 7.0f } ,1);
	g_Enemy[1]->EnemySpawn({  0.0f,15.0f + 15.0f,7.0f } ,1);
	g_Enemy[2]->EnemySpawn({ -9.0f,10.0f + 15.0f,7.0f } ,1);
	g_Enemy[3]->EnemySpawn({ 9.0f,3.0f + 15.0f, 9.0f }, 0);
	g_Enemy[4]->EnemySpawn({ 9.0f,3.0f + 15.0f,-9.0f }, 0);
	g_Enemy[5]->EnemySpawn({ -9.0f,3.0f + 15.0f,9.0f }, 0);
	g_Enemy[6]->EnemySpawn({ -9.0f,3.0f + 15.0f,-9.0f }, 0);
	g_Enemy[7]->EnemySpawn({ 6.0f,3.0f + 15.0f, 0.0f }, 0);
	g_Enemy[8]->EnemySpawn({ -6.0f,4.0f + 15.0f,0.0f }, 0);
	g_Enemy[9]->EnemySpawn({ 0.0f,20.0f + 15.0f,6.0f }, 0);
	g_Enemy[10]->EnemySpawn({ 0.0f,15.0f + 15.0f, -6.0f }, 0);
	g_Enemy[11]->EnemySpawn({ 0.0f,3.0f + 15.0f, 0.0f }, 1);
	g_Enemy[12]->EnemySpawn({ 9.0f,10.0f + 15.0f, 9.0f }, 0);
	g_Enemy[13]->EnemySpawn({ 9.0f,20.0f + 15.0f,-9.0f }, 0);
	g_Enemy[14]->EnemySpawn({ -9.0f,30.0f + 15.0f,-1.0f }, 0);
	g_Enemy[15]->EnemySpawn({ 9.0f,40.0f + 15.0f, 9.0f }, 0);
	g_Enemy[16]->EnemySpawn({ 6.0f,40.0f + 15.0f, 0.0f }, 1);
	g_Enemy[17]->EnemySpawn({ -6.0f,60.0f + 15.0f, 0.0f }, 1);
	g_Enemy[18]->EnemySpawn({ 7.0f,3.0f + 15.0f, 0.0f }, 0);
	g_Enemy[19]->EnemySpawn({ -7.0f,4.0f + 15.0f,0.0f }, 0);
	g_Enemy[20]->EnemySpawn({ 0.0f,7.0f + 15.0f, 7.0f }, 0);
	g_Enemy[21]->EnemySpawn({ 0.0f,10.0f + 15.0f,-7.0f }, 0);
	g_Enemy[22]->EnemySpawn({ 5.0f, 15.0f + 15.0f, 5.0f }, 1);
	g_Enemy[23]->EnemySpawn({ 5.0f, 15.0f + 15.0f, -5.0f }, 1);
	g_Enemy[24]->EnemySpawn({ -5.0f,15.0f + 15.0f, 5.0f }, 1);
	g_Enemy[25]->EnemySpawn({ -5.0f,15.0f + 15.0f, -5.0f }, 1);


	g_Enemy[0]->EnemyEnable();
	g_Enemy[1]->EnemyEnable();
	g_Enemy[2]->EnemyEnable();

}

/*============================================================
�@�@�@�@�@�@�@�G�̃A�b�v�f�[�g
============================================================*/
void GameEnemy_Update()
{
	int x = Camera_GetPosition()->x + Camera_GetFrontVector()->x * 10.0f + Camera_GetRightVector()->x * -2.0f + Camera_GetUpVector()->x * 3.0f;
	int y = Camera_GetPosition()->y + Camera_GetFrontVector()->y * 10.0f + Camera_GetRightVector()->y * -2.0f + Camera_GetUpVector()->y * 3.0f;
	int z = Camera_GetPosition()->z + Camera_GetFrontVector()->z * 10.0f + Camera_GetRightVector()->z * -2.0f + Camera_GetUpVector()->z * 3.0f;


	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i] != NULL) {
			if (g_Enemy[i]->GetEnemyEnable() == true)
			{
				if (g_Enemy[i]->GetEnemyLockOn() == false || g_Enemy[i]->GetEnemyType() == 1) {


					g_Enemy[i]->EnemyMoveMent(g_Enemy[i]->GetEnemyRandomDir());


				}
				else if (g_Enemy[i]->GetEnemyType() == 0)
				{
					g_Enemy[i]->EnemyMoveMent(GetPlayerPos() - g_Enemy[i]->GetEnemyPos());
				}

				//	g_Enemy[i].GameEnemy_KnockBack(GetPlayerPos() - g_Enemy[i].GetEnemyPos(),2);
				//
				//	if (KeyloggerTrigger(KL_ATTACK)) {
				//		g_Enemy[0].EnemyKnockBack();
				//	}
			}
		}
	}

	if (g_DeadEnemyCount == 3 && g_Wave == 0)
	{
		g_EnemySpawn = true;
	}
	if (g_DeadEnemyCount == 7 && g_Wave == 1)
	{
		g_EnemySpawn = true;
	}
	if (g_DeadEnemyCount == 12 && g_Wave == 2)
	{
		g_EnemySpawn = true;
	}
	if (g_DeadEnemyCount == 18 && g_Wave == 3)
	{
		g_EnemySpawn = true;
	}

	if (g_EnemySpawn == true)
	{
		switch (g_Wave)
		{
		case -1:
			g_EnemySpawn = false;
			break;
		case 0:
			g_Enemy[3]->EnemyEnable();
			g_Enemy[4]->EnemyEnable();
			g_Enemy[5]->EnemyEnable();
			g_Enemy[6]->EnemyEnable();
			g_EnemySpawn = false;
			break;
		case 1:
			g_Enemy[7]->EnemyEnable();
			g_Enemy[8]->EnemyEnable();
			g_Enemy[9]->EnemyEnable();
			g_Enemy[10]->EnemyEnable();
			g_Enemy[11]->EnemyEnable();
			g_EnemySpawn = false;
			break;
		case 2:
			g_Enemy[12]->EnemyEnable();
			g_Enemy[13]->EnemyEnable();
			g_Enemy[14]->EnemyEnable();
			g_Enemy[15]->EnemyEnable();
			g_Enemy[16]->EnemyEnable();
			g_Enemy[17]->EnemyEnable();
			g_EnemySpawn = false;
			break;
		case 3:
			g_Enemy[18]->EnemyEnable();
			g_Enemy[19]->EnemyEnable();
			g_Enemy[20]->EnemyEnable();
			g_Enemy[21]->EnemyEnable();
			g_Enemy[22]->EnemyEnable();
			g_Enemy[23]->EnemyEnable();
			g_Enemy[24]->EnemyEnable();
			g_Enemy[25]->EnemyEnable();
			g_EnemySpawn = false;
			break;
		case 4:
			g_EnemyBossMode = true;
		default:
			break;
		}
		GameWaveAnimeSpawn();

		PlaySound(SOUND_LABEL_SE_SUMMON);
		GameWaveFontChange();
		g_Wave++;
	}

	

}

/*============================================================
�@�@�@�@�@�@�@�G�̕`��
============================================================*/
void GameEnemy_Draw()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i] != NULL) {
			if (g_Enemy[i]->GetEnemyEnable() == true)
				g_Enemy[i]->EnemyDraw();
		}
	}
}
void GameEnemy_Final()
{


}

/*============================================================
�@�@�@�@index�Ԃ̓G����΂����ۂ̕����ƍU�����ꂽ�^�C�v
============================================================*/
void GameEnemyKnockBackDir(int index,int AttackType, D3DXVECTOR3 Dir)
{
	g_Enemy[index]->GameEnemyKnockBack(Dir, AttackType);

}

/*============================================================
�@�@�@�@index�Ԃ̓G�̈ʒu�����擾
============================================================*/
D3DXVECTOR3 GetEnemyPos(int index)
{
	return g_Enemy[index]->GetEnemyPos();
}

/*============================================================
�@�@�@�@index�Ԃ̓G�̌����������擾
============================================================*/
D3DXVECTOR3 GetEnemyDir(int index)
{
	return g_Enemy[index]->GetEnemyDir();
}

/*============================================================
�@�@�@�@index�Ԃ��΂���Ԃɂ���
============================================================*/
void GameEnemyKnockBack(int index)
{
	g_Enemy[index]->EnemyKnockBack();

}

/*============================================================
�@�@�@�@index�Ԃ̓G�̑��݂��擾
============================================================*/
bool GetGameEnemyEnable(int index) 
{
	return g_Enemy[index]->GetEnemyEnable();
}

/*============================================================
�@�@�@�@index�Ԃ̓G�̍U�������擾
============================================================*/
bool GetGameEnemyIsAttacking(int index)
{
	return g_Enemy[index]->GetIsAttack();
}

/*============================================================
�@�@�@�@index�Ԃ̓G�̓����蔻����擾
============================================================*/
CircleCollision GetEnemyCollision(int index)
{
	return g_Enemy[index]->GetCollision();
}

/*============================================================
�@�@�@�@index�Ԃ̓G�̍��G�͈͂��擾
============================================================*/
CircleCollision GetEnemyLockOnZone(int index)
{
	return g_Enemy[index]->GetLockOnZone();
}

/*============================================================
�@�@�@�@index�Ԃ̓G�̍U���͈͂��擾
============================================================*/
CircleCollision GetEnemyAttackZone(int index)
{
	return g_Enemy[index]->GetAttackZone();
}

/*============================================================
�@�@�@�@index�Ԃ̓G�����b�N�I����Ԃɂ���
============================================================*/
void EnemyLockOn(int index)
{
	g_Enemy[index]->EnemyLockOn();
}

/*============================================================
�@�@�@�@���b�N�I����Ԃ���������
============================================================*/
void EnemyEndLockOn()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i] != NULL)
		g_Enemy[i]->EnemyNotLockOn();
	}
}

/*============================================================
�@�@�@�@index�Ԃ̓G���v���C���[�ɓ�����
============================================================*/
void PlayerIsTouched(int index,int touch)
{
	g_Enemy[index]->PlayerIsTouch(touch);
}

/*============================================================
�@�@�@�@index�Ԃ̓G�̃r�b�N���}�[�N�A�j���[�V����
============================================================*/
void EnemyIsBikuri(int index)
{
	g_Enemy[index]->EnemyBikuri();
}

/*============================================================
�@�@�@�@index�Ԃ̓G�̃^�C�v���擾����
============================================================*/
int GetEnemyType(int index)
{
	return g_Enemy[index]->GetEnemyType();
}

/*============================================================
�@�@�@�@index�Ԃ̓G����΂���Ă��邩�H
============================================================*/
bool GetEnemyIsKnockBack(int index)
{
	return g_Enemy[index]->GetIsKnockBack();
}

/*============================================================
�@�@�@�@�G���|�����J�E���g
============================================================*/
void DeadAddEnemyCount()
{
	g_DeadEnemyCount++;
}

/*============================================================
�@�@�@�@�|�����G�̐����擾
============================================================*/
int GetDeadEnemyCount()
{
	return g_DeadEnemyCount;
}

/*============================================================
�@�@�@�@�E�F�[�u���擾����
============================================================*/
int GetEnemyWave()
{
	return g_Wave;
}

/*============================================================
�@�@�@�@�G��NULL�ł͂Ȃ������莮
============================================================*/
bool GetEnemyNotNull(int index)
{
	if (g_Enemy[index] != NULL)
		return true;
	else
		return false;
}

int GetModelGhost()
{
	return g_XModelIDGhost;
}

int GetModelSlime()
{
	return g_XModelIDSlime;
}