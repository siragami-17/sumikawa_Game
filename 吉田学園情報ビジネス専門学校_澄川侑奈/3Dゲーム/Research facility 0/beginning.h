//--------------------------------------------------------------------------------
//
//	�n�܂�̉�ʂ̏��� [beginninig.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _BEGINNING_H_
#define	_BEGINNING_H_

#include "main.h"

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitBeginning(void);
void UninitBeginning(void);
void UpdateBeginning(void);
void DrawBeginning(void);

void SetPause(bool bPause);		// �|�[�Y

#endif