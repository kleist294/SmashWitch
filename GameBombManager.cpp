/*============================================================

�@�@�@�@�@�@�@���e�̐���

============================================================*/




#include "GameBombManager.h"
#include "GameBomb.h"
#include "Collision.h"

#define BOMBCOUNT 2

static Bomb* g_Bomb[MAX_BOMB];

static int g_XmodelBomb = INVALID_MODEL_X_ID;
static int g_TestFrame = 0;
static int g_BombCount = 0;

/*============================================================
�@�@�@�@�@�@�@���e����̏�����
============================================================*/

void GameBombManager_Init()
{
	g_BombCount = 0;
	g_XmodelBomb = Model_X_Load("asset\\texture\\model\\bomb.x");
	for (int i = 0; i < MAX_BOMB; i++) {
		g_Bomb[i] = new Bomb;
	}

}

/*============================================================
�@�@�@�@�@�@�@���e����̃A�b�v�f�[�g
============================================================*/
void GameBombManager_Update()
{
	
	//�莞�ɔ��e����
	if (g_TestFrame >= 700) {
		
		for (int i = 0; i < BOMBCOUNT; i++) {
			GameBombManager_Spawn();
		}
		


		g_TestFrame = 0;
	}
	
	for (int i = 0; i < MAX_BOMB; i++) {
		g_Bomb[i]->BombStatus();
	}


	g_TestFrame++;

}

/*============================================================
�@�@�@�@�@�@�@���e�̕`��
============================================================*/
void GameBombManager_Draw()
{
	for (int i = 0; i < MAX_BOMB; i++) {
		g_Bomb[i]->BombDraw();
	}
}
/*============================================================
�@�@�@�@�@�@�@���e�̃����[�X
============================================================*/
void GameBombManager_Final()
{
	delete[] g_Bomb;
}

/*============================================================
�@�@�@�@�@�@�@���e�̐���
============================================================*/
void GameBombManager_Spawn()
{
	if (g_BombCount <= MAX_BOMB) {
		for (int i = 0; i < MAX_BOMB; i++) {
			if (g_Bomb[i]->GetBombIsEnable()) continue;

			float RandomSpawnerX = (float)(rand() % 21 - 10);
			float RandomSpawnerZ = (float)(rand() % 21 - 10);

			g_Bomb[i]->BombSpawn({ RandomSpawnerX,18.0f, RandomSpawnerZ });
			break;
		}
	}
}


int GetBombModelID()
{
	return g_XmodelBomb;
}

void BombExplode(int index)
{
	g_Bomb[index]->BombExplode();
}

void BombKnockBackDir(int index, int AttackType, D3DXVECTOR3 Dir)
{
	g_Bomb[index]->BombKnockBack(Dir, AttackType);
}

void BombKnockBack(int index)
{
	g_Bomb[index]->BombKnockBackEnable();
}

bool GetBombKnockBackEnable(int index)
{
	return g_Bomb[index]->GetIsKnockBack();
}

CircleCollision GetBombCollision(int index)
{
	return g_Bomb[index]->GetCollision();
}
CircleCollision GetBombAttackZone(int index)
{
	return g_Bomb[index]->GetAttackZone();
}
bool GetBombEnable(int index)
{
	return g_Bomb[index]->GetBombIsEnable();
}
bool GetBombExplode(int index)
{
	return g_Bomb[index]->GetBombIsExplode();
}

/*============================================================
�@�@�@�@�@�@�@���e�̃��b�V�����擾
============================================================*/
LPD3DXMESH* GetBombModelMeshID()
{
	return Model_X_GetMesh(g_XmodelBomb);
}

/*============================================================
�@�@�@�@�@�@�@���e�̐�
============================================================*/
void BombCounting(bool count)
{
	if(count)
	g_BombCount++;
	else{
		g_BombCount--;
	}
	
}