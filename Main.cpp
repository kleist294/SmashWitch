

#define _CRT_SECURE_NO_WARNINGS
/*================================================================

	 Windowsの表示(main.cpp)



-----------------------------------------------------------------


================================================================= */

//ライブラリーファイルを入れる
/*#pragma comment(lib , "d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib , "d3dx9d.lib")
#else
#pragma comment( lib , "d3dx9.lib")
#endif
*/

#include <windows.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "Config.h"
#include "Mydirect3d.h"
#include "Game.h"
#include "Title.h"
#include "Sousa.h"
#include "Result.h"
#include "Fade.h"
#include "SystemTimer.h"
#include "DebugFont.h"
#include "DebugPrimitive.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "Keyboard.h"
#include "Keylogger.h"
#include "Sound.h"
#include "Scene.h"
#include "Fade.h"
#include "Mouse.h"

//定数定義
#define CLASS_NAME      "GameWindow"                        //ウィンドウクラス名(あなたのオリジナルウィンドウパーツ)
#define WINDOWS_CAPTION "Smash Witch"                //


//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//ゲームの初期化
//戻り値：初期化失敗したときにFalse
//プロトタイプ宣言はstaticいらない
static bool Init(HWND hWnd);

//ゲームの更新
static void Update();

//ゲームの描画
static void Draw();

//ゲームの終了処理
static void UnInit();

/*---------------------------------------------------------------------
　　グローバル変数宣言
-----------------------------------------------------------------------*/
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0;
static double g_ReserveTime = 0.0;

static int Menu = 0;

/*---------------------------------------------------------------------
　　構造体変数宣言
-----------------------------------------------------------------------*/

//頂点構造体宣言





//FVF : フレキシブルバーテクスフォーマット(flexible vertex format)
//座標変換済み頂点 RHW = 1



//メイン
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);






	//ウィンドウclassの構造体(一旦登録して、呼び出す)
	WNDCLASS wc = {};                                         //初期化が必要 ( = {})中身を全部０にする WNSCLASSEXもあります
	//ZeroMemory()もたまに使ってます
	wc.lpfnWndProc = WndProc;                                 //ウィンドウプロシジャーの指定(ポインター)
	wc.lpszClassName = CLASS_NAME;                            //クラスネーム(名前は自由で   20行目の情報)
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);                 //マウスカーソルを指定(デフォルト化、指定しないとカーソルは変わらない) 
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);        //ウィンドウのクライアント領域の背景色を設定( + 1 は仕様です)

	//class登録
	RegisterClass(&wc);//RegisterClassExもあります


	//XORによるビットを下げる時の注意事項
	//左辺値の下げたいビットがに立っていことが条件
	DWORD style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX); //double word型
	//都合のいいウィンドウサイズの算出
	RECT WindowRect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&WindowRect, style, FALSE);
	int WindowWidth = WindowRect.right - WindowRect.left;
	int WindowHeight = WindowRect.bottom - WindowRect.top;

	//表示するウィンドウの場所を算出する
	//デスクトップ（クライアント領域）の取得

	//APIを利用したデスクトップの幅高さを取得

	//デスクトップの幅高さ
	//RECT desktop_rect;
	//GetWindowRect(GetDesktopWindow(), &desktop_rect);
	//デスクトップの幅高さを算出
	//int desktopwidth = desktop_rect.right - desktop_rect.left;
	//int desktopheight = desktop_rect.bottom - desktop_rect.top;

	//デバイスからモニターの解像度を取得する
	//プライマリーモニターの画面解像度を取得
	int DesktopWidth = GetSystemMetrics(SM_CXSCREEN);
	int DesktopHeight = GetSystemMetrics(SM_CYSCREEN);


	int WindowX = max((DesktopWidth - WindowWidth) / 2, 0);
	int WindowY = max((DesktopHeight - WindowHeight) / 2, 0);


	//ウィンドウの生成
	HWND hWnd = CreateWindow(          //CreateWindowExもあります　＂戻り値はＨＷＮＤです　超重要！！！！！！！！！！＂
	// HWNDはウィンドウハンドル　(HWND 変数の形)　　ウィンドウハンドルというのはウィンドウのＩＤみたいなもの

		CLASS_NAME,            //ウィンドウクラス
		WINDOWS_CAPTION,       //ウィンドウのテキスト（一番上の名前みたいのもの）
		style,   //ウィンドウのスタイル(ビットフラッグ)
		//XORで


		//サイズと位置
		WindowX,    //左上画面から左上ウィンドウのｘ座標　CW_USEDDEFAULTはOSにおまかせの意味
		WindowY,    //左上画面から左上ウィンドウのｙ座標　ｘ座標と同時に設定しないといけない
		WindowWidth,    //ウィンドウのｘ座標（黒い画面だけではない　枠線も含まれた幅）
		WindowHeight,    //ウィンドウのｙ座標（黒い画面だけではない　枠線も含まれた高さ）


		NULL,             //親ウィンドウのハンドル
		NULL,             //メニューのハンドル（ゲームでは処理堕ちになるため、あえて付けない）
		hInstance,        //インスタンスハンドル
		NULL,             //追加のアプリケーションデータ、謎です
		);


	if (hWnd == NULL)
	{
		//ウィンドウが何らかの理由で生成失敗です
		return 0;
	}


	//指定のウィンドウハンドルのウィンドウを指定の方式で表示する
	ShowWindow(hWnd, nCmdShow);
	if (!Init(hWnd))
	{
		//メッセージボックス
		MessageBox(NULL, "予想外のエラーが発生しました", "エラー", MB_OK | MB_ICONHAND);
		return 0;
	}
	//ウィンドウメッセージの取得　（メッセージループ）
	MSG msg = {}; //msg.message == WM_NULL
	while (WM_QUIT != msg.message)
	{
		//このループがないと、一瞬で消えます
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))  //GetMessageはscanfみたい　メッセージを待つ状態 (ゲームループにしたいなら、動かないと固まってします)
		//PeekMessage: メッセージがある場合はメッセージ処理は優先
		{
			TranslateMessage(&msg);        ////そのメッセージを翻訳する
			DispatchMessage(&msg);         //そのメッセージを処理する    (37行目のWndProcが呼ばれる 変数名"WndProc"は自由、たいていWndProc)
		}                                  //ループする
		else
		{
			//ここがゲーム処理
			/*
			double time = SystemTimer_GetTime();
			if((time - g_ReserveTime) < 1.0f/60.f)
			{
			Sleep(0);
			continue;
			}
			g_ReserveTime = time;
			*/






			Update();

			Draw();

			//シーンの切り替え処理
			Scene_ExecuteChange();

		}



	}

	//ゲームの終了処理
	UnInit();
	return (int)msg.wParam;

}


//ウィンドウプロシジャー（コールバック関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

		

			case WM_ACTIVATEAPP:
				Keyboard_ProcessMessage(uMsg, wParam, lParam);
			case WM_INPUT:
			case WM_MOUSEMOVE:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_MOUSEWHEEL:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
			case WM_MOUSEHOVER:
				Mouse_ProcessMessage(uMsg, wParam, lParam);
				
				break;
			case WM_KEYDOWN:
				if (wParam == VK_ESCAPE) //escキー
				{
					SendMessage(hWnd, WM_CLOSE, 0, 0);
				}
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP:
				Keyboard_ProcessMessage(uMsg, wParam, lParam);
				break;


		break;

	case WM_CLOSE:   //×ボタン　
		if (MessageBox(hWnd, "本当終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) //誤作動防止のため、確認を入れます
		{
			DestroyWindow(hWnd); //指定のウィンドウにWM_DESTROYメッセージを送る
		}
		return 0; //DefWindowProcを処理せず、終了することによってなにもなかったことにする
	case WM_DESTROY:
		PostQuitMessage(0); //WM_QUITメッセージ送信
		return 0;
	};

	//通常メッセージ処理はこの関数に任せる (終了処理はかならず作らなきゃいけない)
	return DefWindowProc(hWnd, uMsg, wParam, lParam);



}

bool Init(HWND hWnd)
{
	Mouse_Initialize(hWnd);
	Keyboard_Initialize();
	KeyLogger_Init();
	
	//サウンドの初期化
	InitSound(hWnd);
	

	if (!MyDirect3D_Init(hWnd))
	{
		MessageBox(NULL, "Initial読み込みませんでした", "エラー", MB_OK | MB_ICONHAND);
		return false;
	}
	TextureInit();

	//デバッグ図形描画モジュールの初期化
	DeBugPrimitive_Init();


	
	
	
	DebugFont_Init();
	Fade_Init();
	Scene_Init();
	

	
	
	

	SystemTimer_Initialize();
	g_ReserveTime = g_BaseTime = SystemTimer_GetTime();
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;

	Sprite_Init();
	
	

	

	return true;//初期化成功
}

void Update()
{



	
	KeyLogger_Update();
	
	Scene_Update();
	Fade_Update();
	

	

	double time = SystemTimer_GetTime();
	if (time - g_BaseTime > 1.0)
	{
		g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
		g_BaseTime = time;
		g_BaseFrame = g_FrameCount;
	}


	g_FrameCount++;
}

void Draw()
{
	LPDIRECT3DDEVICE9 pDevice =  MyDirect3D_GetDevice();

	if (!pDevice)
	{
		return;
	}
	//画面クリア                                                       色バッファー                 深度バッファー(1.0fは一番奥)
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(102, 102, 204, 255), 1.0f, 0);


	//描画バッチ命令の開始   BeginとEndはセットで使う 
	pDevice->BeginScene();


	//デバッグ図形描画命令の受付開始
	DeBugPrimitive_BatchBegin();


	Scene_Draw();

	Fade_Draw();

	
	//FPS 表示
	char buf[64];
	

//	sprintf(buf,"FPS = %.2f", g_FPS);
//
//	//この行を実行したらバグ
//	DebugFontDraw(0 , 0, buf);

	//デバッグ図形描画命令の実行
	DeBugPrimitive_BatchRun();

	//描画バッチ命令の終了
	pDevice->EndScene();

	//バックバッファをフリップ（タイミングはD3DPRESENT_PARAMETERSの設定による）
	//Presentは1フレームに一回
	pDevice->Present(NULL, NULL, NULL, NULL);
	
}

void UnInit()
{
	Game_Final();
	Scene_Final();
	Sprite_Final();
	DebugFont_Final();
	TextureFinal();
	MyDirect3D_Final();
	KeyLogger_Final();
	DeBugPrimitive_Final();
	UninitSound();
	Mouse_Finalize();
}