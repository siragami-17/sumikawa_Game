//--------------------------------------------------------------------------------
//
//	XInput�̏��� [Xcontroller.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _XCONTROLLE_H
#define	_XCONTROLLE_H

#include "main.h"

//-------------------------------------------------------------------------------
// �\����
//-------------------------------------------------------------------------------
typedef struct
{
	bool bPless = false;			// �{�^��
	bool bPlessLStick = false;		// L�X�e�B�b�N
	float fAngle;
}XinputGamepad;

//-------------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------------------
void UpdateXcontroller(void);
void XinputButton(void);		// �{�^���̏���
void XinputStick(void);			// �X�e�B�b�N�̏���

//XINPUT_STATE*GetXcontroller(void);

#endif