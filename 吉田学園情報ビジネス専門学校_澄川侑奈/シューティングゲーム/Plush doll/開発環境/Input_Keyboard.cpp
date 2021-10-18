//--------------------------------------------------------------------------------
//
//	�L�[�{�[�h���� [Input_keyboard.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Input_keyboard.h"		// �L�[�{�[�h
#include "Input.h"				// ����

//-------------------------------------------------------------------------------
// �R���X�g���N
//-------------------------------------------------------------------------------
CInput_Keyboard::CInput_Keyboard()
{
	// �L�[���̃N���A
	for (int nData = 0; nData < MAX_KEY; nData++)
	{
		m_aKeyState[nData] = 0;				// �O��̓��͏��
		m_akeyStateTrigger[nData] = 0;		// �L�[�g���K�[���
		m_akeyStateRelease[nData] = 0;		// �L�[�����[�X���
	}
}

//-------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------
CInput_Keyboard::~CInput_Keyboard()
{
}

//-------------------------------------------------------------------------------
// ����������
//-------------------------------------------------------------------------------
HRESULT CInput_Keyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ���͂̏���������
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h�ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	m_pDevice->Acquire();

	return S_OK;
}

//-------------------------------------------------------------------------------
// �I������
//-------------------------------------------------------------------------------
void CInput_Keyboard::Uninit(void)
{
	CInput::Uninit();
}

//-------------------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------------------
void CInput_Keyboard::Update(void)
{
	//�ϐ��錾
	BYTE aKeyState[256];		// ���݂̓���
	
	//�f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < MAX_KEY; nKey++)
		{
			// �g���K�[
			m_akeyStateTrigger[nKey] = (~m_aKeyState[nKey])&(aKeyState[nKey]);

			// �����[�X
			m_akeyStateRelease[nKey] = (m_aKeyState[nKey])&(~aKeyState[nKey]);

			// �L�[�������Ă��邩�̏��ۑ�(�v���X)
			m_aKeyState[nKey] = aKeyState[nKey];	
		}
	}
	else
	{
		// �A�N�Z�X���̎擾
		m_pDevice->Acquire();
	}
}

//-------------------------------------------------------------------------------
// �v���X����
//-------------------------------------------------------------------------------
bool CInput_Keyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) != 0;
}

//-------------------------------------------------------------------------------
// �g���K�[����
//-------------------------------------------------------------------------------
bool CInput_Keyboard::GetTrigger(int nKey)
{
	return(m_akeyStateTrigger[nKey] & 0x80) != 0;
}

//-------------------------------------------------------------------------------
// �����[�X����
//-------------------------------------------------------------------------------
bool CInput_Keyboard::GetRelease(int nKey)
{
	return(m_akeyStateRelease[nKey] & 0x80) != 0;
}