//--------------------------------------------------------------------------------
//
//	XInput�̏��� [Xcontroller.cpp]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#include "Xcontroller.h"		// Xinput
#include "camera.h"				// �J����
#include "player.h"				// �v���C���[
#include "keyboard.h"			// �L�[�{�[�h
#include "fade.h"				// �t�F�[�h

//--------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------
XINPUT_STATE g_state;		// Xinput�̏��

XinputGamepad g_Xinput;		// �Q�[���p�b�g�̏��

//-------------------------------------------------------------------------------
// Xinput�̍X�V����
//-------------------------------------------------------------------------------
void UpdateXcontroller(void)
{
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));

	//XInput����R���g���[���[�̏�Ԃ��擾����
	DWORD dwResult = XInputGetState(0, &g_state);

	if (dwResult == ERROR_SUCCESS)
	{// �R���g���[�����ڑ����ꂽ
		XinputButton();		// �{�^���̏���
		XinputStick();		// �X�e�B�b�N�̏���
	}
	else
	{// �R���g���[�����ڑ�����ĂȂ�

	}
}

//-------------------------------------------------------------------------------
// �{�^���̏���
//-------------------------------------------------------------------------------
void XinputButton(void)
{
	// �v���C���[�̏������炤
	Player * pPlayer = GetPlayer();

	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{// A �{�^���������ꂽ
		SetFade(FADE_OUT, MODE_GAME);
	}
}

//-------------------------------------------------------------------------------
// �X�e�b�N�̏���
//-------------------------------------------------------------------------------
void XinputStick(void)
{
	// �J�����̏������炤
	Camera * pCamer = GetCamera();
	// �v���C���[�̏������炤
	Player * pPlayer = GetPlayer();

	// �f�b�g�]�[���̐ݒ�
	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}

	// JOYPAD�̃X�e�B�b�N����
	if (g_state.Gamepad.sThumbLX != 0 || g_state.Gamepad.sThumbLY != 0)
	{//  �X�e�B�b�N�̓��͊p�x
		g_Xinput.fAngle = atan2f((float)g_state.Gamepad.sThumbLX, (float)g_state.Gamepad.sThumbLY * -1);

		// �X�e�B�b�N�̓��͓`����
		g_Xinput.bPlessLStick = true;

		// �ړ���
		pPlayer->move.x -= 1 * sinf(pCamer->rot.y - g_Xinput.fAngle);		// X��
		pPlayer->move.z -= 1 * cosf(pCamer->rot.y - g_Xinput.fAngle);		// Z��
	}
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
#if 0

XINPUT_STATE * GetXcontroller(void)
{

}

#endif
