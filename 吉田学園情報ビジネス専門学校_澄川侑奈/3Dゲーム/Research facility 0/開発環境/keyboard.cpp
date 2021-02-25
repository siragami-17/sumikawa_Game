//--------------------------------------------------------------------------------
//
//	�L�[�{�[�h�̏��� [input.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "keyboard.h"

//-------------------------------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------------------------------
LPDIRECTINPUT8 g_pInput = NULL;				//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevkeyboard = NULL;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_akeyState[256];						//�L�[�{�[�h�̓��͏��()���񂩂���
BYTE g_akeyStateTrigger[256];				//�L�[�g���K�[���
BYTE g_akeyStateRelease[256];				//�L�[�����[�X���
BYTE g_akeyStateRepeat[256];				//�L�[���s�[�g���
BYTE g_aCountRepeat[256];					//�L�[���s�[�g�J�E���^�[

//-------------------------------------------------------------------------------
//	����������
//-------------------------------------------------------------------------------
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevkeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevkeyboard -> SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�ݒ�
	if (FAILED(g_pDevkeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	g_pDevkeyboard->Acquire();

	return S_OK;
}

//-------------------------------------------------------------------------------
//	�I������
//-------------------------------------------------------------------------------
void  Uninitkeyboard(void)
{
	if (g_pDevkeyboard != NULL)
	{
		//�A�N�Z�X���̔j��
		g_pDevkeyboard->Unacquire();
		g_pDevkeyboard->Release();
		g_pDevkeyboard = NULL;
	}

	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//-------------------------------------------------------------------------------
//	�X�V����
//-------------------------------------------------------------------------------
void Updatakeyboard(void)
{
	//�ϐ��錾
	BYTE aKeyState[256];
	
	//�f�o�C�X����f�[�^���擾

	if (SUCCEEDED(g_pDevkeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			
			g_akeyStateTrigger[nKey] = (g_akeyState[nKey] ^ aKeyState[nKey])&aKeyState[nKey];	//�g���K�[

			//g_akeyStateRelease[nKey] = (g_akeyState[nKey] ^ aKeyState[nKey]) ^ aKeyState[nKey];	//�����[�X

			//g_akeyStateRepeat[nKey] = (g_akeyState[nKey]aKeyState[nKey])aKeyState[nKey];

			g_akeyState[nKey] = aKeyState[nKey];	//�L�[�������Ă��邩�̏��ۑ�(�v���X)
		}
	}
	else
	{
		//�A�N�Z�X���̎擾
		g_pDevkeyboard->Acquire();
	}

}

//-------------------------------------------------------------------------------
//	�L�[�{�[�h���̎擾
//-------------------------------------------------------------------------------
bool GetkeyboardPress(int nkey)
{
	return(g_akeyState[nkey] & 0x80) ? true : false;
}

//-------------------------------------------------------------------------------
//	�L�[�{�[�h�̃g���K�[���
//-------------------------------------------------------------------------------
bool GetkeyboardTrgger(int nkey)
{
	return(g_akeyStateTrigger[nkey] & 0x80) ? true : false;
}