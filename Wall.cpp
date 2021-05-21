
#include <d3dx9.h>
#include "Mydirect3d.h"
#include "Config.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Light.h"
#include "Game.h"
#include "Wall.h"


//���_�\����
typedef struct Vertex3D_tag
{
	D3DXVECTOR3 Position;
	//�@���x�N�g���̒����͐�� 1
	D3DXVECTOR3 Normal;
	D3DCOLOR    Color;
	D3DXVECTOR2 TexCoord;

}Vertex3D;


#define MESH_MAX 512

//����
#define FVF_VERTEX3D (D3DFVF_XYZ| D3DFVF_NORMAL| D3DFVF_DIFFUSE|D3DFVF_TEX1)
/*---------------------
�@�@�@�O���[�o���ϐ�
-----------------------*/



static int g_TextureID = INVALID_TEXTURE_ID;




static Vertex3D g_MeshFieldVertexs[(WALL_X + 1) * (WALL_Z + 1)];



//static WORD g_Indexes[] = {
//	
//	3,0,4,1,5,2,
//	2,6,    //�k�ރ|���S��
//	6,3,7,4,8,5
//
//};





//���_�o�b�t�@�C���^�[�t�F�[�X
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
//�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;




void Wall_Init(int HorinzontalCount, int VerticalCount, int HorinzontalSize, int VerticalSize)
{
	g_TextureID = Texture_SetTextureLoadFile("asset\\texture\\icewall.png");


	for (int i = 0; i < HorinzontalCount + 1; i++) {

		for (int j = 0; j < VerticalCount + 1; j++) {

			g_MeshFieldVertexs[i * (VerticalCount + 1) + j].Position = { ((float)VerticalCount * -(float)HorinzontalSize / 2) + ((float)j * (float)HorinzontalSize),0.0,((float)HorinzontalCount * (float)VerticalSize / 2) - ((float)i * (float)HorinzontalSize) };
			g_MeshFieldVertexs[i * (VerticalCount + 1) + j].Normal = { 0.0, 1.0, 0.0 };
			g_MeshFieldVertexs[i * (VerticalCount + 1) + j].Color = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_MeshFieldVertexs[i * (VerticalCount + 1) + j].TexCoord = { (float)j,(float)i };



		}
	}

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}

	//���_�o�b�t�@�[��byte�� , �������� , FVF , ���܂�������, �擾�����C���^�[�t�F�[�X�A�h���X���L�^���邽�߂̃|�C���^�[�A�h���X
	pDevice->CreateVertexBuffer(sizeof(Vertex3D) * (HorinzontalCount + 1) * (VerticalCount + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	//�l�̒��_���U��

	//�S���_�ɖ߂����ߎQ�Ɠ_
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((VerticalCount + 1) * 2) * (HorinzontalCount + 1) + HorinzontalCount * 2), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

	Vertex3D *pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, g_MeshFieldVertexs, sizeof(g_MeshFieldVertexs));
	g_pVertexBuffer->Unlock();

	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);


	int mesh_up = 0;
	int mesh_down = VerticalCount + 1;
	int meshcount = 0;


	for (int i = 0; i < HorinzontalCount; i++)
	{
		for (int j = 0; j < VerticalCount + 1; j++) {

			meshcount = j * 2;


			pIndex[(i * (VerticalCount + 2) * 2) + meshcount] = mesh_down;
			pIndex[(i * (VerticalCount + 2) * 2) + meshcount + 1] = mesh_up;


			mesh_up++;
			mesh_down++;

		}

		if (i != HorinzontalCount - 1)
		{
			pIndex[i * (VerticalCount + 2) * 2 + (VerticalCount + 1) * 2] = mesh_up - 1;
			pIndex[i * (VerticalCount + 2) * 2 + (VerticalCount + 1) * 2 + 1] = mesh_down;
		}
	}

	g_pIndexBuffer->Unlock();

	Texture_Load();

}
void Wall_Final()
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
	Texture_Release(&g_TextureID, 1);
}

void Wall_Draw(int mode, int HorinzontalCount, int VerticalCount, const D3DXMATRIX* pmtxworld)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	Light_Set();

	//�A���r�G���g���C�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(192, 96, 128, 255));

	//�A���r�G���g�}�e���A���̐ݒ�
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);


	//�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ� 
	
	pDevice->SetTransform(D3DTS_WORLD, pmtxworld);


	//�f�o�C�X��FVF�ݒ�

	pDevice->SetFVF(FVF_VERTEX3D);


	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, Texture_GetTexture(g_TextureID));

	//���C���[�t���[����
	if (mode == 1)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	//�\���b�h��
	if (mode == 0)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	//�|���S����`�悷��
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, &g_CubeVertexs, sizeof(Vertex3D));

	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex3D));
	pDevice->DrawIndexedPrimitive
	(D3DPT_TRIANGLESTRIP, 0, 0, (HorinzontalCount + 1) * (VerticalCount + 1), 0, HorinzontalCount * VerticalCount * 2 + (HorinzontalCount - 1) * 4);
}

