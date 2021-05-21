
/*============================================================

�@�@�@�@�@�@�@�@�@�@�G�t�F�N�g�̃A�j���[�V����(�Z�̃e�N�X�`��)

============================================================*/


#include <d3dx9.h>
#include "Mydirect3d.h"
#include "Config.h"
#include "TextureManager.h"

//���_�\����
typedef struct Shadow3D_tag
{
	D3DXVECTOR3 Position;
	D3DCOLOR    Color;
	D3DXVECTOR2 TexCoord;

}Shadow3D;

//����
#define FVF_VERTEX3D (D3DFVF_XYZ| D3DFVF_DIFFUSE|D3DFVF_TEX1)

static int g_TextureID = INVALID_TEXTURE_ID;
static D3DCOLOR g_color = 0xffffffff;

/*============================================================
�@�@�@�@�@�@�G�t�F�N�g�̏�����
============================================================*/
void DropEffect_Init()
{
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\EnemyDrop.png");

}

/*============================================================
�@�@�@�@�@�@�G�t�F�N�g�̕`��
============================================================*/
void DropEffect_Draw(float x, float y, float z, float size)
{
	Shadow3D g_ShadowVertexs[] =
	{
		//front
		{{-0.5f, 0.0f, 0.5f},g_color,{0.0f,0.0f}},
		{{ 0.5f, 0.0f, 0.5f},g_color,{1.0f,0.0f}},
		{{-0.5f,-0.0f,-0.5f},g_color,{0.0f,1.0f}},
		{{ 0.5f,-0.0f,-0.5f},g_color,{1.0f,1.0f}},
	};

	D3DXMATRIX mtxworld, mtxT, mtxS;

	D3DXMatrixTranslation(&mtxT, x, y, z);
	D3DXMatrixScaling(&mtxS, size, size, size);
	mtxworld = mtxS * mtxT;


	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	

	pDevice->SetTransform(D3DTS_WORLD, &mtxworld);
	pDevice->SetFVF(FVF_VERTEX3D);
	pDevice->SetTexture(0, Texture_GetTexture(g_TextureID));
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_ShadowVertexs, sizeof(Shadow3D));
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	

}

/*============================================================
�@�@�@�@�@�@�G�t�F�N�g�̐F�ݒ�
============================================================*/
void DropEffect_SetColor(D3DCOLOR color)
{
	g_color = color;
}