

/*============================================================

�@�@�@���̓����蔻��i�U���A���G�p�j

============================================================*/


#include "GameJudgement.h"
#include "Collision.h"
#include "GamePlayer.h"
#include "GamePlayerManager.h"

#include "GamePlayerBullet.h"
#include "GameEnemyManager.h"
#include "GameEnemy.h"
#include "GameHitEffect.h"
#include "GameBombManager.h"
#include "Sound.h"
#include "Score.h"
#include "GameParticleEmitter.h"
#include "GameTree.h"

static int g_PlayerAttackType[MAX_ENEMY];
static int g_EnemyAttackType = 0;
static int g_PlayerBombedAttackType = 0;
static int g_PlayerBombAttackType[MAX_BOMB];
static int g_EnemyBombedAttackType;
static D3DXVECTOR3 g_PlayerAttackEnemyDir[MAX_ENEMY];
static D3DXVECTOR3 g_PlayerAttackBombDir[MAX_BOMB];

static D3DXVECTOR3 g_EnemyAttackDir;
static D3DXVECTOR3 g_BombAttackDir;
static int g_LockOnEnemyNum = -1;

/*============================================================
�@�@�@�����蔻��̏�����
============================================================*/
bool GameJudgement_Init()
{
	for (int EnemyIndex = 0; EnemyIndex < MAX_ENEMY; EnemyIndex++) {
		g_PlayerAttackType[EnemyIndex] = 0;
	}
	for (int BombIndex = 0; BombIndex < MAX_BOMB; BombIndex++) {
		g_PlayerBombAttackType[BombIndex] = 0;
	}

	g_LockOnEnemyNum = -1;
	g_EnemyAttackType = 0;
	for (int EnemyIndex = 0; EnemyIndex < MAX_ENEMY; EnemyIndex++) {
		g_PlayerAttackEnemyDir[MAX_ENEMY] = { 0.0f,0.0f,0.0f };
	}
	for (int BombIndex = 0; BombIndex < MAX_BOMB; BombIndex++) {
		g_PlayerAttackBombDir[MAX_BOMB] = { 0.0f,0.0f,0.0f };
	}
	g_EnemyAttackDir = { 0.0f,0.0f,0.0f };
	g_BombAttackDir = {0.0f,0.0f,0.0f};
	return true;
}

/*============================================================
�@�@�@�����蔻��̃A�b�v�f�[�g
============================================================*/
void GameJudgement_Update()
{
	//�v���C���[�̓����蔻��
	CircleCollision pc = GetPlayerCollision();


	//�v���C���[�̃m�b�N�o�b�N����
	if (g_PlayerBombedAttackType == 0 )
	PlayerKnockBack(g_EnemyAttackType, g_EnemyAttackDir);
	
	if (g_EnemyAttackType == 0 )
	PlayerKnockBack(g_PlayerBombedAttackType, g_BombAttackDir);
	
	for (int EnemyIndex = 0; EnemyIndex < MAX_ENEMY; EnemyIndex++)
	{
		//�G�̃m�b�N�o�b�N����
		if (!GetEnemyNotNull(EnemyIndex)) continue;
		GameEnemyKnockBackDir(EnemyIndex, g_PlayerAttackType[EnemyIndex], g_PlayerAttackEnemyDir[EnemyIndex]);

		//�G�̓����蔻��
		CircleCollision ec = GetEnemyCollision(EnemyIndex);
		//�G�̍��G�͈�
		CircleCollision elc = GetEnemyLockOnZone(EnemyIndex);
		//�G�̍U������
		CircleCollision eac = GetEnemyAttackZone(EnemyIndex);
		

		//�G�̔���
		if (GetGameEnemyEnable(EnemyIndex)) {

				if (CollisionCircleAndCircleHit(&pc, &elc) && GetEnemyType(EnemyIndex) == ENEMY_RUNNING && !GetPlayerIsMuteki()) {
					EnemyLockOn(EnemyIndex);
				}
			
				if (CollisionCircleAndCircleHit(&pc, &ec)) {
					PlayerIsTouched(EnemyIndex, 1);
				}
				else
				{
					PlayerIsTouched(EnemyIndex, 0);
				}

				//�v���C���[�ƓG�̏Փ˔���
				if (CollisionCircleAndCircleHit(&pc, &eac) && GetGameEnemyIsAttacking(EnemyIndex)) {
					switch (GetEnemyType(EnemyIndex))
					{
					case ENEMY_RUNNING:
						g_EnemyAttackDir = -GetEnemyDir(EnemyIndex);

						if (GetPlayerIsKnockBack() == false) {
							PlaySound(SOUND_LABEL_SE_FALLHIT);
							GameHitEffect_Spawn(eac.Center.x + GetEnemyDir(EnemyIndex).x * eac.radius, eac.Center.y + GetEnemyDir(EnemyIndex).y * eac.radius, eac.Center.z + GetEnemyDir(EnemyIndex).z * eac.radius);
						}

						g_EnemyAttackType = 1;
						break;
					case ENEMY_JUMPING:
						g_EnemyAttackDir = -(GetPlayerPos() - eac.Center);

						if (GetPlayerIsKnockBack() == false) {
							PlaySound(SOUND_LABEL_SE_FALLHIT);
							GameHitEffect_Spawn(eac.Center.x - g_EnemyAttackDir.x * eac.radius, eac.Center.y - g_EnemyAttackDir.y * eac.radius, eac.Center.z - g_EnemyAttackDir.z* eac.radius);
						}
						g_EnemyAttackType = 3;
						break;

					}
					g_BombAttackDir = { 0.0f,0.0f,0.0f };
					GamePlayerKnockBack();
				}

				//�n���}�[�U���ƓG�̔���
				if (GetPlayerSwordAttacking() == true) {
					CircleCollision psc = GetPlayerSwordCollision();
					if (CollisionCircleAndCircleHit(&psc, &ec))
					{
						g_PlayerAttackEnemyDir[EnemyIndex] = psc.Center - ec.Center;
						switch (GetEnemyType(EnemyIndex))
						{
						case ENEMY_RUNNING:
							g_EnemyAttackDir = -g_PlayerAttackEnemyDir[EnemyIndex];
							g_PlayerAttackType[EnemyIndex] = 3;
							break;
						case ENEMY_JUMPING:
							g_EnemyAttackDir = -g_PlayerAttackEnemyDir[EnemyIndex];
							g_PlayerAttackType[EnemyIndex] = 1;
							break;

						}
						if (GetEnemyIsKnockBack(EnemyIndex) == false) {
							PlaySound(SOUND_LABEL_SE_FALLHIT);
							GameHitEffect_Spawn(psc.Center.x - g_PlayerAttackEnemyDir[EnemyIndex].x, psc.Center.y - g_PlayerAttackEnemyDir[EnemyIndex].y, psc.Center.z - g_PlayerAttackEnemyDir[EnemyIndex].z);
						}
						GameEnemyKnockBack(EnemyIndex);
						if (GetEnemyType(EnemyIndex) == ENEMY_RUNNING)
						{
							g_LockOnEnemyNum = EnemyIndex;
							EnemyLockOn(EnemyIndex);
						}
					}

				}

				//�{�������ƓG�̔���
				for (int BombIndex = 0; BombIndex < MAX_BOMB; BombIndex++)
				{
					CircleCollision bomAZ = GetBombAttackZone(BombIndex);

					if (GetBombExplode(BombIndex)) {
						if (CollisionCircleAndCircleHit(&bomAZ, &ec))
						{
							g_PlayerAttackEnemyDir[EnemyIndex] = bomAZ.Center - ec.Center;
							switch (GetEnemyType(EnemyIndex))
							{
							case ENEMY_RUNNING:
								g_EnemyAttackDir = -g_PlayerAttackEnemyDir[EnemyIndex];
								g_PlayerAttackType[EnemyIndex] = 1;
								break;
							case ENEMY_JUMPING:
								g_EnemyAttackDir = -g_PlayerAttackEnemyDir[EnemyIndex];
								g_PlayerAttackType[EnemyIndex] = 1;
								break;

							}
							if (GetEnemyIsKnockBack(EnemyIndex) == false) {
								PlaySound(SOUND_LABEL_SE_FALLHIT);
								GameHitEffect_Spawn(bomAZ.Center.x - g_PlayerAttackEnemyDir[EnemyIndex].x, bomAZ.Center.y - g_PlayerAttackEnemyDir[EnemyIndex].y, bomAZ.Center.z - g_PlayerAttackEnemyDir[EnemyIndex].z);
							}
							GameEnemyKnockBack(EnemyIndex);
						}
					}

				}




		}

		
		//�e�ƓG�̔���
		for (int PlayerBulletIndex = 0; PlayerBulletIndex < GameBulletGetCountMax(); PlayerBulletIndex++){
		
			//�e�̓����蔻��
			CircleCollision pbc = GameBulletGetCollision(PlayerBulletIndex);
			
			
			if(GetGameEnemyEnable(EnemyIndex) && GameBulletIsEnable(PlayerBulletIndex)){
				//�Փ˔���
				if (CollisionCircleAndCircleHit(&pbc, &ec)){
					g_PlayerAttackEnemyDir[EnemyIndex] = -GetGameBulletDir(PlayerBulletIndex);
					
					switch (GetEnemyType(EnemyIndex))
					{
					case ENEMY_RUNNING:
						g_EnemyAttackDir = -g_PlayerAttackEnemyDir[EnemyIndex];
						PlaySound(SOUND_LABEL_SE_EXPLOSION);
						GameHitEffect_Spawn(pbc.Center.x, pbc.Center.y, pbc.Center.z);
						g_PlayerAttackType[EnemyIndex] = 1;
						break;
					case ENEMY_JUMPING:
						g_EnemyAttackDir = -g_PlayerAttackEnemyDir[EnemyIndex];
						PlaySound(SOUND_LABEL_SE_EXPLOSION);
						GameHitEffect_Spawn(pbc.Center.x, pbc.Center.y, pbc.Center.z);
						g_PlayerAttackType[EnemyIndex] = 3;
						break;

					}
					
					GameEnemyKnockBack(EnemyIndex);
					
					GameBulletDestroy(PlayerBulletIndex);
					
					
					if (GetEnemyType(EnemyIndex) == ENEMY_RUNNING) {
						g_LockOnEnemyNum = EnemyIndex;
						EnemyLockOn(EnemyIndex);
					}
				}
			}
		}
	}

	//���e�̔���
	for (int BombIndex = 0; BombIndex < MAX_BOMB; BombIndex++)
	{
		//�{���̃m�b�N�o�b�N����
		BombKnockBackDir(BombIndex, g_PlayerBombAttackType[BombIndex], g_PlayerAttackBombDir[BombIndex]);
		
		//���e�̓����蔻��(�U����)
		CircleCollision bomC = GetBombCollision(BombIndex);
		//���e�̔����͈�
		CircleCollision bomAZ = GetBombAttackZone(BombIndex);

		if (GetBombEnable(BombIndex))
		{
			//�e�Ɣ��e�̔���
			for (int PlayerBulletIndex = 0; PlayerBulletIndex < GameBulletGetCountMax(); PlayerBulletIndex++) {
				//�e�̓����蔻��
				CircleCollision pbc = GameBulletGetCollision(PlayerBulletIndex);
			
				//�e�����݂��Ă����ꍇ
				if (GameBulletIsEnable(PlayerBulletIndex)) {
					if (CollisionCircleAndCircleHit(&pbc, &bomC))
					{
						GameBulletDestroy(PlayerBulletIndex);
						BombExplode(BombIndex);
						GameScore_AddScore(10);
					}
				}
			}

			


			//�n���}�[�Ɣ��e�̔���
			if (GetPlayerSwordAttacking()) {
				//�n���}�[�U���͈͂̓����蔻��
				CircleCollision psc = GetPlayerSwordCollision();
				//�Փ˔���
				if (CollisionCircleAndCircleHit(&psc, &bomC))
				{
					g_PlayerAttackBombDir[BombIndex] = psc.Center - bomC.Center;
					
					g_BombAttackDir = -g_PlayerAttackBombDir[BombIndex];
					g_PlayerBombAttackType[BombIndex] = 1;
					
					if (GetBombKnockBackEnable(BombIndex) == false) {
						PlaySound(SOUND_LABEL_SE_FALLHIT);
						GameHitEffect_Spawn(psc.Center.x - g_PlayerAttackBombDir[BombIndex].x, psc.Center.y - g_PlayerAttackBombDir[BombIndex].y, psc.Center.z - g_PlayerAttackBombDir[BombIndex].z);
					}
					BombKnockBack(BombIndex);
				}

			}
			

		}
		else if (GetBombExplode(BombIndex)) {
			if (CollisionCircleAndCircleHit(&pc, &bomAZ)) {
				//�v���C���[�Ɣ����̔���
				if (GetPlayerIsKnockBack() == false) {
					PlaySound(SOUND_LABEL_SE_FALLHIT);
					GameHitEffect_Spawn(GetPlayerPos().x, GetPlayerPos().y, GetPlayerPos().z);
					g_BombAttackDir = -(GetPlayerPos() - bomAZ.Center);
					g_EnemyAttackDir = { 0.0f,0.0f,0.0f };
					g_PlayerBombedAttackType = 3;
					GamePlayerKnockBack();
				}
			
			}

			for (int EnemyIndex = 0; EnemyIndex < MAX_ENEMY; EnemyIndex++)
			{
				if (!GetEnemyNotNull(EnemyIndex)) continue;
				GameEnemyKnockBackDir(EnemyIndex, g_PlayerAttackType[EnemyIndex], g_PlayerAttackEnemyDir[EnemyIndex]);
			}



		}





	}


}

/*============================================================
�@�@�@�т�����}�[�N�̔���
============================================================*/
int GetLockOnEnemyNum()
{
	if (!GetEnemyNotNull(g_LockOnEnemyNum) || g_LockOnEnemyNum != -1)
	return g_LockOnEnemyNum;
}

/*============================================================
�@�@�@�v���C���[���U�����Ă��Ȃ���ԂɕύX
============================================================*/
void EndAttack()
{
	g_EnemyAttackType = 0;
	g_PlayerBombedAttackType = 0;
	
}

