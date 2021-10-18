//--------------------------------------------------------------------------------
//
//	キーボードの処理 [input.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef  _INPUT_H_
#define	_INPUT_H_

#include "main.h"

//-------------------------------------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------------------------------------
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd);
void  Uninitkeyboard(void);
void Updatakeyboard(void);
bool GetkeyboardPress(int nkey);							//プレス
bool GetkeyboardTrgger(int nkey);							//トリガー

#endif