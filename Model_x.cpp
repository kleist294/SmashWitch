
/*============================================================

�@�@�@�@�@�@�@�@�@X���f��

============================================================*/

#include "Model_x.h"
#include "Mydirect3d.h"
#include "Light.h"
#include "TextureManager.h"

//�\���̐錾
struct XModel
{
	LPD3DXMESH pMesh;//���b�V��
	//LPD3DXBUFFER pAdjacency; //�אڏ��o�b�t�@�[
	DWORD materialCount; //�}�e���A����
	//�}�e���A�����
	D3DMATERIAL9 *pMaterials;
	//�e�N�X�`��Id
	int *pTextureIds;
};



//�萔�錾
#define MODEL_X_MAX (64)


//�O���[�o��
static XModel g_XModels[MODEL_X_MAX] = {};


/*============================================================�@�@�@�@�@�@�@�@�@
		 ���f���̏�����
============================================================*/
void Model_X_Init() 
{
	Model_x_ReleaseAll();

}

/*============================================================�@�@�@�@�@�@�@�@�@
		 ���f���̃����[�X
============================================================*/
void Model_X_Final() 
{
	Model_x_ReleaseAll();

}

/*============================================================�@�@�@�@�@�@�@�@�@
�@�@�@�@�@�@���f�������[�h����
============================================================*/
int Model_X_Load(const char *pFileName)
{
	int id = INVALID_MODEL_X_ID;
	//g_XModels���疢�g�p�̈������
	for (int i = 0; i < MODEL_X_MAX; i++) {
		if (g_XModels[i].pMesh == NULL) {
			id = i;
			break;
		}
	}

	//id�͎擾�ł������H
	if (id == INVALID_MODEL_X_ID) {
		return INVALID_MODEL_X_ID;//���g�p�̈悪�Ȃ�����
	}

	//���f���f�[�^�̓ǂݍ���
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	LPD3DXBUFFER pAdjacency; // �אڏ��o�b�t�@(�ꎞ�g�p)
	LPD3DXMESH pTempMesh;    //���f�����b�V��(�ꎞ�g�p)
	LPD3DXBUFFER pMaterial;//�}�e���A���o�b�t�@(�ꎞ�g�p)
	DWORD materialCount;     //�}�e���A����(�ꎞ�g�p)

	hr = D3DXLoadMeshFromX(
		pFileName,         //�t�@�C����
		D3DXMESH_SYSTEMMEM,//�I�v�V����()
		pDevice,           //Direct3D�f�o�C�X
		&pAdjacency,       //�אڏ��
		&pMaterial,              //�}�e���A�����擾
		NULL,              //�G�t�F�N�g(�V�F�[�_�[) (�擾)
		&materialCount,    //�}�e���A����(�擾)
		&pTempMesh         //���b�V��(�擾)
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
		return INVALID_MODEL_X_ID;
	}

	g_XModels[id].materialCount = materialCount;

	D3DXMATERIAL *pD3DXMaterial = (D3DXMATERIAL*)pMaterial->GetBufferPointer();
	
	g_XModels[id].pMaterials = new D3DMATERIAL9[materialCount];
	g_XModels[id].pTextureIds = new int[materialCount];

	for (int i = 0; i < materialCount; i++)
	{
		//�}�e���A���l�̃R�s�[
		g_XModels[id].pMaterials[i] = pD3DXMaterial[i].MatD3D;
		//�v�f��I��ŃR�s�[���邱�Ƃ��I�X�X��
		//g_XModels[id].pMaterials[i].Diffuse = pD3DXMaterial[i].MatD3D.Emissive;
		//g_XModels[id].pMaterials[i].Diffuse = pD3DXMaterial[i].MatD3D.Emissive;
		//g_XModels[id].pMaterials[i].Ambient = pD3DXMaterial[i].MatD3D.Diffuse;
		//g_XModels[id].pMaterials[i].Emissive = pD3DXMaterial[i].MatD3D.Ambient;
		//g_XModels[id].pMaterials[i].Power = pD3DXMaterial[i].MatD3D.Power;
		//g_XModels[id].pMaterials[i].Specular = pD3DXMaterial[i].MatD3D.Specular;
		//�e�N�X�`���t�@�C�����̎擾
		pD3DXMaterial[i].pTextureFilename;

		if (pD3DXMaterial[i].pTextureFilename) {

			char buf[256];

			strcpy(buf, pFileName);
			char* pSplit = strrchr(buf, '\\');
			*(pSplit + 1) = '\0';

			strcat(buf, pD3DXMaterial[i].pTextureFilename);

			g_XModels[id].pTextureIds[i] = Texture_SetTextureLoadFile(buf);
		}
		else {
			g_XModels[id].pTextureIds[i] = INVALID_TEXTURE_ID;
		}
	}


	

	//���b�V���̍œK��������
	pTempMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacency->GetBufferPointer(),NULL,NULL,NULL);

	//�����Ŗʓ|�����Ă���钸�_�o�b�t�@����舵�����b�V���Ƃ��ăN���[�����쐬����
	pTempMesh->CloneMeshFVF(
		D3DXMESH_MANAGED,
		pTempMesh->GetFVF(),
		pDevice,&g_XModels[id].pMesh);
	//�p�ς݃o�b�t�@���폜
	pMaterial->Release();
	pAdjacency->Release();
	pTempMesh->Release();

	return id;
}

/*============================================================�@�@�@�@�@�@�@�@�@
�@�@�@�@�@�@���f���������[�X����
============================================================*/
void Model_x_Release(const int *pIDs, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!g_XModels[pIDs[i]].pMesh)
			continue;

			g_XModels[pIDs[i]].pMesh->Release();
			g_XModels[pIDs[i]].pMesh = NULL;
		
			delete[] g_XModels[pIDs[i]].pMaterials;
			delete[] g_XModels[pIDs[i]].pTextureIds;
	}
}

/*============================================================�@�@�@�@�@�@�@�@�@
�@�@�@�@�@�@���f����S�������[�X����
============================================================*/
void Model_x_ReleaseAll() 
{
	for (int i = 0; i < MODEL_X_MAX; i++){
			Model_x_Release(&i, 1);
	}

}

/*============================================================�@�@�@�@�@�@�@�@�@
�@�@�@�@�@�@���f���̕`��
============================================================*/
void Model_X_Draw(int ID, D3DXMATRIX *mtxmodel) 
{
	if (!g_XModels[ID].pMesh)return;

	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
    
	
	pDevice->SetTransform(D3DTS_WORLD, mtxmodel);
	
	Light_Set();

	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		
	for (DWORD i = 0; i < g_XModels[ID].materialCount; i++) {

		

		pDevice->SetMaterial(&g_XModels[ID].pMaterials[i]);//�}�e���A����ݒ�

		pDevice->SetTexture(0, Texture_GetTexture(g_XModels[ID].pTextureIds[i]));

		g_XModels[ID].pMesh->DrawSubset(i);//FVF�̐ݒ�E���_�o�b�t�@�ƃC���f�b�N�X�̐ݒ�
	}
}


LPD3DXMESH* Model_X_GetMesh(int index)
{
	return &g_XModels[index].pMesh;
}