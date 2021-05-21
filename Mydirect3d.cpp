
/*============================================================�@�@�@�@�@�@�@�@�@
�@�@�@
   �@�@�@directX�̎���

============================================================*/


#include <windows.h> 
#include <d3d9.h>
#include <d3dx9.h>
#include "config.h"


/*---------------------------------------------------------------------
�@�@�O���[�o���ϐ��錾
-----------------------------------------------------------------------*/

static LPDIRECT3D9 g_pD3D = NULL; //Direct3D�C���^�[�t�F�[�X
static LPDIRECT3DDEVICE9 g_pDevice = NULL; //Direct3D�f�o�C�X�C���^�[�t�F�[�X



/*---------------------------------------------------------------------
�@�@�֐���`
-----------------------------------------------------------------------*/



bool MyDirect3D_Init(HWND hWnd)
{
	//Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		//Direct3D�C���^�[�t�F�[�X�̂Ɏ��s
		MessageBox(NULL, "Direct3D�C���^�[�t�F�[�X�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONHAND);
		return false;
	}


	/*Direct3D�f�o�C�X�̎擾*/

	//�f�o�C�X�̎擾�ɕK�v�̏��\���̂̍쐬
	D3DPRESENT_PARAMETERS d3dpp = {};                            //0����������
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                        //�o�b�N�o�t�@�[�̉���
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                      //�o�b�N�o�t�@�[�̏c��
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                     //�o�b�N�o�t�@�[�̃t�H�[�}�b�g
	d3dpp.BackBufferCount = 1;                                   //�o�b�N�o�t�@�[�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                    //�X���b�v���@�̐ݒ�
	d3dpp.Windowed = TRUE;                                       //�E�B���h�E or �t���X�N���[��
	d3dpp.EnableAutoDepthStencil = TRUE;                         //�[�x�o�t�@�[�E�X�e���V���o�t�@�[�̎g�p (���s��)
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                   //�[�x�o�t�@�[�E�X�e���V���o�t�@�[�̃t�H�[�}�b�g�i16�͉��s����16bit�̈Ӗ��j
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	 //�t���X�N���[���̃��t���b�V�����[�g�̐ݒ�
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;    //���t���b�X�����[�g��Present�����̊֌W
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//Direct3D�f�o�C�X�̎擾
	HRESULT hr;

	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);

	// HRESULT�^�ϐ��͐����⎸�s���l�Ƃ��ē����Ă���̂�
	//���s�␬���������肷��ꍇ�̓}�N���𗘗p���� FAILED(hr) SUCCEEDED(hr)
	if (FAILED(hr))
	{
		//�f�o�C�X�̎擾�Ɏ��s
		MessageBox(NULL, "Direct3D�C���^�[�t�F�[�X�̎擾�Ɏ��s���܂���", "�G���[", MB_OK | MB_ICONHAND);
		return false;
	}


	// �e�N�X�`���̓ǂݍ���

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

	//WRAP : �^�C���݂��������o��
	//CLAMP: �Ō��pixel�̐F���L�т��Ă�
	//MIRROR : ���]
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); 
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�@���x�N�g���͕K�����K�����Ďg�p����ݒ������
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