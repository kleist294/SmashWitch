

/*============================================================

　　　　　　　　　ライトの制御

============================================================*/


#include <d3dx9.h>
#include "mydirect3d.h"
#include "Camera.h"

static D3DCOLOR g_Color = { D3DCOLOR_RGBA(60,60,60, 255) };


/*============================================================
　　　　　
	 　　　　ライトの設置

============================================================*/
void Light_Set()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();


	//ライトを設定する
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	//ライト（平行光源）の設定を作成
	D3DLIGHT9 Light = {};
	//他の初期化のやり方
	//memset(&Light,0,sizeof(Light));
	//ZeroMemory(&Light,sizeof(Light));

	Light.Type = D3DLIGHT_DIRECTIONAL;

	D3DXVECTOR3 vecDirLight = *Camera_GetFrontVector();
	vecDirLight.y = -1.0f;
	//D3DXVec3Normalize(&vecDirLight, &vecDirLight);
	//Light.Direction = vecDirLight;
	D3DXVec3Normalize((D3DXVECTOR3*)&Light.Direction, &vecDirLight);

	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;
	Light.Diffuse.a = 1.0f;

	Light.Ambient.r = 0.1f;
	Light.Ambient.g = 0.1f;
	Light.Ambient.b = 0.1f;
	Light.Ambient.a = 1.0f;


	//マテリアルを設定（今回は頂点カラーがマテリアル）
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);



	//デバイスにライトを設定する
	pDevice->SetLight(0, &Light);
	pDevice->LightEnable(0, TRUE);

	// アンビエントライトの設定
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(60,60,60, 255));

}
