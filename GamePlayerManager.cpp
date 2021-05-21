/*==========================================================

　　　　　　　　　　　プレイヤーの制御

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
　　　　　　　グローバル変数
==========================================================*/

static int g_PlayerModelMajoID = INVALID_MODEL_X_ID;
static CPlayer g_Player;



/*==========================================================
　　　　　　　プレイヤーの初期化
==========================================================*/
void GamePlayer_Init()
{
	g_PlayerModelMajoID = Model_X_Load("asset\\texture\\model\\majo.x");
	g_Player.PlayerInit();
	
}

/*==========================================================
　　　　　モデルをリリース
==========================================================*/
void GamePlayer_Final()
{
	Model_x_Release(&g_PlayerModelMajoID, 1);
}

/*==========================================================
　　　　　　　プレイヤーのアップデート
==========================================================*/
void GamePlayer_Update()
{


	g_Player.PlayerMove();
	g_Player.PlayerJump();

	


	//プレイヤーが落ちたの座標判定
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
　　　　　プレイヤーが飛ばされていたか？
==========================================================*/

void GamePlayerKnockBack()
{
	g_Player.KnockBack();
}



/*==========================================================
　　　　　プレイヤー武器の向き
==========================================================*/

D3DXVECTOR3 GetPlayerSwordDir()
{
	return g_Player.GetSwordDir();
}

/*==========================================================
　　　　　プレイヤーの位置情報を取得
==========================================================*/

D3DXVECTOR3 GetPlayerPos()
{
	return g_Player.GetPlayerPos();
}

/*==========================================================
　　　　　プレイヤーが飛ばされる情報を取得
==========================================================*/
void PlayerKnockBack(int AttackType, D3DXVECTOR3 MoveDir)
{
	g_Player.PlayerKnockBack(MoveDir, AttackType);
}

/*==========================================================
　　　　　プレイヤーの当たり判定を取得
==========================================================*/

CircleCollision GetPlayerCollision()
{
	return g_Player.GetCollision();
}


/*==========================================================
　　　　　プレイヤー武器の当たり判定を取得
==========================================================*/


CircleCollision GetPlayerSwordCollision()
{
	return g_Player.GetSwordCollision();
}





/*==========================================================
　　　　　プレイヤーが攻撃しているか？（ハンマー状態）
==========================================================*/


bool GetPlayerSwordAttacking()
{
	return g_Player.GetSwordAttacking();
}


/*==========================================================
　　　　　プレイヤーがジャンプしているか？
==========================================================*/


bool GetPlayerIsJumping()
{
	return g_Player.GetIsJumping();
}



/*==========================================================
　　　　　プレイヤーを持っている武器の情報を取得
==========================================================*/

int GetPlayerAttackMode()
{
	return g_Player.GetAttackMode();

}
/*==========================================================
　　　　　プレイヤー最終の向き方を決める
==========================================================*/
void GamePlayerSetDir(const D3DXVECTOR3* pDir)
{
	g_Player.GamePlayerSetDir(pDir);
}
/*==========================================================
　　　　　プレイヤーが動く際の速度
==========================================================*/
void GamePlayerAccelerate()
{
	g_Player.GamePlayerAccelerate();
}

/*==========================================================
　　　　　プレイヤーは飛ばされているか？
==========================================================*/

bool GetPlayerIsKnockBack()
{
	return g_Player.GetIsKnockBack();
}
/*==========================================================
　　　　　プレイヤーの向きを取得
==========================================================*/
D3DXVECTOR3 GetPlayerDir()
{
	return g_Player.GetPlayerDir();
}

/*==========================================================
　　　　　プレイヤーの左方向を取得
==========================================================*/
D3DXVECTOR3 GetPlayerLeft()
{
	return g_Player.GetPlayerLeft();
}


/*==========================================================
　　　　　プレイヤーのライフ情報を取得
==========================================================*/

int GetPlayerHP()
{
	return g_Player.GetHP();
}




/*==========================================================
　　　　　プレイヤーは無敵状態なのか？
==========================================================*/
bool GetPlayerIsMuteki()
{
	return g_Player.GetIsMuteki();
}


/*==========================================================
　　　　　プレイヤーが攻撃している状態になる（ポーズ機能対応）
==========================================================*/
void playerStopAttack()
{
	g_Player.SetIsAttackStop();
}

/*==========================================================
　　　　　プレイヤーのモデルIDを取得 
==========================================================*/
int GetModelMajo()
{
	return g_PlayerModelMajoID;
}