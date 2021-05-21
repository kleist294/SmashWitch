

#define _CRT_SECURE_NO_WARNINGS
/*================================================================

	 Windows�̕\��(main.cpp)



-----------------------------------------------------------------


================================================================= */

//���C�u�����[�t�@�C��������
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

//�萔��`
#define CLASS_NAME      "GameWindow"                        //�E�B���h�E�N���X��(���Ȃ��̃I���W�i���E�B���h�E�p�[�c)
#define WINDOWS_CAPTION "Smash Witch"                //


//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//�Q�[���̏�����
//�߂�l�F���������s�����Ƃ���False
//�v���g�^�C�v�錾��static����Ȃ�
static bool Init(HWND hWnd);

//�Q�[���̍X�V
static void Update();

//�Q�[���̕`��
static void Draw();

//�Q�[���̏I������
static void UnInit();

/*---------------------------------------------------------------------
�@�@�O���[�o���ϐ��錾
-----------------------------------------------------------------------*/
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0;
static double g_ReserveTime = 0.0;

static int Menu = 0;

/*---------------------------------------------------------------------
�@�@�\���̕ϐ��錾
-----------------------------------------------------------------------*/

//���_�\���̐錾





//FVF : �t���L�V�u���o�[�e�N�X�t�H�[�}�b�g(flexible vertex format)
//���W�ϊ��ςݒ��_ RHW = 1



//���C��
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);






	//�E�B���h�Eclass�̍\����(��U�o�^���āA�Ăяo��)
	WNDCLASS wc = {};                                         //���������K�v ( = {})���g��S���O�ɂ��� WNSCLASSEX������܂�
	//ZeroMemory()�����܂Ɏg���Ă܂�
	wc.lpfnWndProc = WndProc;                                 //�E�B���h�E�v���V�W���[�̎w��(�|�C���^�[)
	wc.lpszClassName = CLASS_NAME;                            //�N���X�l�[��(���O�͎��R��   20�s�ڂ̏��)
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);                 //�}�E�X�J�[�\�����w��(�f�t�H���g���A�w�肵�Ȃ��ƃJ�[�\���͕ς��Ȃ�) 
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);        //�E�B���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�( + 1 �͎d�l�ł�)

	//class�o�^
	RegisterClass(&wc);//RegisterClassEx������܂�


	//XOR�ɂ��r�b�g�������鎞�̒��ӎ���
	//���Ӓl�̉��������r�b�g���ɗ����Ă����Ƃ�����
	DWORD style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX); //double word�^
	//�s���̂����E�B���h�E�T�C�Y�̎Z�o
	RECT WindowRect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&WindowRect, style, FALSE);
	int WindowWidth = WindowRect.right - WindowRect.left;
	int WindowHeight = WindowRect.bottom - WindowRect.top;

	//�\������E�B���h�E�̏ꏊ���Z�o����
	//�f�X�N�g�b�v�i�N���C�A���g�̈�j�̎擾

	//API�𗘗p�����f�X�N�g�b�v�̕��������擾

	//�f�X�N�g�b�v�̕�����
	//RECT desktop_rect;
	//GetWindowRect(GetDesktopWindow(), &desktop_rect);
	//�f�X�N�g�b�v�̕��������Z�o
	//int desktopwidth = desktop_rect.right - desktop_rect.left;
	//int desktopheight = desktop_rect.bottom - desktop_rect.top;

	//�f�o�C�X���烂�j�^�[�̉𑜓x���擾����
	//�v���C�}���[���j�^�[�̉�ʉ𑜓x���擾
	int DesktopWidth = GetSystemMetrics(SM_CXSCREEN);
	int DesktopHeight = GetSystemMetrics(SM_CYSCREEN);


	int WindowX = max((DesktopWidth - WindowWidth) / 2, 0);
	int WindowY = max((DesktopHeight - WindowHeight) / 2, 0);


	//�E�B���h�E�̐���
	HWND hWnd = CreateWindow(          //CreateWindowEx������܂��@�W�߂�l�͂g�v�m�c�ł��@���d�v�I�I�I�I�I�I�I�I�I�I�W
	// HWND�̓E�B���h�E�n���h���@(HWND �ϐ��̌`)�@�@�E�B���h�E�n���h���Ƃ����̂̓E�B���h�E�̂h�c�݂����Ȃ���

		CLASS_NAME,            //�E�B���h�E�N���X
		WINDOWS_CAPTION,       //�E�B���h�E�̃e�L�X�g�i��ԏ�̖��O�݂����̂��́j
		style,   //�E�B���h�E�̃X�^�C��(�r�b�g�t���b�O)
		//XOR��


		//�T�C�Y�ƈʒu
		WindowX,    //�����ʂ��獶��E�B���h�E�̂����W�@CW_USEDDEFAULT��OS�ɂ��܂����̈Ӗ�
		WindowY,    //�����ʂ��獶��E�B���h�E�̂����W�@�����W�Ɠ����ɐݒ肵�Ȃ��Ƃ����Ȃ�
		WindowWidth,    //�E�B���h�E�̂����W�i������ʂ����ł͂Ȃ��@�g�����܂܂ꂽ���j
		WindowHeight,    //�E�B���h�E�̂����W�i������ʂ����ł͂Ȃ��@�g�����܂܂ꂽ�����j


		NULL,             //�e�E�B���h�E�̃n���h��
		NULL,             //���j���[�̃n���h���i�Q�[���ł͏������ɂȂ邽�߁A�����ĕt���Ȃ��j
		hInstance,        //�C���X�^���X�n���h��
		NULL,             //�ǉ��̃A�v���P�[�V�����f�[�^�A��ł�
		);


	if (hWnd == NULL)
	{
		//�E�B���h�E�����炩�̗��R�Ő������s�ł�
		return 0;
	}


	//�w��̃E�B���h�E�n���h���̃E�B���h�E���w��̕����ŕ\������
	ShowWindow(hWnd, nCmdShow);
	if (!Init(hWnd))
	{
		//���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�\�z�O�̃G���[���������܂���", "�G���[", MB_OK | MB_ICONHAND);
		return 0;
	}
	//�E�B���h�E���b�Z�[�W�̎擾�@�i���b�Z�[�W���[�v�j
	MSG msg = {}; //msg.message == WM_NULL
	while (WM_QUIT != msg.message)
	{
		//���̃��[�v���Ȃ��ƁA��u�ŏ����܂�
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))  //GetMessage��scanf�݂����@���b�Z�[�W��҂�� (�Q�[�����[�v�ɂ������Ȃ�A�����Ȃ��ƌł܂��Ă��܂�)
		//PeekMessage: ���b�Z�[�W������ꍇ�̓��b�Z�[�W�����͗D��
		{
			TranslateMessage(&msg);        ////���̃��b�Z�[�W��|�󂷂�
			DispatchMessage(&msg);         //���̃��b�Z�[�W����������    (37�s�ڂ�WndProc���Ă΂�� �ϐ���"WndProc"�͎��R�A�����Ă�WndProc)
		}                                  //���[�v����
		else
		{
			//�������Q�[������
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

			//�V�[���̐؂�ւ�����
			Scene_ExecuteChange();

		}



	}

	//�Q�[���̏I������
	UnInit();
	return (int)msg.wParam;

}


//�E�B���h�E�v���V�W���[�i�R�[���o�b�N�֐��j
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
				if (wParam == VK_ESCAPE) //esc�L�[
				{
					SendMessage(hWnd, WM_CLOSE, 0, 0);
				}
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP:
				Keyboard_ProcessMessage(uMsg, wParam, lParam);
				break;


		break;

	case WM_CLOSE:   //�~�{�^���@
		if (MessageBox(hWnd, "�{���I�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) //��쓮�h�~�̂��߁A�m�F�����܂�
		{
			DestroyWindow(hWnd); //�w��̃E�B���h�E��WM_DESTROY���b�Z�[�W�𑗂�
		}
		return 0; //DefWindowProc�����������A�I�����邱�Ƃɂ���ĂȂɂ��Ȃ��������Ƃɂ���
	case WM_DESTROY:
		PostQuitMessage(0); //WM_QUIT���b�Z�[�W���M
		return 0;
	};

	//�ʏ탁�b�Z�[�W�����͂��̊֐��ɔC���� (�I�������͂��Ȃ炸���Ȃ��Ⴂ���Ȃ�)
	return DefWindowProc(hWnd, uMsg, wParam, lParam);



}

bool Init(HWND hWnd)
{
	Mouse_Initialize(hWnd);
	Keyboard_Initialize();
	KeyLogger_Init();
	
	//�T�E���h�̏�����
	InitSound(hWnd);
	

	if (!MyDirect3D_Init(hWnd))
	{
		MessageBox(NULL, "Initial�ǂݍ��݂܂���ł���", "�G���[", MB_OK | MB_ICONHAND);
		return false;
	}
	TextureInit();

	//�f�o�b�O�}�`�`�惂�W���[���̏�����
	DeBugPrimitive_Init();


	
	
	
	DebugFont_Init();
	Fade_Init();
	Scene_Init();
	

	
	
	

	SystemTimer_Initialize();
	g_ReserveTime = g_BaseTime = SystemTimer_GetTime();
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;

	Sprite_Init();
	
	

	

	return true;//����������
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
	//��ʃN���A                                                       �F�o�b�t�@�[                 �[�x�o�b�t�@�[(1.0f�͈�ԉ�)
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(102, 102, 204, 255), 1.0f, 0);


	//�`��o�b�`���߂̊J�n   Begin��End�̓Z�b�g�Ŏg�� 
	pDevice->BeginScene();


	//�f�o�b�O�}�`�`�施�߂̎�t�J�n
	DeBugPrimitive_BatchBegin();


	Scene_Draw();

	Fade_Draw();

	
	//FPS �\��
	char buf[64];
	

//	sprintf(buf,"FPS = %.2f", g_FPS);
//
//	//���̍s�����s������o�O
//	DebugFontDraw(0 , 0, buf);

	//�f�o�b�O�}�`�`�施�߂̎��s
	DeBugPrimitive_BatchRun();

	//�`��o�b�`���߂̏I��
	pDevice->EndScene();

	//�o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ��j
	//Present��1�t���[���Ɉ��
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