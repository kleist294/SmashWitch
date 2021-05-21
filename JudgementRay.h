#pragma once

#ifndef _JUDGEMENT_RAY_H_
#define _JUDGEMENT_RAY_H_
#include <d3dx9.h>

typedef enum {

	ENEMY_SLIME,
	ENEMY_GHOST,
	BOMB,
	HAMMER_EFFECT,
	BULLET,
	JUDGEMENT_RAYMAX


}TYPE;



bool JudgementRay_Set(D3DXVECTOR3 ray, D3DXVECTOR3 vdir, D3DXVECTOR3 object, LPD3DXMESH* pMesh, float* pdist);

bool JudgementRay_PlayerGround_Check(float ray_dist, float* floor_distance);
bool JudgementRay_ObjectGround_Check(D3DXVECTOR3 Pos, float ray_dist, float* floor_distance, int type);
bool JudgementRay_PlayerObject_Check(D3DXVECTOR3 PlayerDir, float ray_dist, float* floor_distance);
bool JudgementRay_ObjectAndObject_Check(D3DXVECTOR3 Pos, D3DXVECTOR3 dir, float ray_dist, float* floor_distance, int type);

#endif