#define _CRT_SECURE_NO_WARNINGS

/*===========================================================

�@�@�@�@�@�@�@�@�QD�摜�̕`��

===========================================================*/


#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "TextureManager.h"
#include "Mydirect3d.h"

typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Color;
	D3DXVECTOR2 Textcoord;
}Vertex2D;

#define FVF_VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//�O���[�o���ϐ�

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL; //���_�o�b�t�@�[�C���^�[�t�F�C�X
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL; //�C���f�b�N�X�o�b�t�@�[�C���^�[�t�F�C�X
static D3DCOLOR g_Color = 0xffffffff;//�|���S���J���[


void Sprite_Init()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	                         //���_�o�b�t�@�[��byte�� , �������� , FVF , ���܂�������, �擾�����C���^�[�t�F�[�X�A�h���X���L�^���邽�߂̃|�C���^�[�A�h���X
	pDevice->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED , &g_pVertexBuffer, NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

}

void Sprite_Draw(int textureID, float dx, float dy)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}


	//�f�o�C�X��FVF�ݒ�

	pDevice->SetFVF(FVF_VERTEX2D);


	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	Vertex2D testhaikei[] = {
		//���_�f�[�^��p�ӂ���
		//�|���S���͕\��������܂� �E��肵�Ȃ��Əo�Ă��Ȃ� �菇���d�v
		//���オ 0,0


		//                                                                                     (x�̃f�[�^,y�̃f�[�^)(1.0f�͈�̃e�N�X�`����)
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(0.0f, 0.0f)},
		{D3DXVECTOR4(dx + w - 0.5f   ,dy + 0.0f - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(1.0f, 0.0f)},
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy +    h - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(0.0f, 1.0f)},
		{D3DXVECTOR4(dx + h - 0.5f   ,dy +    h - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(1.0f, 1.0f)},

		//     WRAP�̏ꍇ    0.5����ɂ��炵�āA�g��������
	};
	//�|���S����`��(�ȈՔ�)
	//����: 1.�`(�_�������ʂ�) 2.�}�`�̐� 3.���_�f�[�^�̐擪�A�h���X 4.�傫��

	//���_�u���b�N�̏�������

	//�C���f�b�N�X�o�b�t�@�̃��b�N����������
	WORD* pI; //LPWORD�� OK
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, 0);
	pI[0] = 0;
	pI[1] = 1;
	pI[2] = 3;
	pI[3] = 0;
	pI[4] = 3;
	pI[5] = 2;
	g_pIndexBuffer->Unlock();


	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));

	pDevice->SetIndices(g_pIndexBuffer);

	
	
	//�f�o�C�X�ɒ��_�o�b�t�@��ݒ�
	//�C���f�b�N�X�f�[�^
	//WORD index������
	//WORD index[] = {0,1,3,0,3,2};

	//�f�o�C�X�ɃC���f�b�N�X�o�b�t�@��ݒ�

	//���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�𗘗p�����v���~�e�B�u�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0 , 0, 4 , 0, 2);





}

void Sprite_Draw(int textureID, float dx, float dy, int tcx, int tcy, int tcw, int tch)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}


	//�f�o�C�X��FVF�ݒ�

	pDevice->SetFVF(FVF_VERTEX2D);


	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;



	
	Vertex2D testhaikei[] = {
		//���_�f�[�^��p�ӂ���
		//�|���S���͕\��������܂� �E��肵�Ȃ��Əo�Ă��Ȃ� �菇���d�v
		//���オ 0,0


		//                                                                                     (x�̃f�[�^,y�̃f�[�^)(1.0f�͈�̃e�N�X�`����)
		{D3DXVECTOR4(dx - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f),       g_Color,D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + tcw - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx - 0.5f,dy + tch - 0.5f , 1.0f , 1.0f),       g_Color,D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + tcw - 0.5f,dy + tch - 0.5f , 1.0f , 1.0f), g_Color,D3DXVECTOR2(u1, v1)},

		//     WRAP�̏ꍇ    0.5����ɂ��炵�āA�g��������
	};
	
	Vertex2D* pV;
	//���_�o�b�t�@�[�̃��b�N�ƃf�[�^�̏�������
	//CPU�����b�N����        0�͑S�������b�N
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, testhaikei, sizeof(testhaikei));
	g_pVertexBuffer->Unlock();


	//���_�o�b�t�@�[�̎w��
	       //SetStreamSource�͏d�v
	pDevice->SetStreamSource(0, g_pVertexBuffer , 0 , sizeof(Vertex2D));

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//MAGFILTER : �g�債���Ƃ��ǂ̃t�B���^�[���g��
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//MINFILTER : �k�������Ƃ��ǂ̃t�B���^�[���g��
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); //MIPFILTER : 

	//�A���t�@�u�����h�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//�������`��F��������`�悷��q�f�a * ������`�悷�郿 + ��ʂq�f�a * (1 - ������`�悷�郿 )
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	

	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//1. LINEAR �� 2.ANISOTROPIC �ٕ���(�d����)
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);




	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
	//D3DPT_POINTLIST : �_
	//D3DPT_LINELIST : ��
	//D3DPT_LINESTRIP : �q�����
	//D3DPT_TRIANGLELIST : ��
	//D3DPT_TRIANGLESTRIP : 


}


void Sprite_Draw(int textureID, float dx, float dy,float dw,float dh, int tcx ,int tcy , int tcw ,int tch , int alpha)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}

	
	//�f�o�C�X��FVF�ݒ�

	pDevice->SetFVF(FVF_VERTEX2D);


	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;




	Vertex2D testhaikei[] = {
		//���_�f�[�^��p�ӂ���
		//�|���S���͕\��������܂� �E��肵�Ȃ��Əo�Ă��Ȃ� �菇���d�v
		//���オ 0,0


		//                                                                                     (x�̃f�[�^,y�̃f�[�^)(1.0f�͈�̃e�N�X�`����)
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f),D3DCOLOR_RGBA(255,255,225,alpha),D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + dw - 0.5f ,dy + 0.0f - 0.5f, 1.0f , 1.0f), D3DCOLOR_RGBA(255,255,225,alpha),D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + dh - 0.5f , 1.0f , 1.0f), D3DCOLOR_RGBA(255,255,225,alpha),D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + dw - 0.5f ,dy + dh - 0.5f , 1.0f , 1.0f),  D3DCOLOR_RGBA(255,255,225,alpha),D3DXVECTOR2(u1, v1)},

		//     WRAP�̏ꍇ    0.5����ɂ��炵�āA�g��������
	};
		
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//MAGFILTER : �g�債���Ƃ��ǂ̃t�B���^�[���g��
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//MINFILTER : �k�������Ƃ��ǂ̃t�B���^�[���g��
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); //MIPFILTER : 

	//�A���t�@�u�����h�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//�������`��F��������`�悷��q�f�a * ������`�悷�郿 + ��ʂq�f�a * (1 - ������`�悷�郿 )
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�|���S����`��(�ȈՔ�)
	//����: 1.�`(�_�������ʂ�) 2.�}�`�̐� 3.���_�f�[�^�̐擪�A�h���X 4.�傫��

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, testhaikei, sizeof(Vertex2D));

	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//1. LINEAR �� 2.ANISOTROPIC �ٕ���(�d����)
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);




	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
	//D3DPT_POINTLIST : �_
	//D3DPT_LINELIST : ��
	//D3DPT_LINESTRIP : �q�����
	//D3DPT_TRIANGLELIST : ��
	//D3DPT_TRIANGLESTRIP : 


}

void Sprite_Draw(int textureID, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}


	//�f�o�C�X��FVF�ݒ�

	pDevice->SetFVF(FVF_VERTEX2D);


	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;




	Vertex2D testhaikei[] = {
		//���_�f�[�^��p�ӂ���
		//�|���S���͕\��������܂� �E��肵�Ȃ��Əo�Ă��Ȃ� �菇���d�v
		//���オ 0,0


		//                                                                                     (x�̃f�[�^,y�̃f�[�^)(1.0f�͈�̃e�N�X�`����)
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + 0.0f - 0.5f, 1.0f , 1.0f),g_Color,D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dx + dw - 0.5f ,dy + 0.0f - 0.5f, 1.0f , 1.0f), g_Color,D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(dx + 0.0f - 0.5f,dy + dh - 0.5f , 1.0f , 1.0f), g_Color,D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dx + dw - 0.5f ,dy + dh - 0.5f , 1.0f , 1.0f),  g_Color,D3DXVECTOR2(u1, v1)},

		//     WRAP�̏ꍇ    0.5����ɂ��炵�āA�g��������
	};

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//MAGFILTER : �g�債���Ƃ��ǂ̃t�B���^�[���g��
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//MINFILTER : �k�������Ƃ��ǂ̃t�B���^�[���g��
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); //MIPFILTER : 

	//�A���t�@�u�����h�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//�������`��F��������`�悷��q�f�a * ������`�悷�郿 + ��ʂq�f�a * (1 - ������`�悷�郿 )
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�|���S����`��(�ȈՔ�)
	//����: 1.�`(�_�������ʂ�) 2.�}�`�̐� 3.���_�f�[�^�̐擪�A�h���X 4.�傫��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, testhaikei, sizeof(Vertex2D));
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//1. LINEAR �� 2.ANISOTROPIC �ٕ���(�d����)
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);




	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
	//D3DPT_POINTLIST : �_
	//D3DPT_LINELIST : ��
	//D3DPT_LINESTRIP : �q�����
	//D3DPT_TRIANGLELIST : ��
	//D3DPT_TRIANGLESTRIP : 


}


//                                                                                                          cx ��]�g��̒��S���Wx
//                                                                                                          cy ��]�g��̒��S���Wy
void Sprite_Draw(int textureID, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, float cx, float cy , float angle)
{

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}

	//�f�o�C�X��FVF�ݒ�

	pDevice->SetFVF(FVF_VERTEX2D);


	//�f�o�C�X�Ƀe�N�X�`���̐ݒ������
	pDevice->SetTexture(0, Texture_GetTexture(textureID));

	//�e�N�X�`���̃T�C�Y�擾
	int w = Texture_GetTextureWidth(textureID);
	int h = Texture_GetTextureHeight(textureID);

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;




	Vertex2D testhaikei[] = {
		//���_�f�[�^��p�ӂ���
		//�|���S���͕\��������܂� �E��肵�Ȃ��Əo�Ă��Ȃ� �菇���d�v
		//���オ 0,0


		//                                                                                     (x�̃f�[�^,y�̃f�[�^)(1.0f�͈�̃e�N�X�`����)
		{D3DXVECTOR4(0.0f - 0.5f ,  0.0f  - 0.5f, 1.0f , 1.0f),  g_Color,D3DXVECTOR2(u0, v0)},
		{D3DXVECTOR4(dw   -  0.5f,  0.0f  - 0.5f, 1.0f , 1.0f),  g_Color,D3DXVECTOR2(u1, v0)},
		{D3DXVECTOR4(0.0f - 0.5f ,  dh    - 0.5f , 1.0f , 1.0f), g_Color,D3DXVECTOR2(u0, v1)},
		{D3DXVECTOR4(dw   - 0.5f ,  dh    - 0.5f , 1.0f , 1.0f), g_Color,D3DXVECTOR2(u1, v1)},

		//     WRAP�̏ꍇ    0.5����ɂ��炵�āA�g��������
	};


	//���s�ړ��s��
	D3DXMATRIX mtxTranslationC;
	D3DXMatrixTranslation(&mtxTranslationC, -cx, -cy, 0.0f);

	D3DXMATRIX mtxTranslationI;
	D3DXMatrixTranslation(&mtxTranslationI, cx + dx, cy + dy, 0.0f);

	//��]�s����쐬����
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationZ(&mtxRotation, angle);

	//�g��s��
	D3DXMATRIX mtxscale;        //1.0��1�{�̈Ӗ�
	D3DXMatrixScaling(&mtxscale, 1.0, 1.0, 1.0);
	//�s��̍���
	D3DXMATRIX mtxWorld;
	mtxWorld = mtxTranslationC * mtxscale * mtxRotation * mtxTranslationI;


	//���W�ϊ�
	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&testhaikei[i].Position, &testhaikei[i].Position, &mtxWorld);
	}





	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);//MAGFILTER : �g�債���Ƃ��ǂ̃t�B���^�[���g��
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);//MINFILTER : �k�������Ƃ��ǂ̃t�B���^�[���g��
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); //MIPFILTER : 

	//�A���t�@�u�����h�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//�������`��F��������`�悷��q�f�a * ������`�悷�郿 + ��ʂq�f�a * (1 - ������`�悷�郿 )
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�|���S����`��(�ȈՔ�)
	//����: 1.�`(�_�������ʂ�) 2.�}�`�̐� 3.���_�f�[�^�̐擪�A�h���X 4.�傫��

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, testhaikei, sizeof(Vertex2D));

	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//1. LINEAR �� 2.ANISOTROPIC �ٕ���(�d����)
	//pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);



	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));
	//D3DPT_POINTLIST : �_
	//D3DPT_LINELIST : ��
	//D3DPT_LINESTRIP : �q�����
	//D3DPT_TRIANGLELIST : ��
	//D3DPT_TRIANGLESTRIP : 











}


void Sprite_SetColor(D3DCOLOR color)
{
	g_Color = color;
}

void Sprite_Final()
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

}