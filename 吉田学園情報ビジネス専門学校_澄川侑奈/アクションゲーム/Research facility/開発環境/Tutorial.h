//--------------------------------------------------------------------------------
//
//	�`���[�g���A����ʏ��� [Tutorial.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _TUTORIAL_H
#define	_TUTORIAL_H

#include "main.h"

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorial(bool bSelect);

#endif