//--------------------------------------------------------------------------------
//
//	�L�[�{�[�h�̏��� [input.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _INPUT_H_
#define	_INPUT_H_

#include "main.h"

//-------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//-------------------------------------------------------------------------------
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd);
void  Uninitkeyboard(void);
void Updatakeyboard(void);
bool GetkeyboardPress(int nkey);							//�v���X
bool GetkeyboardTrgger(int nkey);							//�g���K�[

#endif