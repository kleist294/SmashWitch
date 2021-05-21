
/*============================================================

　　　　草の配置

============================================================*/


#include <d3dx9.h>
#include "GameGrass.h"
#include "Model_x.h"
#include "GameEnemyManager.h"
#include "Collision.h"

typedef struct
{
	D3DXVECTOR3 Pos;
	bool IsEnable;
	D3DXMATRIX MtxW, MtxT, MtxR;
}Grass;


static int g_XModelGrass = INVALID_MODEL_X_ID;

static Grass* g_Grass[MAX_GRASS];

/*============================================================
　　　　地面の初期化
============================================================*/
void GameGrass_Init()
{
	g_XModelGrass = Model_X_Load("asset\\texture\\model\\grass.x");


	for (int i = 0; i < MAX_GRASS; i++) {
		g_Grass[i] = new Grass;
		g_Grass[i]->IsEnable = true;
		g_Grass[i]->Pos = { 0.0f,0.0f,0.0f };

	}





	g_Grass[0]->Pos = { 6.0f,0.0f,-4.0f };
	
	g_Grass[1]->Pos = { -12.0f,0.0f,1.4f };
	g_Grass[2]->Pos = { 14.0f,0.0f,-10.5f };
	g_Grass[3]->Pos = { 13.0f,0.0f,5.4f };
	g_Grass[20]->Pos = { -7.0f,0.0f,5.0f };
	g_Grass[21]->Pos = { -7.0f,0.0f,-13.0f };
	g_Grass[22]->Pos = { 1.0f,0.0f,8.0f };
	g_Grass[23]->Pos = { 2.0f,0.0f,-12.0f };

	g_Grass[24]->Pos = { 3.0f,0.0f,-4.0f };
	g_Grass[25]->Pos = { -1.0f,0.0f,2.0f };
	g_Grass[26]->Pos = { 10.0f,0.0f,5.0f };
	g_Grass[27]->Pos = { -5.0f,0.0f,-4.0f };
	g_Grass[28]->Pos = { 7.0f,0.0f,-8.0f };
	g_Grass[29]->Pos = { -2.0f,0.0f,-10.0f };
	g_Grass[30]->Pos = { 0.0f,0.0f,-15.0f };
	g_Grass[31]->Pos = { 1.0f,0.0f,13.0f };
	g_Grass[32]->Pos = { -14.0f,0.0f,-5.0f };
	g_Grass[33]->Pos = { 9.0f,0.0f,-2.0f };

	g_Grass[4]->Pos = { -20.0f,0.0f,-10.5f };
	g_Grass[5]->Pos = { 20.0f,0.0f,10.5f };
	g_Grass[6]->Pos = { -20.0f,0.0f,10.5f };
	g_Grass[7]->Pos = { 20.0f,0.0f,-10.5f };
	g_Grass[8]->Pos = { 10.5f,0.0f,-20.0f };
	g_Grass[9]->Pos = { -10.5f,0.0f,20.0f };
	g_Grass[10]->Pos = { 10.5f,0.0f,20.0f };
	g_Grass[11]->Pos = { -10.5f,0.0f,-20.0f };

	g_Grass[12]->Pos = { 18.5f,0.0f,18.5f };
	g_Grass[13]->Pos = { 18.5f,0.0f,-18.5f };
	g_Grass[14]->Pos = { -18.5f,0.0f,18.5f };
	g_Grass[15]->Pos = { -18.5f,0.0f,-18.5f };
	g_Grass[16]->Pos = { -26.0f,0.0f,0.0f };
	g_Grass[17]->Pos = { 26.0f,0.0f,0.0f };
	g_Grass[18]->Pos = { 0.0f,0.0f,26.0f };
	g_Grass[19]->Pos = { 0.0f,0.0f,-26.0f };



	 D3DXMatrixRotationY(&g_Grass[0]->MtxR,  D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[1]->MtxR,   D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[2]->MtxR,   D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[3]->MtxR,   D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[20]->MtxR,  D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[21]->MtxR,  D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[22]->MtxR,  D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[23]->MtxR,  D3DXToRadian(180));
	D3DXMatrixRotationY(&g_Grass[24]->MtxR,  D3DXToRadian(180));
	D3DXMatrixRotationY(&g_Grass[25]->MtxR,  D3DXToRadian(180));
	D3DXMatrixRotationY(&g_Grass[26]->MtxR,  D3DXToRadian(180));
	D3DXMatrixRotationY(&g_Grass[27]->MtxR,  D3DXToRadian(180));
	D3DXMatrixRotationY(&g_Grass[28]->MtxR,  D3DXToRadian(0));
	D3DXMatrixRotationY(&g_Grass[29]->MtxR,  D3DXToRadian(0));
	D3DXMatrixRotationY(&g_Grass[30]->MtxR,  D3DXToRadian(0));
	D3DXMatrixRotationY(&g_Grass[31]->MtxR,  D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[32]->MtxR,  D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[33]->MtxR,  D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[4]->MtxR,   D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[5]->MtxR,   D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[6]->MtxR,   D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[7]->MtxR,   D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[8]->MtxR,   D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[9]->MtxR,   D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[10]->MtxR,  D3DXToRadian(90));
	D3DXMatrixRotationY(&g_Grass[11]->MtxR,  D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[12]->MtxR,  D3DXToRadian(-90));
	D3DXMatrixRotationY(&g_Grass[13]->MtxR,  D3DXToRadian(0));
	D3DXMatrixRotationY(&g_Grass[14]->MtxR,  D3DXToRadian(0));
	D3DXMatrixRotationY(&g_Grass[15]->MtxR,  D3DXToRadian(0));
	D3DXMatrixRotationY(&g_Grass[16]->MtxR,  D3DXToRadian(-180));
	D3DXMatrixRotationY(&g_Grass[17]->MtxR,  D3DXToRadian(-180));
	D3DXMatrixRotationY(&g_Grass[18]->MtxR,  D3DXToRadian(-180));
	D3DXMatrixRotationY(&g_Grass[19]->MtxR,  D3DXToRadian(-180));










}

/*============================================================
　　　　草のアップデート
============================================================*/
void GameGrass_Update()
{
	if (GetEnemyWave() >= 2)
	{
		g_Grass[12]->Pos.y -= 0.1f;
		g_Grass[13]->Pos.y -= 0.1f;
		g_Grass[14]->Pos.y -= 0.1f;
		g_Grass[15]->Pos.y -= 0.1f;
		g_Grass[16]->Pos.y -= 0.1f;
		g_Grass[17]->Pos.y -= 0.1f;
		g_Grass[18]->Pos.y -= 0.1f;
		g_Grass[19]->Pos.y -= 0.1f;


	}
	if (GetEnemyWave() >= 4)
	{
		g_Grass[4]->Pos.y -= 0.1f;
		g_Grass[5]->Pos.y -= 0.1f;
		g_Grass[6]->Pos.y -= 0.1f;
		g_Grass[7]->Pos.y -= 0.1f;
		g_Grass[8]->Pos.y -= 0.1f;
		g_Grass[9]->Pos.y -= 0.1f;
		g_Grass[10]->Pos.y -= 0.1f;
		g_Grass[11]->Pos.y -= 0.1f;
	}

	for (int i = 0; i < MAX_GRASS; i++) {
		if (g_Grass[i]->Pos.y <= -10.0f)
		{
			g_Grass[i]->IsEnable = false;
		}
	}



}

/*============================================================
　　　　草の描画
============================================================*/
void GameGrass_Draw()
{
	for (int i = 0; i < MAX_GRASS; i++) {
		D3DXMatrixTranslation(&g_Grass[i]->MtxT, g_Grass[i]->Pos.x, g_Grass[i]->Pos.y, g_Grass[i]->Pos.z);

		g_Grass[i]->MtxW = g_Grass[i]->MtxR * g_Grass[i]->MtxT;


		if (g_Grass[i]->IsEnable == true) {
			Model_X_Draw(g_XModelGrass, &g_Grass[i]->MtxW);
		}

	}
}
void GameGrass_Final()
{

}

/*============================================================
　　　　草が存在しているか？
============================================================*/
bool GetGrassIsEnable(int index)
{
	return g_Grass[index]->IsEnable;
}

/*============================================================
　　　　草の位置の取得
============================================================*/
D3DXVECTOR3* GetGrassPos(int index)
{
	return &g_Grass[index]->Pos;
}

/*============================================================
　　　　草のメッシュ情報の取得
============================================================*/
LPD3DXMESH* GetGrassModelID(int index)
{
	return Model_X_GetMesh(g_XModelGrass);
}

