
/*============================================================

　　　　地面の状態

============================================================*/


#include <d3dx9.h>
#include "GameFloor.h"
#include "Model_x.h"
#include "GameEnemyManager.h"

typedef struct 
{
	D3DXVECTOR3 Pos;
	bool IsEnable;
	D3DXMATRIX MtxW, MtxT;

}Floor;


static int g_XModelFloor = INVALID_MODEL_X_ID;
static int g_XModelFloorRing1 = INVALID_MODEL_X_ID;
static int g_XModelFloorRing2 = INVALID_MODEL_X_ID;
static Floor g_floor[3];

/*============================================================
　　　　地面の初期化
============================================================*/
void GameFloor_Init()
{
	g_XModelFloor = Model_X_Load("asset\\texture\\model\\floor.x");
	g_XModelFloorRing1 = Model_X_Load("asset\\texture\\model\\floorring1.x");
	g_XModelFloorRing2 = Model_X_Load("asset\\texture\\model\\floorring2.x");



	for (int i = 0; i < 3; i++) {
		g_floor[i].IsEnable = true;
		g_floor[i].Pos = { 0.0f,0.0f,0.0f };
	}
}

/*============================================================
　　　　地面のアップデート
============================================================*/
void GameFloor_Update()
{
	if (GetEnemyWave() >= 2)
	{
		g_floor[2].Pos.y -= 0.05f;
	}
	if (GetEnemyWave() >= 4)
	{
		g_floor[1].Pos.y -= 0.05f;
	}
		
	for (int i = 0; i < 3; i++) {
		if (g_floor[i].Pos.y <= -5.0f)
		{
			g_floor[i].IsEnable = false;
		}
	}

}

/*============================================================
　　　　地面の描画
============================================================*/
void GameFloor_Draw()
{
	

	
	for (int i = 0; i < 3; i++) {
		D3DXMatrixTranslation(&g_floor[i].MtxT, g_floor[i].Pos.x, g_floor[i].Pos.y, g_floor[i].Pos.z);

		g_floor[i].MtxW = g_floor[i].MtxT;


	if (g_floor[i].IsEnable == true) {
		switch(i) {
		case 0:
			Model_X_Draw(g_XModelFloor, &g_floor[i].MtxW);
			break;
		case 1:
			Model_X_Draw(g_XModelFloorRing1, &g_floor[i].MtxW);
			break;
		case 2:
			Model_X_Draw(g_XModelFloorRing2, &g_floor[i].MtxW);
			break;
			
		}
	}
	}
}
void GameFloor_Final()
{


}

/*============================================================
　　　　地面の位置情報の取得
============================================================*/
D3DXVECTOR3* GetFloorPos(int index)
{
	return &g_floor[index].Pos;
}

/*============================================================
　　　　地面のメッシュ情報の取得
============================================================*/
LPD3DXMESH* GetFloorModelID(int index)
{
	switch (index) {
	case 0:
		return Model_X_GetMesh(g_XModelFloor);
	case 1:
		return Model_X_GetMesh(g_XModelFloorRing1);
	case 2:
		return Model_X_GetMesh(g_XModelFloorRing2);
	}
}