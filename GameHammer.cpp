
/*============================================================

　　　　　　　　武器がハンマーの時の状態

============================================================*/


#include "GamePlayerManager.h"
#include "GameHammer.h"
#include "DropEffect.h"
#include "Sound.h"
#include "TextureManager.h"
#include "Model_x.h"
#include "GameParticleEmitter.h"
#include "JudgementRay.h"

static int g_XModelHammer = INVALID_MODEL_X_ID;

static int g_HammerTex = INVALID_TEXTURE_ID;
static Hammer g_Hammer;

static D3DXVECTOR3 g_HammerAttackCenter;

static int   g_HammerAttackFrame;
static float g_HammerAttackSize;
static bool g_IsDrop;

/*============================================================
　　　　　　　ハンマーの初期化
============================================================*/
void GameHammer_Init() 
{
	g_XModelHammer = Model_X_Load("asset\\texture\\model\\hammer.x");
	g_HammerTex = Texture_SetTextureLoadFile("asset\\texture\\model\\hammer.png");
	g_Hammer.IsAttacking = false;
	g_Hammer.IsEnable = false;
	g_IsDrop = false;
	g_Hammer.AttackRotate = 0.0f;
	g_HammerAttackFrame = 0;
	g_HammerAttackSize = 0.0f;
	g_HammerAttackCenter = { -GetPlayerDir().z, 0.0f,GetPlayerDir().x };
}

/*============================================================
　　　　　　　ハンマーのアップデート
============================================================*/
void GameHammer_Update()
{
	g_HammerAttackCenter = { -GetPlayerDir().z , 0.0f ,GetPlayerDir().x };


	if (GetPlayerAttackMode() == 1)
	{
		g_Hammer.IsEnable = true;

	}
	else
	{
		g_Hammer.IsEnable = false;
	}




	if (g_Hammer.IsEnable == true && GetPlayerSwordAttacking() == true)
	{
		g_Hammer.AttackRotate -= 0.2f;
		g_HammerAttackFrame ++;
		g_HammerAttackSize += 0.2f;
		if(g_HammerAttackFrame == 4)
		PlaySound(SOUND_LABEL_SE_HAMMER);
	}
	else
	{
		g_Hammer.AttackRotate = 0.0f;
		g_HammerAttackFrame = 0;
		g_HammerAttackSize = 0.0f;
	}

}

/*============================================================
　　　　　　　ハンマーの描画
============================================================*/
void GameHammer_Draw()
{
	D3DXMATRIX mtxWorld, mtxWAttack, mtxT, mtxTAttack, mtxS, mtxS1, mtxR, mtxRAttack, mtxRAttackR;

	float FloorDistance = 0.0f;


	D3DXMatrixScaling(&mtxS1, 0.15f, 0.15f, 0.15f);
	D3DXMatrixTranslation(&mtxT, GetPlayerPos().x + GetPlayerDir().z * 0.4, GetPlayerPos().y - 0.225f, GetPlayerPos().z - GetPlayerDir().x * 0.4);
	D3DXMatrixTranslation(&mtxTAttack, GetPlayerPos().x + GetPlayerDir().x * 0.6f + GetPlayerDir().z * 0.375 , GetPlayerPos().y + 0.2f + g_Hammer.AttackRotate * 0.5f, GetPlayerPos().z + GetPlayerDir().z * 0.4f - GetPlayerDir().x * 0.375);

	D3DXMatrixRotationY(&mtxR, -atan2f(GetPlayerDir().z, GetPlayerDir().x) + D3DXToRadian(-90));
	D3DXMatrixRotationAxis(&mtxRAttack, &g_HammerAttackCenter, g_Hammer.AttackRotate);
	D3DXMatrixRotationAxis(&mtxRAttackR, &GetPlayerDir(), D3DXToRadian(-90));
	//D3DXMatrixRotationY(&mtxR, -3.14f + D3DXToRadian(-90));




	mtxWorld = mtxS1 * mtxR * mtxT;
	mtxWAttack = mtxS1 * mtxR * mtxRAttack *mtxTAttack ;

	if (g_Hammer.IsEnable == true )
	{
		if (GetPlayerSwordAttacking() == true) {
			
			
			Model_X_Draw(g_XModelHammer, &mtxWAttack);
			if (GetPlayerIsJumping() == false && JudgementRay_ObjectGround_Check(GetPlayerSwordCollision().Center,1.0f, &FloorDistance,HAMMER_EFFECT)) {
				DropEffect_Draw(GetPlayerSwordCollision().Center.x, GetPlayerSwordCollision().Center.y + 0.025f - FloorDistance, GetPlayerSwordCollision().Center.z, g_HammerAttackSize);
				if (g_IsDrop == false) {

					for (int i = 0; i < 10; i++) {

						float RandomSize = (float)(rand() % 50 + 50) / 1000;
						float RandomSpeed = (float)(rand() % 6 + 20) / 100;
						GameParticleEmitter_Spawn({ GetPlayerSwordCollision().Center.x,GetPlayerSwordCollision().Center.y + 0.025f - FloorDistance ,GetPlayerSwordCollision().Center.z }, 0, RandomSize, RandomSpeed);
					}
					g_IsDrop = true;
				}
			}
		}
		else {
			Model_X_Draw(g_XModelHammer, &mtxWorld);
			g_IsDrop = false;
		}
	}
	

}





void GameHammer_Final()
{


}
