//--------------------------------------------------------------------------------
//
//	�L�[�{�[�h���� [Input_keyboard.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

#include "main.h"
#include "Input.h"

//-------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------
#define MAX_KEY		(256)

//-------------------------------------------------------------------------------
// �L�[�{�[�h�N���X(�h���N���X)
//-------------------------------------------------------------------------------
class  CInput_Keyboard : public CInput
{
public:
	CInput_Keyboard();									// �R���X�g���N
	 ~CInput_Keyboard();								// �f�X�g���N�^

	 HRESULT Init(HINSTANCE hInstance,HWND hWnd);		// ����������
	 void Uninit(void);									// �I������
	 void Update(void);									// �X�V����
	 bool GetPress(int nKey);							// �v���X(����������)
	 bool GetTrigger(int nKey);							// �g���K�[(�������u��)
	 bool GetRelease(int nKey);							// �����[�X

private:
	BYTE m_aKeyState[MAX_KEY];							// �ߋ��̓��͏��
	BYTE m_akeyStateTrigger[MAX_KEY];					// �L�[�g���K�[���
	BYTE m_akeyStateRelease[MAX_KEY];					// �L�[�����[�X���
};

#endif