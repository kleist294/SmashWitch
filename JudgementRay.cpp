/*============================================================

　　　　　　　　　レイを使用したの当たり判定

============================================================*/

#include <d3dx9.h>
#include "JudgementRay.h"
#include "GamePlayerManager.h"
#include "Model_x.h"
#include "GameFloor.h"
#include "GameBombManager.h"
#include "GameTree.h"
#include "GameStone.h"

//向き
static const D3DXVECTOR3 vGrand(0.0f, -1.0f, 0.0f);


// 地面との判定用
bool JudgementRay_Set(D3DXVECTOR3 ray, D3DXVECTOR3 vdir, D3DXVECTOR3 object, LPD3DXMESH* pMesh, float* pDist)
{
	BOOL boHit = FALSE;
	D3DXMATRIX mWorld, mRotation;
	D3DXVECTOR3 vStart;
	D3DXVECTOR3 vDirection = vdir;
	vStart = ray;
	D3DXMatrixTranslation(&mWorld, object.x, object.y, object.z);
	D3DXMatrixInverse(&mWorld, NULL, &mWorld);
	D3DXVec3TransformCoord(&vStart, &vStart, &mWorld);
	D3DXVec3TransformNormal(&vDirection, &vDirection, &mWorld);
	D3DXVec3Normalize(&vDirection, &vDirection);

	HRESULT hr = D3DXIntersect(*pMesh, &vStart, &vDirection, &boHit, NULL, NULL, NULL, pDist, NULL, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	if (boHit)
	{
   		return true;
	}
	return false;
}


/*============================================================
　　　　　　　　　プレイヤーと地面オブジェクトの判定(下向き)
============================================================*/
bool JudgementRay_PlayerGround_Check(float RayDist,float* FloorDistance)
{
	


		float Dist = 0.0f;

		//              プレイヤーの頂上座標
		D3DXVECTOR3 Pos(GetPlayerPos().x, GetPlayerPos().y + 0.725f, GetPlayerPos().z);



		for (int i = 0; i < MAX_BOMB; i++) {
			//                                  ボムの座標            ボムのメッシュ                   距離(頭頂上からボムの距離)
			if (GetBombEnable(i)) {
				if (JudgementRay_Set(Pos, vGrand, GetBombCollision(i).Center, GetBombModelMeshID(), &Dist) && Dist <= RayDist)
				{
					BombExplode(i);
					*FloorDistance = Dist;
					return true;
				}
			}
		}



		for (int i = 0; i < MAX_TREE; i++) {
			if (GetTreeIsEnable(i)) {
				//                                  樹の座標            樹のメッシュ                   距離(頭頂上から樹の距離)
				if (JudgementRay_Set(Pos, vGrand, *GetTreePos(i), GetTreeModelID(i), &Dist) && Dist <= RayDist)
				{
					*FloorDistance = Dist;
					return true;
				}
			}
		}

		for (int i = 0; i < MAX_STONE; i++) {
			if (GetStoneIsEnable(i)) {
				//                                  石の座標            石のメッシュ                   距離(頭頂上から石の距離)
				if (JudgementRay_Set(Pos, vGrand, *GetStonePos(i), GetStoneModelID(i), &Dist) && Dist <= RayDist)
				{
					*FloorDistance = Dist;
					return true;
				}
			}
		}


		for (int i = 0; i < 3; i++) {
			//                                  床の座標            床のメッシュ                   距離(頭頂上から地面の距離)
			if (JudgementRay_Set(Pos, vGrand, *GetFloorPos(i), GetFloorModelID(i), &Dist) && Dist <= RayDist)
			{
				*FloorDistance = Dist;
				return true;
			}
		
		}



	return false;
}
/*============================================================
　　　　　　　　　オブジェクトと地面の判定
============================================================*/
bool JudgementRay_ObjectGround_Check(D3DXVECTOR3 pPos, float RayDist, float* FloorDistance,int type)
{
	


	float Dist = 0.0f;
	//オブジェクトの頂上座標変数
	D3DXVECTOR3 Pos = { 0.0f,0.0f,0.0f };
	
	//オブジェクトのタイプ
	switch (type)
	{case ENEMY_GHOST:
		Pos = { pPos.x, pPos.y + 0.5f, pPos.z };
		break;
	case ENEMY_SLIME:
		Pos = { pPos.x, pPos.y + 0.5f, pPos.z };
		break;
	case BOMB:
		Pos = { pPos.x, pPos.y + 0.5f, pPos.z };
		break;
	case HAMMER_EFFECT:
		Pos = { pPos.x, pPos.y + 0.0f, pPos.z };
	}


	for (int i = 0; i < 3; i++) {
		//                                  床の座標            床のメッシュ                   距離(オブジェクトから床の距離)
		if (JudgementRay_Set(Pos, vGrand, *GetFloorPos(i), GetFloorModelID(i), &Dist) && Dist <= RayDist)
		{
			*FloorDistance = Dist;
			return true;
		}
	}
	
	for (int i = 0; i < MAX_STONE; i++) {
		if (GetStoneIsEnable(i)) {
			//                                  石の座標            石のメッシュ                   距離(オブジェクトから石の距離)
			if (JudgementRay_Set(Pos, vGrand, *GetStonePos(i), GetStoneModelID(i), &Dist) && Dist <= RayDist && type != ENEMY_GHOST)
			{
				*FloorDistance = Dist;
				return true;
			}
		}
	}

	for (int i = 0; i < MAX_TREE; i++) {
		if (GetTreeIsEnable(i)) {
			//                                  樹の座標            樹のメッシュ                   距離(オブジェクトから樹の距離)
			if (JudgementRay_Set(Pos, vGrand, *GetTreePos(i), GetTreeModelID(i), &Dist) && Dist <= RayDist && type == ENEMY_SLIME)
			{
				*FloorDistance = Dist;
				return true;
			}
		}
	}



	return false;
}

/*============================================================
　　　　　　　　　プレイヤーとオブジェクトの判定(下向き以外)
============================================================*/
bool JudgementRay_PlayerObject_Check(D3DXVECTOR3 PlayerDir,float RayDist, float* FloorDistance)
{
	

	float Dist = 0.0f;
	D3DXVECTOR3 Left = { 0.0f,0.0f,0.0f };


	D3DXMATRIX mtxR;
	D3DXMatrixRotationY(&mtxR, D3DXToRadian(90));

	D3DXVec3TransformNormal(&Left, &PlayerDir, &mtxR);



	//              プレイヤーの座標
	D3DXVECTOR3 Pos(GetPlayerPos().x, GetPlayerPos().y, GetPlayerPos().z);
	D3DXVECTOR3 PosLeft(GetPlayerPos().x + Left.x * 0.3f, Left.y + Left.y * 0.3f, GetPlayerPos().z + Left.z * 0.3f);
	D3DXVECTOR3 PosRight(GetPlayerPos().x - Left.x * 0.3f, GetPlayerPos().y - Left.y * 0.3f, GetPlayerPos().z - Left.z * 0.3f);

	D3DXVECTOR3 PosTree(GetPlayerPos().x, GetPlayerPos().y + 0.725f, GetPlayerPos().z);
	D3DXVECTOR3 PosTreeLeft(GetPlayerPos().x + Left.x * 0.1f, Left.y + Left.y * 0.1f + 0.725f, GetPlayerPos().z + Left.z * 0.1f);
	D3DXVECTOR3 PosTreeRight(GetPlayerPos().x - Left.x * 0.1f, GetPlayerPos().y - Left.y * 0.1f + 0.725f, GetPlayerPos().z - Left.z * 0.1f);


	for (int i = 0; i < MAX_BOMB; i++) {
		if (GetBombEnable(i)) {
			//                                  ボムの座標            ボムのメッシュ                   距離(プレイヤーとオブジェクトの距離)
			if (JudgementRay_Set(Pos, PlayerDir, GetBombCollision(i).Center, GetBombModelMeshID(), &Dist) && Dist <= RayDist)
			{
				*FloorDistance = Dist;
				return true;
			}
			else if (JudgementRay_Set(PosLeft, PlayerDir, GetBombCollision(i).Center, GetBombModelMeshID(), &Dist) && Dist <= RayDist)
			{
				*FloorDistance = Dist;
				return true;
			}
			else if (JudgementRay_Set(PosRight, PlayerDir, GetBombCollision(i).Center, GetBombModelMeshID(), &Dist) && Dist <= RayDist)
			{
				*FloorDistance = Dist;
				return true;
			}
		}

	}

	for (int i = 0; i < MAX_STONE; i++) {
		if (GetStoneIsEnable(i)) {
			//                                  石の座標            石のメッシュ                   距離(プレイヤーとオブジェクトの距離)
			if (JudgementRay_Set(Pos, PlayerDir, *GetStonePos(i), GetStoneModelID(i), &Dist) && Dist <= RayDist)
			{
				*FloorDistance = Dist;
				return true;
			}
			
		}
	}


	for (int i = 0; i < MAX_TREE; i++) {
		if (GetTreeIsEnable(i)) {
			//                                  樹の座標            樹のメッシュ                   距離(プレイヤーとオブジェクトの距離)
			if (JudgementRay_Set(Pos, PlayerDir, *GetTreePos(i), GetTreeModelID(i), &Dist) && Dist <= RayDist)
			{
				*FloorDistance = Dist;
				return true;
			}
			
		}
	}




	return false;
}


/*============================================================
　　　　　　　　　オブジェクト間の判定
============================================================*/
bool JudgementRay_ObjectAndObject_Check(D3DXVECTOR3 pPos, D3DXVECTOR3 dir, float RayDist, float* FloorDistance, int type)
{

	float Dist = 0.0f;
	D3DXVECTOR3 Pos = { pPos.x, pPos.y, pPos.z };
	//D3DXVECTOR3 posLeft = { 0.0f,0.0f,0.0f };
	//D3DXVECTOR3 posRight = { 0.0f,0.0f,0.0f };
	//
	//D3DXVECTOR3 Left = { 0.0f,0.0f,0.0f };
	//D3DXMATRIX mtxR;
	//D3DXMatrixRotationY(&mtxR, D3DXToRadian(90));
	//
	//D3DXVec3TransformNormal(&Left, &dir, &mtxR);


	//オブジェクトの種類
	switch (type)
	{
	case ENEMY_SLIME:
		Pos = { pPos.x, pPos.y , pPos.z };
	
		break;
	case BOMB:
		Pos = { pPos.x, pPos.y , pPos.z };
	
		break;
	case BULLET:
		Pos = { pPos.x, pPos.y, pPos.z };
	
		break;
	}
	
	for (int i = 0; i < MAX_TREE; i++) {
		if (GetTreeIsEnable(i)) {
			//                                  樹の座標            樹のメッシュ                   距離(オブジェクト間の距離)
			if (JudgementRay_Set(Pos, dir, *GetTreePos(i), GetTreeModelID(i), &Dist) && Dist <= RayDist)
			{
				*FloorDistance = Dist;
				return true;
			}
		}
	}
	
	for (int i = 0; i < MAX_STONE; i++) {
		if (GetStoneIsEnable(i)) {
			//                                  石の座標            石のメッシュ                   距離(オブジェクト間の距離)
			if (JudgementRay_Set(Pos, dir, *GetStonePos(i), GetStoneModelID(i), &Dist) && Dist <= RayDist)
			{
				*FloorDistance = Dist;
				return true;
			}
		}
	}
	
	
	
	
	
	return false;
}