

/*============================================================
　　　　　　
	  　　　　　石の配置

============================================================*/


#include <d3dx9.h>
#include "GameStone.h"
#include "Model_x.h"
#include "GameEnemyManager.h"
#include "Collision.h"

typedef struct
{
	D3DXVECTOR3 Pos;
	int Model;
	bool IsEnable;
	D3DXMATRIX MtxW, MtxT, MtxR;
}Stone;


typedef struct
{
	D3DXVECTOR3 Pos;
	int Model;
	D3DXMATRIX MtxW, MtxT, MtxR;
}StoneHitBox;


static int g_XModelStone = INVALID_MODEL_X_ID;
static int g_XModelStone2 = INVALID_MODEL_X_ID;

static int g_XModelStoneHitBox = INVALID_MODEL_X_ID;
static int g_XModelStone2HitBox = INVALID_MODEL_X_ID;

static Stone* g_Stone[MAX_STONE];
static StoneHitBox* g_StoneHitBox[MAX_STONE];

/*============================================================
　　　　　　　　　　　石の初期化
============================================================*/
void GameStone_Init()
{
	g_XModelStone = Model_X_Load("asset\\texture\\model\\stone.x");
	g_XModelStone2 = Model_X_Load("asset\\texture\\model\\stone2.x");

	g_XModelStoneHitBox = Model_X_Load("asset\\texture\\model\\stonehitbox.x");
	g_XModelStone2HitBox = Model_X_Load("asset\\texture\\model\\stone2hitbox.x");


	for (int i = 0; i < MAX_STONE; i++) {
		g_Stone[i] = new Stone;
		g_Stone[i]->IsEnable = true;
		g_Stone[i]->Pos = { 0.0f,0.0f,0.0f };
		
	}
	for (int i = 0; i < MAX_STONE; i++) {
		g_StoneHitBox[i] = new StoneHitBox;
		g_StoneHitBox[i]->Pos = { 0.0f,0.0f,0.0f };

	}



	g_Stone[0]->Pos = { -10.0f,0.0f,-4.0f };
	g_Stone[1]->Pos = { 13.5f,0.0f,-5.4f };
	g_Stone[2]->Pos = { 5.5f,0.0f,-15.5f };
	g_Stone[3]->Pos = { -4.0f,0.0f,5.4f };

	g_Stone[0]->Model = g_XModelStone;
	g_Stone[1]->Model = g_XModelStone;
	g_Stone[2]->Model = g_XModelStone2;
	g_Stone[3]->Model = g_XModelStone2;


	for (int i = 0; i < MAX_STONE; i++) {
		g_StoneHitBox[i] = new StoneHitBox;
		g_StoneHitBox[i]->Pos = g_Stone[i]->Pos;
		if(g_Stone[i]->Model == g_XModelStone)
		{
			g_StoneHitBox[i]->Model = g_XModelStoneHitBox;
		}
		else if(g_Stone[i]->Model == g_XModelStone2)
		{
			g_StoneHitBox[i]->Model = g_XModelStone2HitBox;
		}
	}


}
void GameStone_Update()
{
	




}

/*============================================================
　　　　　　　　　　　石の描画
============================================================*/
void GameStone_Draw()
{
	for (int i = 0; i < MAX_STONE; i++) {
		D3DXMatrixTranslation(&g_Stone[i]->MtxT, g_Stone[i]->Pos.x, g_Stone[i]->Pos.y, g_Stone[i]->Pos.z);

		g_Stone[i]->MtxW = g_Stone[i]->MtxT;


		if (g_Stone[i]->IsEnable == true) {
			Model_X_Draw(g_Stone[i]->Model, &g_Stone[i]->MtxW);	
			//Model_X_Draw(g_StoneHitBox[i]->Model, &g_Stone[i]->MtxW);
		}

	}
}
void GameStone_Final()
{

}

/*============================================================
　　　　　　　　　　　石が存在しているか？
============================================================*/
bool GetStoneIsEnable(int index)
{
	return g_Stone[index]->IsEnable;
}

/*============================================================
　　　　　　　　　　　石の位置を取得する
============================================================*/
D3DXVECTOR3* GetStonePos(int index)
{
	return &g_StoneHitBox[index]->Pos;
}

/*============================================================
　　　　　　　　　　　石のメッシュ情報を取得する
============================================================*/
LPD3DXMESH* GetStoneModelID(int index)
{

	return Model_X_GetMesh(g_StoneHitBox[index]->Model);

}

