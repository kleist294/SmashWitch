
/*============================================================

　　　　　　　　　　　樹の配置

============================================================*/



#include <d3dx9.h>
#include "GameTree.h"
#include "Model_x.h"
#include "GameEnemyManager.h"
#include "collision.h"

typedef struct
{
	D3DXVECTOR3 Pos;
	bool IsEnable;
	D3DXMATRIX MtxW, MtxT,MtxR;
}Tree;

typedef struct
{
	D3DXVECTOR3 Pos;
	D3DXMATRIX MtxW, MtxT, MtxR;
}TreeHitBox;

static int g_XModelTree = INVALID_MODEL_X_ID;
static int g_XModelTreeHitBox = INVALID_MODEL_X_ID;


static Tree* g_Trees[MAX_TREE];
static TreeHitBox* g_TreesHitBox[MAX_TREE];

/*============================================================
　　　　　　　　　　　樹の初期化
============================================================*/
void GameTree_Init()
{
	g_XModelTree = Model_X_Load("asset\\texture\\model\\tree.x");
	g_XModelTreeHitBox = Model_X_Load("asset\\texture\\model\\treehitbox.x");


	for (int i = 0; i < MAX_TREE; i++) {
		g_Trees[i] = new Tree;
		g_Trees[i]->IsEnable = true;
		
	}





	g_Trees[0]->Pos = { 6.0f,0.0f,-4.0f };
	g_Trees[1]->Pos = { -12.0f,0.0f,1.4f };
	g_Trees[2]->Pos = { 14.0f,0.0f,-10.5f };
	g_Trees[3]->Pos = { 13.0f,0.0f,5.4f };
	g_Trees[20]->Pos = { -7.0f,0.0f,5.0f };
	g_Trees[21]->Pos = { -7.0f,0.0f,-13.0f };
	g_Trees[22]->Pos = { 1.0f,0.0f,8.0f };
	g_Trees[23]->Pos = { 2.0f,0.0f,-12.0f };



	g_Trees[4]->Pos = { -20.0f,0.0f,-10.5f };
	g_Trees[5]->Pos = { 20.0f,0.0f,10.5f };
	g_Trees[6]->Pos = { -20.0f,0.0f,10.5f };
	g_Trees[7]->Pos = { 20.0f,0.0f,-10.5f };
	g_Trees[8]->Pos = { 10.5f,0.0f,-20.0f };
	g_Trees[9]->Pos = { -10.5f,0.0f,20.0f };
	g_Trees[10]->Pos = { 10.5f,0.0f,20.0f };
	g_Trees[11]->Pos = { -10.5f,0.0f,-20.0f };

	g_Trees[12]->Pos = { 18.5f,0.0f,18.5f };
	g_Trees[13]->Pos = { 18.5f,0.0f,-18.5f };
	g_Trees[14]->Pos = { -18.5f,0.0f,18.5f };
	g_Trees[15]->Pos = { -18.5f,0.0f,-18.5f };
	g_Trees[16]->Pos = { -26.0f,0.0f,0.0f };
	g_Trees[17]->Pos = { 26.0f,0.0f,0.0f };
	g_Trees[18]->Pos = { 0.0f,0.0f,26.0f };
	g_Trees[19]->Pos = { 0.0f,0.0f,-26.0f };
	
	









	for (int i = 0; i < MAX_TREE; i++) {
		g_TreesHitBox[i] = new TreeHitBox;
		g_TreesHitBox[i]->Pos = g_Trees[i]->Pos;
		g_TreesHitBox[i]->MtxR = g_Trees[i]->MtxR;
	}


}

/*============================================================
　　　　　　　　　　　樹のアップデート
============================================================*/
void GameTree_Update()
{
	if (GetEnemyWave() >= 2)
	{
		g_Trees[12]->Pos.y -= 0.1f;
		g_Trees[13]->Pos.y -= 0.1f;
		g_Trees[14]->Pos.y -= 0.1f;
		g_Trees[15]->Pos.y -= 0.1f;
		g_Trees[16]->Pos.y -= 0.1f;
		g_Trees[17]->Pos.y -= 0.1f;
		g_Trees[18]->Pos.y -= 0.1f;
		g_Trees[19]->Pos.y -= 0.1f;
		

	}
	if (GetEnemyWave() >= 4)
	{
		g_Trees[4]->Pos.y -= 0.1f;
		g_Trees[5]->Pos.y -= 0.1f;
		g_Trees[6]->Pos.y -= 0.1f;
		g_Trees[7]->Pos.y -= 0.1f;
		g_Trees[8]->Pos.y -= 0.1f;
		g_Trees[9]->Pos.y -= 0.1f;
		g_Trees[10]->Pos.y -= 0.1f;
		g_Trees[11]->Pos.y -= 0.1f;
	}

	for (int i = 0; i < MAX_TREE; i++) {
		g_TreesHitBox[i]->Pos = g_Trees[i]->Pos;

	}

	for (int i = 0; i < MAX_TREE; i++) {
		if (g_Trees[i]->Pos.y <= -10.0f)
		{
			g_Trees[i]->IsEnable = false;
		}
	}



}

/*============================================================
　　　　　　　　　　　樹の描画
============================================================*/
void GameTree_Draw()
{
	for (int i = 0; i < MAX_TREE; i++) {
		D3DXMatrixTranslation(&g_Trees[i]->MtxT, g_Trees[i]->Pos.x, g_Trees[i]->Pos.y, g_Trees[i]->Pos.z);

		g_Trees[i]->MtxW = g_Trees[i]->MtxT;


		if (g_Trees[i]->IsEnable == true) {
				Model_X_Draw(g_XModelTree, &g_Trees[i]->MtxW);
				//Model_X_Draw(g_XModelTreeHitBox, &g_Trees[i]->MtxW);
			}
		
	}
}
void GameTree_Final()
{

}

/*============================================================
　　　　　　　　　　　樹が存在しているか？
============================================================*/
bool GetTreeIsEnable(int index)
{
	return g_Trees[index]->IsEnable;
}

/*============================================================
　　　　　　　　　　　樹の位置情報を取得する
============================================================*/
D3DXVECTOR3* GetTreePos(int index)
{
	return &g_Trees[index]->Pos;
}

/*============================================================
　　　　　　　　　　　樹のメッシュ情報を取得する
============================================================*/
LPD3DXMESH* GetTreeModelID(int index)
{
	return Model_X_GetMesh(g_XModelTreeHitBox);
}

