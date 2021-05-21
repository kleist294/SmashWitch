
/*============================================================

�@�@�@�@�n�ʂ̏��

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
�@�@�@�@�n�ʂ̏�����
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
�@�@�@�@�n�ʂ̃A�b�v�f�[�g
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
�@�@�@�@�n�ʂ̕`��
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
�@�@�@�@�n�ʂ̈ʒu���̎擾
============================================================*/
D3DXVECTOR3* GetFloorPos(int index)
{
	return &g_floor[index].Pos;
}

/*============================================================
�@�@�@�@�n�ʂ̃��b�V�����̎擾
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