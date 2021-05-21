#pragma once
#ifndef COLLISION_H_
#define COLLISION_H_
#include <d3d9.h>
#include <d3dx9.h>


typedef struct {

	D3DXVECTOR3 Center;
	float radius;


}CircleCollision;




bool CollisionCircleAndCircleHit(const CircleCollision* pA, const CircleCollision* pB);



#endif