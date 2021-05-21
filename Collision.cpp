
/*============================================================

　　　　　　　　　　　当たり判定の関数

============================================================*/


#include "Collision.h"
#include <d3dx9.h>





/*============================================================
　　　　　　　　　　　円と円の関数
============================================================*/
bool CollisionCircleAndCircleHit(const CircleCollision* pA, const CircleCollision* pB)
{
	//ルートが重いので、平方で比べる
	return D3DXVec3LengthSq(&(pA->Center - pB->Center)) < (pA->radius + pB->radius) * (pA->radius + pB->radius);
}


