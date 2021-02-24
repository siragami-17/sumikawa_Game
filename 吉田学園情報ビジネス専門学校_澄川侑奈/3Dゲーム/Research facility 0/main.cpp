//--------------------------------------------------------------------------------
//
//	�E�C���h�E�̏��� [main.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "main.h"
#include "camera.h"			// �J����
#include "keyboard.h"		// �L�[�{�[�h
#include "mouse.h"			// �}�E�X
#include "Xcontroller.h"	// Xinput
#include "fade.h"			// �t�F�[�h
#include "sound.h"			// BGM
#include "title.h"			// �^�C�g��
#include "tutorial.h"		// �`���[�g���A��
#include "game.h"			// �Q�[��
#include "result.h"			// ���U���g
#include "ranking.h"		// �����L���O
#include "beginning.h"		// ���߂̉��

//-------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------
#define CLASS_NAME "windowclass"									// �E�C���h�E�N���X��
#define WINDOW_NAME "Research facility 0"							// �E�C���h�E��
#define ID_BUTTON000	(101)										// �{�^��000��ID
#define ID_EDIT000		(111)										// �G�f�B�b�g��ID
#define WINDOW_POS_X	(500)										// �E�C���h�E�̍���X���W
#define WINDOW_POS_Y	(500)										// �E�C���h�E�̍���Y���W
#define ID_TIMER		(121)										// �^�C�}�[��ID
#define TIMER_INTERVAL	(1000/60)									// �^�C�}�[�����Ԋu
#define MAX_FPS			(256)										// FPS

#define RED				(0)											// �J���[(��)
#define GREEN			(0)											// �J���[(��)
#define BLUE			(0)											// �J���[(��)
#define OPACITY			(255)										// �J���[(�s����)

//-------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hEnd, BOOL bWindow);
void DrawFPS(void);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawTxT(void);		// ���l���o��

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECT3D9 g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	// Direct3D�f�o�C�X�ւ��|�C���^
LPD3DXFONT g_pFont = NULL;				// �t�H���g�ւ̃|�C���^
int g_nCountFPS;						// FPS�J�E���^
MODE g_mode = MODE_TITLE;				// ���[�h�̎��

//-------------------------------------------------------------------------------
//	���C���֐�
//-------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow)
{
	DWORD dwExecLastTime;			// �������s�ŏI����
	DWORD dwFPSLastTime;			// FPS�v���ŏI����
	DWORD dwCurrentTime;			// ���ݎ���
	DWORD dwFrameCount;				// �t���[���J�E���g

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();	// ���ݎ�����ݒ�
	dwFrameCount = 0;				// ������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"CLASS_NAME",
		LoadIcon(NULL,IDI_APPLICATION),
	};
	HWND hWnd;
	MSG msg;

	// �E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�C���h�E�쐬
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);	// �E�C���h�E�̑傫���𒲐�����

	hWnd = CreateWindowEx
	(0,
		"CLASS_NAME",
		WINDOW_NAME,				// �E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,		// ��
		rect.bottom - rect.top,		// ����
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������
	if (FAILED(Init(hInstance, hWnd, FALSE)))// FALSE���ƃt���X�N���[���BTRUE���Ǝw��̑傫��
	{
		return -1;
	}

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	// ���[�v���b�Z�[�W
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	// Windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	// DirectX�̏���

			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// �ŏI�����̕ۑ�
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime)>(1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	// �I������
	Uninit();

	// �E�C���h�E�̓o�^����
	UnregisterClass("CLASS_NAME", wcex.hInstance);
	return(int)msg.wParam;
}

//-------------------------------------------------------------------------------
//	�E�C���h�E�v���V�[�W��
//-------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �ϐ��錾
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// �~�{�^�����������Ƃ�
	case WM_CLOSE:
		nID = MessageBox(NULL, "�I�����܂����H", "����", (MB_YESNO | MB_ICONQUESTION));						//�E�C���h�E�ɕ\��
		if (nID == IDYES)
		{	//�͂���I��
			DestroyWindow(hWnd);
		}
		else
		{	// ��������I��
			return 0;
		}
		break;
	case WM_KEYDOWN:

		//ESC�L�[���������Ƃ�
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(NULL, "�I�����܂����H", "����", (MB_YESNO | MB_ICONQUESTION | MB_TOPMOST));	//�E�C���h�E�ɕ\��
			if (nID == IDYES)
			{	// �͂���I��
				DestroyWindow(hWnd);
			}
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//-------------------------------------------------------------------------------
//	����������
//-------------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bwindow)
{
	//�ϐ��錾
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//�Q�[����ʂ̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//�Q�[����ʂ̍���
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;	//�L���ɂ���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bwindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direact3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice
	(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice
		(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice
			(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//���u�����h(���l�̍���)�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�\�[�X�̍������@�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�f�X�e�B�l�[�V�����̍������@�̐ݒ�

	//�T���v���[�X�e�[�g�̐ݒ�(�e�N�X�`���̐ݒ�)
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k���̎�	���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g��̎�	���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l		�J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V�l		�J��Ԃ�

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	D3DXCreateFont(g_pD3DDevice,
		18,	//�T�C�Y
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont);

	// �L�[���͂̏���������
	Initkeyboard(hInstance, hWnd);

	//�T�E���h
	InitSound(hWnd);

	//�t�F�[�h
	InitFade(g_mode);

	//���[�h�̐ݒ�
	SetMode(g_mode);

	// �}�E�X�̏���������
	mainMouse();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�I������
//-------------------------------------------------------------------------------
void Uninit(void)
{
	//�T�E���h�̏I������
	UninitSound();

	//�t�F�[�h�̏I������
	UninitFade();

	// �L�[�{�[�h�̏I������
	Uninitkeyboard();

	//���[�h�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:					// �^�C�g����ʂ̏I������
		UninitTitle();
		break;
	case MODE_TUTORIAL:					// �`���[�g���A����ʂ̏I������
		UniniTtutorial();
		break;
	case MODE_BEGINNING:				// ���߂̉�ʂ̏I������
		UninitBeginning();
		break;
	case MODE_GAME:						// �Q�[���̏I������
		UninitGame();
		break;
	case MODE_RESULT:					// ���U���g�̏I������
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();				// �����L���O�̏I������
		break;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	// Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// birect3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�X�V����
//-------------------------------------------------------------------------------
void Update(void)
{
	UpdateXcontroller();	// Xinput
	UpdateFade();			// �t�F�[�h�̍X�V����
	Updatakeyboard();		// �L�[�{�[�h�̍X�V����

	//���[�h�̍X�V����
	switch (g_mode)
	{
	case MODE_TITLE:					// �^�C�g����ʂ̍X�V����
		UpdateTitle();
		break;
	case MODE_TUTORIAL:					// �`���[�g���A����ʂ̍X�V����
		UpdateTutorial();
		break;
	case MODE_BEGINNING:				// ���߂̉�ʂ̍X�V����
		UpdateBeginning();
		break;
	case MODE_GAME:						// �Q�[���̍X�V����
		UpdateGame();
		break;
	case MODE_RESULT:					//���U���g�̍X�V����
		UpdateResult();
		break;
	case MODE_RANKING:
		UpdateRanking();				// �����L���O�̍X�V����
		break;
	}
}

//-------------------------------------------------------------------------------
//	�`�揈��
//-------------------------------------------------------------------------------
void Draw(void)
{
	// �o�b�N�o�b�t�@&�o�b�t�@�̃N���A(��ʂ̃N���A)
	g_pD3DDevice->Clear
	(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(RED, GREEN, BLUE, OPACITY),		// �E�C���h�E�̃J���[�ݒ�
		1.0f,
		0);


	// �J�����̐ݒ�
	SetCamera(1);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{// �`��J�n(�`��ɕK�v)

		D3DVIEWPORT9 viewportDef;

		// ���݂̃r���[�|�[�g���擾
		g_pD3DDevice->GetViewport(&viewportDef);

		// �J�����̐ݒ�
		SetCamera(1);

		 //���[�h�̕`�揈��
		switch (g_mode)
		{
		case MODE_TITLE:					//�^�C�g����ʂ̕`�揈��
			DrawTitle();
			break;
		case MODE_TUTORIAL:					//�`���[�g���A����ʂ̕`�揈��
			DrawtuTorial();
			break;
		case MODE_BEGINNING:				// ���߂̉�ʂ̕`�揈��
			DrawBeginning();
			break;
		case MODE_GAME:						//�Q�[���̕`�揈��
			DrawGame();
			break;
		case MODE_RESULT:					//���U���g�̕`�揈��
			DrawResult();
			break;
		case MODE_RANKING:
			DrawRanking();					// �����L���O�̕`�揈��
			break;
		}

		// �r���[�|�[�g�����ɖ߂�
		g_pD3DDevice->SetViewport(&viewportDef);

		DrawFade();					//�t�F�[�h�̕`�揈��

		// Release�̎�FPS�̕\��������
#ifdef _DEBUG
		DrawFPS();						// FPS�̕`�揈��
		DrawTxT();						// ���l�̕`�揈��

#endif

		g_pD3DDevice->EndScene();		// �`��I��

	}
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-------------------------------------------------------------------------------
//	�f�o�C�X�̎擾
//-------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//-------------------------------------------------------------------------------
//	FPS�̕`�揈��
//-------------------------------------------------------------------------------
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[MAX_FPS];

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	// �e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));		// FPS�̐F��ς���
}

//-------------------------------------------------------------------------------
//	�J�������l�̕`�揈��
//-------------------------------------------------------------------------------
void DrawTxT(void)
{
	// �J�����̏��
	Camera pCamera;
	pCamera = *GetCamera();

	// �ǂ��܂ł͈̔͂�
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �ϐ��錾
	char aStr[256];

	int nNum = sprintf(&aStr[0],"%.2f",pCamera.rot.y);

	// �e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));		// FPS�̐F��ς���
}

//-------------------------------------------------------------------------------
//	���[�h�̐ݒ�
//-------------------------------------------------------------------------------
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:					//�^�C�g����ʂ̏I������
		UninitTitle();
		break;
	case MODE_TUTORIAL:					//�`���[�g���A����ʂ̏I������
		UniniTtutorial();
		break;
	case MODE_BEGINNING:				// ���߂̉�ʂ̏I������
		UninitBeginning();
		break;
	case MODE_GAME:						//�Q�[���̏I������
		UninitGame();
		break;
	case MODE_RESULT:					//���U���g�̏I������
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();				// �����L���O�̏I������
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:					//�^�C�g����ʂ̏���������
		InitTitle();
		break;
	case MODE_TUTORIAL:					//�`���[�g���A����ʂ̏���������
		InitTutorial();
		break;
	case MODE_BEGINNING:				// ���߂̉�ʂ̏���������
		InitBeginning();
		break;
	case MODE_GAME:						//�Q�[���̏���������
		InitGame();
		break;
	case MODE_RESULT:					//���U���g�̏���������
		InitResult();
		break;
	case MODE_RANKING:
		InitRanking();					// �����L���O�̏���������
		break;
	}
	g_mode = mode;
}

//-------------------------------------------------------------------------------
//	���[�h�̎擾
//-------------------------------------------------------------------------------
MODE * GetMode(void)
{
	return &g_mode;		// ���[�h�̏��̐擪�A�h���X��Ԃ�
}