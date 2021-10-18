//--------------------------------------------------------------------------------
//
//	���C������ [mein.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "main.h"			// ���C��
#include "renderer.h"		// �����_�����O
#include "scene.h"			// �|���S��
#include "scene2D.h"		// 2D�|���S��
#include "manager.h"		// �}�l�[�W��

//--------------------------------------------------------------------------------
// �}�N����`
//--------------------------------------------------------------------------------
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"Plush doll"	// �E�C���h�E�̃L���v�V������

//--------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�:
//--------------------------------------------------------------------------------
#ifdef _DEBUG
int	g_nCountFPS;								// FPS�J�E���^
#endif

//--------------------------------------------------------------------------------
// ���C���֐�
//--------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
		// �R���\�[�����쐬����
		AllocConsole();
		// �W�����o�͂Ɋ��蓖�Ă�
		FILE* fp = NULL;
		// ���݂̃R�[�h
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("%s", "�m�肽�����\n");
#endif

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						(rect.right - rect.left),
						(rect.bottom - rect.top),
						NULL,
						NULL,
						hInstance,
						NULL);

	//�@�}�l�[�W���N���X�̐���
	CManager*pManager = NULL;		// ���g��NULL�ɂ���

	// ���I�m��
	if (pManager == NULL)
	{// NULL�`�F�b�N
		pManager = new CManager;

		if (pManager != NULL)
		{// NULL����Ȃ�������
			 // ����������
			if (pManager->Init(hWnd, TRUE, hInstance))		// FALSE���ƃt���X�N���[���BTRUE���Ǝw��̑傫��
			{// ������������ʂ�����
				return -1;						// true��������-1�Ԃ�
			}

		}
	}
	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwCurrentTime =
	dwFrameCount = 0;
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
#ifdef _DEBUG
				// FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�

				// �X�V����
				pManager->Update();

				// �`�揈��
				pManager->Draw();

				// �J�E���g
				dwFrameCount++;
			}
		}
	}
	// �}�l�[�W���[�̔j��
	if (pManager != NULL)
	{
		// �I������
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:				// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);	// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------
//	�f�o�C�X�̎擾(FPS)
//-------------------------------------------------------------------------------
int GetFPS(void)
{
#ifdef _DEBUG
	return g_nCountFPS;
#endif
}