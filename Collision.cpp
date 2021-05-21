
/*============================================================

�@�@�@�@�@�@�@�@�@�@�@�����蔻��̊֐�

============================================================*/


#include "Collision.h"
#include <d3dx9.h>





/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�~�Ɖ~�̊֐�
============================================================*/
bool CollisionCircleAndCircleHit(const CircleCollision* pA, const CircleCollision* pB)
{
	//���[�g���d���̂ŁA�����Ŕ�ׂ�
	return D3DXVec3LengthSq(&(pA->Center - pB->Center)) < (pA->radius + pB->radius) * (pA->radius + pB->radius);
}


