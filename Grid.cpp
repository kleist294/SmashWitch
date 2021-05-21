

#include <d3dx9.h>
#include "mydirect3d.h"
#include "config.h"
#include "Grid.h"
#include <malloc.h>
#include "Camera.h"


//���_�\����
typedef struct Vertex3D_tag
{
	D3DXVECTOR3 Position;
	D3DCOLOR Color;

}Vertex3D;

#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)

static Vertex3D* g_pVertex = NULL;
static int g_VertexCount = 0;
static int g_LineCount = 0;



static float g_Angle = 0;



void Grid_Init(float size, int count, D3DCOLOR color)
{
	g_LineCount = (count + 1) * 2;
	g_VertexCount = g_LineCount * 2;
	g_pVertex = (Vertex3D*)malloc(g_VertexCount * sizeof(Vertex3D));

	float length = size * count;
	float start = -length * 0.5f;
	float end = length * 0.5f;
	int n = g_LineCount;
	//�ꏊ
	for (int i = 0; i < count + 1; i++)
	{
		//�l�ӂ̒��_���
		g_pVertex[    i * 2    ].Position = D3DXVECTOR3(start + size * i , 0.0f ,start);
		g_pVertex[    i * 2 + 1].Position = D3DXVECTOR3(start + size * i, 0.0f, end);
		g_pVertex[n + i * 2    ].Position = D3DXVECTOR3(start, 0.0f, start + size * i);
		g_pVertex[n + i * 2 + 1].Position = D3DXVECTOR3(end, 0.0f, start + size * i);

	}


	for (int i = 0; i < g_VertexCount; i++)
	{
		g_pVertex[i].Color = color;
	}


}
void Grid_Final()
{

}
void Grid_Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//���[���h���W�ϊ��s��̍쐬
	D3DXMATRIX mtxWorld;
	//�P�ʍs��̍쐬
	//D3DXMatrixIdentity(&mtxWorld);//mtxWorld = 1
	//��]�s��쐬
	D3DXMatrixRotationY(&mtxWorld, g_Angle);
	//�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);


	


	//�f�o�C�X��FVF�ݒ�

	pDevice->SetFVF(FVF_VERTEX3D);


	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, NULL);

	//���C�g�𖳌��ɂ���(���K������)
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�|���S����`�悷��
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, g_LineCount, g_pVertex, sizeof(Vertex3D));

}

