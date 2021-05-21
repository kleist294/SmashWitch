

/*============================================================

　　　球体当たり判定（攻撃、索敵用）

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
　　　当たり判定の初期化
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
　　　当たり判定のアップデート
============================================================*/
void GameJudgement_Update()
{
	//プレイヤーの当たり判定
	CircleCollision pc = GetPlayerCollision();


	//プレイヤーのノックバック判定
	if (g_PlayerBombedAttackType == 0 )
	PlayerKnockBack(g_EnemyAttackType, g_EnemyAttackDir);
	
	if (g_EnemyAttackType == 0 )
	PlayerKnockBack(g_PlayerBombedAttackType, g_BombAttackDir);
	
	for (int EnemyIndex = 0; EnemyIndex < MAX_ENEMY; EnemyIndex++)
	{
		//敵のノックバック判定
		if (!GetEnemyNotNull(EnemyIndex)) continue;
		GameEnemyKnockBackDir(EnemyIndex, g_PlayerAttackType[EnemyIndex], g_PlayerAttackEnemyDir[EnemyIndex]);

		//敵の当たり判定
		CircleCollision ec = GetEnemyCollision(EnemyIndex);
		//敵の索敵範囲
		CircleCollision elc = GetEnemyLockOnZone(EnemyIndex);
		//敵の攻撃判定
		CircleCollision eac = GetEnemyAttackZone(EnemyIndex);
		

		//敵の判定
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

				//プレイヤーと敵の衝突判定
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

				//ハンマー攻撃と敵の判定
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

				//ボム爆発と敵の判定
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

		
		//弾と敵の判定
		for (int PlayerBulletIndex = 0; PlayerBulletIndex < GameBulletGetCountMax(); PlayerBulletIndex++){
		
			//弾の当たり判定
			CircleCollision pbc = GameBulletGetCollision(PlayerBulletIndex);
			
			
			if(GetGameEnemyEnable(EnemyIndex) && GameBulletIsEnable(PlayerBulletIndex)){
				//衝突判定
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

	//爆弾の判定
	for (int BombIndex = 0; BombIndex < MAX_BOMB; BombIndex++)
	{
		//ボムのノックバック判定
		BombKnockBackDir(BombIndex, g_PlayerBombAttackType[BombIndex], g_PlayerAttackBombDir[BombIndex]);
		
		//爆弾の当たり判定(攻撃の)
		CircleCollision bomC = GetBombCollision(BombIndex);
		//爆弾の爆発範囲
		CircleCollision bomAZ = GetBombAttackZone(BombIndex);

		if (GetBombEnable(BombIndex))
		{
			//弾と爆弾の判定
			for (int PlayerBulletIndex = 0; PlayerBulletIndex < GameBulletGetCountMax(); PlayerBulletIndex++) {
				//弾の当たり判定
				CircleCollision pbc = GameBulletGetCollision(PlayerBulletIndex);
			
				//弾が存在していた場合
				if (GameBulletIsEnable(PlayerBulletIndex)) {
					if (CollisionCircleAndCircleHit(&pbc, &bomC))
					{
						GameBulletDestroy(PlayerBulletIndex);
						BombExplode(BombIndex);
						GameScore_AddScore(10);
					}
				}
			}

			


			//ハンマーと爆弾の判定
			if (GetPlayerSwordAttacking()) {
				//ハンマー攻撃範囲の当たり判定
				CircleCollision psc = GetPlayerSwordCollision();
				//衝突判定
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
				//プレイヤーと爆発の判定
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
　　　びっくりマークの判定
============================================================*/
int GetLockOnEnemyNum()
{
	if (!GetEnemyNotNull(g_LockOnEnemyNum) || g_LockOnEnemyNum != -1)
	return g_LockOnEnemyNum;
}

/*============================================================
　　　プレイヤーを攻撃していない状態に変更
============================================================*/
void EndAttack()
{
	g_EnemyAttackType = 0;
	g_PlayerBombedAttackType = 0;
	
}

