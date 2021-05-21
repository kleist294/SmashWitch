
/*============================================================

�@�@�@�@�@�@�@�@�@�@�@�J�����̐���

============================================================*/

#include <d3dx9.h>

#include "Mydirect3d.h"
#include "Config.h"
#include "Keylogger.h"
#include "GamePlayerManager.h"
#include "Game.h"
#include "Mouse.h"
#include "DebugFont.h"

#define MOVING_SPEEDMAX (1.0f / 30)
#define ROTATIONAL_SPEEDMAX (1.0f)
#define MOVING_ACCEL (0.04f)
#define MOVING_ATTENUATION_RATE (0.8f)

static D3DXVECTOR3 g_vFront(0.0, 0.0f, -1.0f);
static D3DXVECTOR3 g_vRight(1.0, 0.0f, 0.0f);
static D3DXVECTOR3 g_vUp(0.0, 1.0f, 0.0f);
static D3DXVECTOR3 g_At(0.0, 0.0f, 0.0f);
static D3DXVECTOR3 g_vPos(0.0, 1.0f, -5.0f);
static D3DXVECTOR3 g_vMovementSpeed(0.0, 0.0f, 0.0f);
static float g_RotationalSpeed = 0.04f;
static D3DXMATRIX g_MtxView;
static D3DXVECTOR3 g_PlayerCameraPos(0.0f, 1.0f, 3.5f);
static float g_PlayerCameraLength = 0;
static D3DXVECTOR3 g_PlayerCameraVector(0.0f, 0.0f, 0.0f);
static float g_vFrontLength = 0;
static float g_vRightLength = 0;
static float g_vUpLength = 0;

static float g_CosFrontAndCamera = 0;
static float g_CosRightAndCamera = 0;
static float g_CosUpAndCamera = 0;
static float g_CameraRange = 0;

static Mouse_State g_MouseState;



/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�J�����̏�����
============================================================*/
void Camera_Init() 
{
	g_vFront = D3DXVECTOR3(0.0, 0.0f, 1.0f);
	g_vRight = D3DXVECTOR3(1.0, 0.0f, 0.0f);
	g_CameraRange = 3.5f;

	//�O�����x�N�g���ƉE�����x�N�g���ƒ��p�ɂȂ������x�N�g����
	//�O�ςŋ��߂邱�Ƃ��ł���
	D3DXVec3Cross(&g_vUp, &g_vFront, &g_vRight);

	//�e�x�N�g���𐳋K�� (����1)�ɂ���
	D3DXVec3Normalize(&g_vFront, &g_vFront);
	D3DXVec3Normalize(&g_vUp, &g_vUp);
	D3DXVec3Normalize(&g_vRight, &g_vRight);


	g_vPos = D3DXVECTOR3(0.0, 1.0f, -5.0f);
	g_vMovementSpeed = D3DXVECTOR3(0.0, 0.0f, 0.0f);
	g_RotationalSpeed = 0.05f;
	g_At = D3DXVECTOR3(0.0, 0.0f, 0.0f);
	D3DXMatrixIdentity(&g_MtxView);

	g_vPos = GetPlayerPos() - g_vFront * 3.5f + g_vUp;
}

/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�J�����̃A�b�v�f�[�g
============================================================*/
void Camera_Update()
{
	D3DXVECTOR3 Dir(0.0f, 0.0f, 0.0f);//�J�����̕���

	//W�L�[�@
	if (KeyloggerPress(KL_UP) )
	{
		D3DXVECTOR3 v = g_vFront;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		Dir += v;	
	}
	//S�L�[�@
	if (KeyloggerPress(KL_DOWN) )
	{
		D3DXVECTOR3 v = g_vFront;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		//g_vPos -= v * 0.1f;
		Dir -= v;
	}
	//A�L�[
	if (KeyloggerPress(KL_LEFT) )
	{

		Dir -= g_vRight * 0.01f;
	}
	//D�L�[
	if (KeyloggerPress(KL_RIGHT) )
	{
		
		Dir += g_vRight * 0.01f;
	}
	
	
	//�����L�[�@���܂��̓}�E�X����ړ�
	if (KeyloggerPress(KL_TURN_UP) || (float)GetCursorY() < 0.0f)
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationAxis(&mtxR, &g_vRight, -g_RotationalSpeed);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);
	
		//D3DXVec3Transform : ���W�ϊ������4�����x�N�g���ŏo��(w = 1��ǉ����ĉ��Z)
		//D3DXVec3TransformCoord : ���W�ϊ������3�����x�N�g���ŏo��(w = 1��ǉ����ĉ��Z�Aw�������폜)
		//D3DXVec3TransformNormal : ���W�ϊ������3�����x�N�g���ŏo��(w = 0��ǉ����ĉ��Z�Aw�������폜)
	
	}
	//�����L�[�@���܂��̓}�E�X�����ړ�
	if (KeyloggerPress(KL_TURN_DOWN) || (float)GetCursorY() > 0.0f)
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationAxis(&mtxR, &g_vRight, g_RotationalSpeed);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);
	}

	//�����L�[�@���܂��̓}�E�X�����ړ�
	if (KeyloggerPress(KL_TURN_LEFT) || (float)GetCursorX() < 0.0f)
	{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, -g_RotationalSpeed);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);


	}

	//�����L�[�@���܂��̓}�E�X���E�ړ�
	else if (KeyloggerPress(KL_TURN_RIGHT) || (float)GetCursorX() > 0.0f)
	{
		D3DXVECTOR3 temp_at = g_vPos + g_vFront * 2.5f;

		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, g_RotationalSpeed);
		D3DXVec3TransformNormal(&g_vFront, &g_vFront, &mtxR);
		D3DXVec3TransformNormal(&g_vRight, &g_vRight, &mtxR);
		D3DXVec3TransformNormal(&g_vUp, &g_vUp, &mtxR);
	}

	//�}�C�i�X�L�[�i-�j
	if (KeyloggerPress(KL_NEAR))
	{
		g_CameraRange -= 0.1f;
		if (g_CameraRange <= 1.0f)
		{
			g_CameraRange = 1.0f;
		}
	}
	//�v���X�L�[�i+�j
	if (KeyloggerPress(KL_FAR))
	{
		g_CameraRange += 0.1f;
		if (g_CameraRange >= 6.0f)
		{
			g_CameraRange = 6.0f;
		}
	}

	//�J�����ʒu�̌v�Z
	g_vPos = GetPlayerPos() + g_vUp * (g_CameraRange/3.5f)  - g_vFront * g_CameraRange;

	if (g_vPos.y <= 0.2f)
	{
		g_vPos.y = 0.2f;
	}

		


		



		


	//�����x�̌v�Z
	D3DXVec3Normalize(&Dir,&Dir);
	g_vMovementSpeed += Dir * MOVING_ACCEL;

	//���x�̗}��
	if (D3DXVec3Length(&g_vMovementSpeed) > MOVING_SPEEDMAX)
	{
		D3DXVec3Normalize(&g_vMovementSpeed, &g_vMovementSpeed);
		g_vMovementSpeed *= MOVING_SPEEDMAX;
	}

	//�ړ�
	g_vPos += g_vMovementSpeed;
	
	//���x�̌���
	g_vMovementSpeed *= MOVING_ATTENUATION_RATE;
	
	//�����_�����߂� (�J�����̈ʒu+�x�N�g��)

	g_At = g_vPos + g_vFront * g_CameraRange;
	
	D3DXMatrixLookAtLH(&g_MtxView, &g_vPos, &g_At, &g_vUp);


	
	

}


/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�J�����̎���
============================================================*/
void Camera_SetMatrixToDevice()
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();



	//�r���[���W�ϊ��s��̍쐬
	//D3DXMATRIX mtxView;

                                        //�����_
//	D3DXMatrixLookAtLH(&g_MtxView, &g_vPos, &g_At, &g_vUp);
//	//�f�o�C�X�Ƀr���[�ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_MtxView);

	//�v���W�F�N�V����(�p�[�X�y�N�e�B�u)���W�ϊ��s��̍쐬
	D3DXMATRIX mtxProjection;
	float fovy = D3DXToRadian(60);
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	float z_near = 0.1f;
	float z_far = 500.0f;
	D3DXMatrixPerspectiveFovLH(&mtxProjection, fovy, aspect, z_near, z_far);
	//�f�o�C�X�Ƀv���W�F�N�V�����ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

}

/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�J�����̌����擾
============================================================*/
const D3DXVECTOR3* Camera_GetFrontVector(void)
{
	return &g_vFront;
}

/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�J�����̉E�����擾
============================================================*/
const D3DXVECTOR3* Camera_GetRightVector(void)
{
	return &g_vRight;
}

/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�J�����̏�����擾
============================================================*/
const D3DXVECTOR3* Camera_GetUpVector(void)
{
	return &g_vUp;
}

/*============================================================
�@�@�@�@�@�@�@�@�@�@�@�J�����̈ʒu�擾
============================================================*/
const D3DXVECTOR3* Camera_GetPosition(void)
{
	return &g_vPos;
}


const D3DXVECTOR3* Camera_GetAt(void)
{
	return &g_At;
}


const D3DXMATRIX& Camera_GetViewMatrix() 
{
	return g_MtxView;

}