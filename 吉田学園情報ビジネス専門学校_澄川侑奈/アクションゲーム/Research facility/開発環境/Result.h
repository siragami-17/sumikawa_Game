//--------------------------------------------------------------------------------
//
//	���U���g��ʂ̏��� [Result.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _RESULT_H
#define	_RESULT_H

#include "main.h"

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(bool bClear);

#endif