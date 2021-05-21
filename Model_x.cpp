
/*============================================================

　　　　　　　　　Xモデル

============================================================*/

#include "Model_x.h"
#include "Mydirect3d.h"
#include "Light.h"
#include "TextureManager.h"

//構造体宣言
struct XModel
{
	LPD3DXMESH pMesh;//メッシュ
	//LPD3DXBUFFER pAdjacency; //隣接情報バッファー
	DWORD materialCount; //マテリアル数
	//マテリアル情報
	D3DMATERIAL9 *pMaterials;
	//テクスチャId
	int *pTextureIds;
};



//定数宣言
#define MODEL_X_MAX (64)


//グローバル
static XModel g_XModels[MODEL_X_MAX] = {};


/*============================================================　　　　　　　　　
		 モデルの初期化
============================================================*/
void Model_X_Init() 
{
	Model_x_ReleaseAll();

}

/*============================================================　　　　　　　　　
		 モデルのリリース
============================================================*/
void Model_X_Final() 
{
	Model_x_ReleaseAll();

}

/*============================================================　　　　　　　　　
　　　　　　モデルをロードする
============================================================*/
int Model_X_Load(const char *pFileName)
{
	int id = INVALID_MODEL_X_ID;
	//g_XModelsから未使用領域を検索
	for (int i = 0; i < MODEL_X_MAX; i++) {
		if (g_XModels[i].pMesh == NULL) {
			id = i;
			break;
		}
	}

	//idは取得できたか？
	if (id == INVALID_MODEL_X_ID) {
		return INVALID_MODEL_X_ID;//未使用領域がなかった
	}

	//モデルデータの読み込み
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	LPD3DXBUFFER pAdjacency; // 隣接情報バッファ(一時使用)
	LPD3DXMESH pTempMesh;    //モデルメッシュ(一時使用)
	LPD3DXBUFFER pMaterial;//マテリアルバッファ(一時使用)
	DWORD materialCount;     //マテリアル数(一時使用)

	hr = D3DXLoadMeshFromX(
		pFileName,         //ファイル名
		D3DXMESH_SYSTEMMEM,//オプション()
		pDevice,           //Direct3Dデバイス
		&pAdjacency,       //隣接情報
		&pMaterial,              //マテリアル情報取得
		NULL,              //エフェクト(シェーダー) (取得)
		&materialCount,    //マテリアル数(取得)
		&pTempMesh         //メッシュ(取得)
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Xファイルの読み込みに失敗しました", "エラー", MB_OK);
		return INVALID_MODEL_X_ID;
	}

	g_XModels[id].materialCount = materialCount;

	D3DXMATERIAL *pD3DXMaterial = (D3DXMATERIAL*)pMaterial->GetBufferPointer();
	
	g_XModels[id].pMaterials = new D3DMATERIAL9[materialCount];
	g_XModels[id].pTextureIds = new int[materialCount];

	for (int i = 0; i < materialCount; i++)
	{
		//マテリアル値のコピー
		g_XModels[id].pMaterials[i] = pD3DXMaterial[i].MatD3D;
		//要素を選んでコピーすることをオススメ
		//g_XModels[id].pMaterials[i].Diffuse = pD3DXMaterial[i].MatD3D.Emissive;
		//g_XModels[id].pMaterials[i].Diffuse = pD3DXMaterial[i].MatD3D.Emissive;
		//g_XModels[id].pMaterials[i].Ambient = pD3DXMaterial[i].MatD3D.Diffuse;
		//g_XModels[id].pMaterials[i].Emissive = pD3DXMaterial[i].MatD3D.Ambient;
		//g_XModels[id].pMaterials[i].Power = pD3DXMaterial[i].MatD3D.Power;
		//g_XModels[id].pMaterials[i].Specular = pD3DXMaterial[i].MatD3D.Specular;
		//テクスチャファイル名の取得
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


	

	//メッシュの最適化をする
	pTempMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdjacency->GetBufferPointer(),NULL,NULL,NULL);

	//高速で面倒を見てくれる頂点バッファを取り扱うメッシュとしてクローンを作成する
	pTempMesh->CloneMeshFVF(
		D3DXMESH_MANAGED,
		pTempMesh->GetFVF(),
		pDevice,&g_XModels[id].pMesh);
	//用済みバッファを削除
	pMaterial->Release();
	pAdjacency->Release();
	pTempMesh->Release();

	return id;
}

/*============================================================　　　　　　　　　
　　　　　　モデルをリリースする
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

/*============================================================　　　　　　　　　
　　　　　　モデルを全部リリースする
============================================================*/
void Model_x_ReleaseAll() 
{
	for (int i = 0; i < MODEL_X_MAX; i++){
			Model_x_Release(&i, 1);
	}

}

/*============================================================　　　　　　　　　
　　　　　　モデルの描画
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

		

		pDevice->SetMaterial(&g_XModels[ID].pMaterials[i]);//マテリアルを設定

		pDevice->SetTexture(0, Texture_GetTexture(g_XModels[ID].pTextureIds[i]));

		g_XModels[ID].pMesh->DrawSubset(i);//FVFの設定・頂点バッファとインデックスの設定
	}
}


LPD3DXMESH* Model_X_GetMesh(int index)
{
	return &g_XModels[index].pMesh;
}