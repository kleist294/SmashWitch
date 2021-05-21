
/*============================================================　　　　　　　　　
　　　
   　　　directXの実装

============================================================*/


#include <windows.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include "config.h"


/*---------------------------------------------------------------------
　　グローバル変数宣言
-----------------------------------------------------------------------*/

static LPDIRECT3D9 g_pD3D = NULL; //Direct3Dインターフェース
static LPDIRECT3DDEVICE9 g_pDevice = NULL; //Direct3Dデバイスインターフェース



/*---------------------------------------------------------------------
　　関数定義
-----------------------------------------------------------------------*/



bool MyDirect3D_Init(HWND hWnd)
{
	//Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		//Direct3Dインターフェースのに失敗
		MessageBox(NULL, "Direct3Dインターフェースの作成に失敗しました", "エラー", MB_OK | MB_ICONHAND);
		return false;
	}


	/*Direct3Dデバイスの取得*/

	//デバイスの取得に必要の情報構造体の作成
	D3DPRESENT_PARAMETERS d3dpp = {};                            //0初期化する
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                        //バックバファーの横幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                      //バックバファーの縦幅
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                     //バックバファーのフォーマット
	d3dpp.BackBufferCount = 1;                                   //バックバファーの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                    //スワップ方法の設定
	d3dpp.Windowed = TRUE;                                       //ウィンドウ or フルスクリーン
	d3dpp.EnableAutoDepthStencil = TRUE;                         //深度バファー・ステンシルバファーの使用 (奥行き)
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                   //深度バファー・ステンシルバファーのフォーマット（16は奥行きが16bitの意味）
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	 //フルスクリーンのリフレッシュレートの設定
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;    //リフレッスュレートとPresent処理の関係
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//Direct3Dデバイスの取得
	HRESULT hr;

	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);

	// HRESULT型変数は成功や失敗が値として入っているので
	//失敗や成功だけ判定する場合はマクロを利用する FAILED(hr) SUCCEEDED(hr)
	if (FAILED(hr))
	{
		//デバイスの取得に失敗
		MessageBox(NULL, "Direct3Dインターフェースの取得に失敗しました", "エラー", MB_OK | MB_ICONHAND);
		return false;
	}


	// テクスチャの読み込み

	//g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_CURRENT);
	//g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	//g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_CURRENT);
	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//UV
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 255, 0, 255));
	
	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	//WRAP : タイルみたい複数出る
	//CLAMP: 最後のpixelの色が伸びってる
	//MIRROR : 反転
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); 
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//法線ベクトルは必ず正規化して使用する設定をする
	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	return true;

}



void MyDirect3D_Final(void)
{
	if (g_pDevice) {
		g_pDevice->Release();
		g_pDevice = NULL;

	}
	if (g_pD3D) {
		g_pD3D->Release();
		g_pD3D = NULL;

	}

}

LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void)
{

	return g_pDevice;

}